import java.io.*;
import java.lang.*;
import java.util.*;
import java.util.concurrent.locks.*;

public class Exercice
{
    public static void main(String[] args)
    {
        HoareMonitor moniteur = new HoareMonitor();
        int t;

        System.out.print("PING PONG !\n");

        int n = 10;
        List<Thread> joueurs = new ArrayList<>();
        for (int i=0; i<n; ++i)
        {
            t = (i%2);
            System.out.print( "Joueur : " + t + "\n");
            Thread j = new Joueur(t, i, moniteur);
            joueurs.add(j);
            joueurs.get(i).start();
        }   
    }
}