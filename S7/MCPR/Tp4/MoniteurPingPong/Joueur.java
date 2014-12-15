// Joueur dans le jeu de ping pong avec synchronisation via un "moniteur" Table

import java.util.logging.Level;
import java.util.logging.Logger;


public class Joueur implements Runnable {
  // Lee type de coup joue
  private int monType;
  // Le numero associe au joueur
  private int monNum;
  // Le "moniteur" gerant l'acces des joueurs a la table commune
  private MoniteurTable maTable;

  // Constructeur de la classe joueur
  public Joueur (int numJoueur, int typeJoueur, MoniteurTable uneTable) {
        monType = typeJoueur;
        monNum = numJoueur;
        maTable = uneTable;
        System.out.println("Joueur " + monNum + " (" + monType + ") : defini");
  }
  
  public static void waiting()
    {
        try { Thread.sleep(500); }
        catch( Exception e){ }
    }

  // Implantation de run => comportement du joueur
  @Override
  public void run() {
    int i;
    for (i = 0; i < 10; i++) {
        try {
            // Demander l'acces a la table pour jouer quand il le faut
            // A completer : appeler l'operation qui convient de la classe "moniteur"
            maTable.demanderAccesTable(monType);
            // On a l'acces a la table, on peut jouer (en prenant un peu de temps)
            System.out.println("Joueur " + monNum + " (de type " + monType + ") : je joue pour la " + (i+1) + "me fois");
            // Relacher l'acces a la table pour laisser jouer le suivant
            // A completer : appeler l'operation qui convient de la classe "moniteur"
            waiting();
            maTable.libererAccesTable();
        } catch (InterruptedException ex) {
            Logger.getLogger(Joueur.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    System.out.println("Joueur " + monNum + " (de type " + monType + ") : termine");
  }
}
