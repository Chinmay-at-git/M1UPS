import java.lang.*;
import java.util.*;

public class Consomateur extends Thread {

        private int number;
        private BufferPartage buffer;

        public Consomateur(int number, BufferPartage buffer) {
                this.buffer = buffer;
                this.number = number;
        }

        public void run()
        {
                for (int i=0; i<10; ++i)
                {
                        Message msg = buffer.retirerMessage(i%3);
                        System.out.print("\tRetrait msg : " + msg + "\n");
                }

        }
}