import java.io.*;
import java.lang.*;
import java.util.*;
import java.util.concurrent.locks.*;
// Base pour le jeu de ping pong sans synchronisation entre joueurs

// A modifier pour faire jouer un joueur Ping et un joueur Pong
// puis N joueurs Ping et M joueurs Pong
// avec N et M = parametres de l'application

public class BasePingPong {

	   public static void main(String[] args)  {
	          
	          if(args.length < 2){
	            System.out.println("Erreur args < 2\n N ==> joueurs PING\n M ==> joueurs PONG");
	            System.exit(0);
	          }
	          int N = Integer.parseInt(args[0]);
	          int M = Integer.parseInt(args[1]);
	          
	          List<Thread> thJoueursPing = new ArrayList<Thread>();
	          List<Thread> thJoueursPong = new ArrayList<Thread>();
	          
	          int nb;
	          for(nb = 0; nb < N; ++nb){
	            Thread joueur = new Thread(new Joueur(nb+1, Joueur.PING));
                thJoueursPing.add(joueur);
                thJoueursPing.get(nb).start();
	          }
	          
	          for(int i = 0; i < M; ++i){
	            Thread joueur = new Thread(new Joueur(i+1+nb, Joueur.PONG));
                thJoueursPong.add(joueur);
                thJoueursPong.get(i).start();
	          }

	          System.out.println("Fin lancement application BasePingPong_VRunnable");

	          System.out.println("Fin application BasePingPong_VRunnable");
	        }
	}

