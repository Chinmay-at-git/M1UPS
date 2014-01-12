class Main
{
        public static void main(String[] args)
        {
                if( args.length != 2)
                {
                        System.out.print("Usage : Main [NB_PROD] [NB_CONS]\n");
                        System.exit(1);
                }
                BufferPartage buffer = new BufferPartage();
                int nbProd = Integer.parseInt(args[0]);
                int nbCons = Integer.parseInt(args[1]);
                for (int i=0; i<nbProd; ++i)
                        new Producteur(i, buffer).start();
                for (int i=0; i<nbCons; ++i)
                        new Consomateur(i, buffer).start();
        }        
}