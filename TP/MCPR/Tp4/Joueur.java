import java.io.*;
import java.lang.*;
import java.util.*;

public class Joueur extends Thread
{
    public static boolean partyInProgress;
    public int type;
    public int number;
    public HoareMonitor monitor;

    public Joueur( int type, int number, HoareMonitor monitor )
    {
        this.partyInProgress = true;
        this.type = type;
        this.number = number;
        this.monitor = monitor;
    }

    public void run()
    {
        while (partyInProgress)
        {
            monitor.accessTable(type);
            play(this.type, this.number);
            waiting();
            monitor.freeTable();
        }
    }

    public static void play(int type, int number)
    {
        if( type == 0 )
            System.out.print( number + "-> PING\n");
        else
            System.out.print( number + "       PONG  <-\n");
    }

    public static void waiting()
    {
        try { Thread.sleep(500); }
        catch( Exception e){ }
    }
}