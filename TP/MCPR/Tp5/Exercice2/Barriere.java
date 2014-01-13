import java.lang.*;
import java.util.*;
import java.util.concurrent.locks.*;

public class Barriere {

        private static int cpt;
        private static int cptAttente;
        private static int cptRDV;
        private static int cptTotal;
        private static int nbParticipant;
        private static ReentrantLock lock;
        private static Condition condProchainRdv;
        private static Condition condAttendAutres;

        public Barriere(int number)
        {
                cpt = 0;
                cptAttente = 0;
                cptRDV = 0;
                cptTotal = 0;
                nbParticipant = number;
                lock = new ReentrantLock();
                condProchainRdv = lock.newCondition();
                condAttendAutres = lock.newCondition();
        }

        public void demanderRDV(int number)
        {
                lock.lock();
                try {
                        if( cpt >= nbParticipant )
                        {
                                cptAttente++;
                                System.out.print( number + " - Attends le RDV\n");
                                condProchainRdv.await();
                                cptAttente--;
                        }
                        cpt++;
                }
                catch( Exception e){}
                lock.unlock();
        }

        public void prendreRDV(int number)
        {
                lock.lock();
                try {
                                cptRDV++;
                                if( cpt < nbParticipant )
                                        condAttendAutres.await();
                                else
                                        condAttendAutres.signalAll();
                                cpt--;
                                cptRDV--;
                                condProchainRdv.signal();
                                cptTotal++;
                        System.out.print("\t" + number + " - RDV terminé ( " + cptRDV + " / " + cptAttente + " = " + cptTotal + " )\n");
                        condProchainRdv.signal();
                }
                catch( Exception e){}
                lock.unlock();
        }

}