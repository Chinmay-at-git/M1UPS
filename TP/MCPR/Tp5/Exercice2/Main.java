public class Main {

        public static void main(String[] args) {

                if( args.length != 1)
                {
                        System.out.print("Usage : Main [NB_PARTICIPANT]\n");
                        System.exit(1);
                }
                
                int nbParticipant = Integer.parseInt(args[0]);
                Barriere barriere = new Barriere(nbParticipant);

                for (int i=0; i<nbParticipant; ++i)
                        new Participant(i, barriere).start();
        }
}
