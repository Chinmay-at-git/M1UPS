import java.util.ArrayList;
import java.util.List;


public class BasePingPongSynchro {
    
    
    public static void main(String[] args) {
        // Creation du "moniteur" gerant les acces synchronises a la table de jeu
        // la meme instance de la classe pour tous les joueurs (sinon, impossible
        // d'avoir de la synchro
        MoniteurTable laTable = new MoniteurTable();
        int type;
        
        if(args.length != 1){
            System.out.println("Erreur args ==> NombreDeJoueur");
            System.exit(0);
        }
        
        int nbJoueurs = Integer.parseInt(args[0]);
	    List<Thread> joueurs = new ArrayList<Thread>();
	         
    	for (int i = 0; i < nbJoueurs; ++i){
                type = ((i+1)%2);
    	    Thread thJoueur =  new Thread(new Joueur(i+1, type, laTable));
    	    joueurs.add(thJoueur);
    	    joueurs.get(i).start();
    	}
    	
            System.out.println("Fin lancement application BasePingPong_VRunnable");
            System.out.println("Fin application BasePingPong_VRunnable");
        }
    
}
