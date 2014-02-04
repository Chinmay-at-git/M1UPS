import java.lang.*;

public class Participant extends Thread {

        public int number;
        public Barriere barriere;

        public Participant(int number, Barriere barriere) {
                this.number = number;
                this.barriere = barriere;
        }

        public void run()
        {
                barriere.demanderRDV(number);
                barriere.prendreRDV(number);
        }
}