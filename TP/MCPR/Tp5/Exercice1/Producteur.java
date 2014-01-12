import java.lang.*;
import java.util.*;

public class Producteur extends Thread {

        private int number;
        private BufferPartage buffer;

        public Producteur(int number, BufferPartage buffer)
        {
                this.buffer = buffer;
                this.number = number;
        }

        public void run()
        {
                for (int i=0; i<10; ++i)
                        buffer.deposerMessage(new Message(i%3, "Message " + number));
        }
}