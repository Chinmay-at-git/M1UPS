import java.io.*;
import java.lang.*;
import java.util.*;
// Classe simulant le comportement d'un joueur (ping/pong)

public class Joueur implements Runnable {
  private int monType;
  private int monNum;

  public final static int PONG = 0;
  public final static int PING = 1;

  public Joueur (int numJoueur, int typeJoueur) {
        monType = typeJoueur;
        monNum = numJoueur;
        System.out.println("Joueur " + monNum + " (" + monType + ") : defini");
  }

  // Implantation de run => comportement du joueur
  public void run() {
    int i;
    for (i = 0; i < 10; i++) {
      System.out.println("Joueur " + monNum
       + " (de type " + monType + ") : je joue pour la " + i + "me fois");
    }
    System.out.println("Joueur " + monNum
     + " (de type " + monType + ") : termine");
  }
}

