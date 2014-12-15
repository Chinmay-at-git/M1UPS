// Classe jouant le role du moniteur qui protege les acces
// a la table de ping-pong et assure l'alternance des coups
// des joueurs 

// Pour declarer des "variables condition"
import java.util.concurrent.locks.Condition;
// Pour declarer des verrous ou semaphores d'exclusion mutuelle
import java.util.concurrent.locks.ReentrantLock;

public class MoniteurTable {
   // Les types de coups possibles
   public static final int PONG = 0;
   public static final int PING = 1;

   // Variable utiles pour la synchronisation
   // verrous, variables conditions . . . 
   // A modifier /completer
   private final ReentrantLock mutex;
   private final Condition joueurPongCond;
   private final Condition joueurPingCond;
   // Variables d'etat
   // A completer
   private static int nbUser;
   private int typeJoueurCourant;
   
   // Constructeur de la classe
   public MoniteurTable () {
      // Creer les verrous et variables condition
	  // A cmodifier / ompleter
	   mutex = new ReentrantLock();
	   joueurPongCond = mutex.newCondition();
	   joueurPingCond = mutex.newCondition();
	   nbUser = 0;
	   typeJoueurCourant = MoniteurTable.PING;
   }

   // Obtenir l'acces a la table pour pouvoir jouer
   public void demanderAccesTable(int typeJoueur) throws InterruptedException {
      mutex.lock();
       try {
           // Se bloquer si on ne peut pas jouer
           if(nbUser != 0){
               if(typeJoueur == MoniteurTable.PONG){
                   joueurPongCond.await();
               }else{
                   joueurPingCond.await();
               }
           }else {
                this.typeJoueurCourant = typeJoueur;
           }
           // On a acces a la table
           nbUser = 1;
           // Fin de l'E.M.
       } finally {
           mutex.unlock();
       }
   }
   
  // Rendre l'acces au joueur du type oppose
   public void libererAccesTable() {
       mutex.lock();
       try {
           if (typeJoueurCourant == MoniteurTable.PONG)
               typeJoueurCourant = MoniteurTable.PING;
           else
               typeJoueurCourant = MoniteurTable.PONG;
           if( typeJoueurCourant == MoniteurTable.PONG)
               joueurPongCond.signal();
           else
               joueurPingCond.signal();
       } finally {
           mutex.unlock();
       }
   }
}

