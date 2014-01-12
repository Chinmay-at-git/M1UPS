import java.lang.*;
import java.util.*;
import java.util.concurrent.locks.*;

public class BufferPartage 
{
        private static List<Message> buffer;
        private static int maxMessage;

        private static ReentrantLock lock;
        private static Condition condPlaceLibre;
        private static Condition[] condNouveauMessage;

        public BufferPartage()
        {
                buffer = new ArrayList<>();
                maxMessage = 10;
                lock = new ReentrantLock();
                condPlaceLibre = lock.newCondition();
                condNouveauMessage = new Condition[3];
                for ( Condition c : condNouveauMessage ) {
                        c = lock.newCondition();
                }
        }

        public void deposerMessage( Message msg )
        {
                lock.lock();
                try
                {
                        if( buffer.size() >= maxMessage )
                                condPlaceLibre.await();
                        buffer.add(msg);
                        System.out.print("Depot : " + msg.toString() + "\n");
                        condNouveauMessage[msg.type].signal();
                }
                catch( Exception e) {}        
                lock.unlock();
        }

        public Message retirerMessage(int type)
        {
                Message ret = new Message();
                lock.lock();
                try 
                {
                        if( buffer.size() == 0 )
                                condNouveauMessage[type].await();
                        ret = buffer.remove(0);
                        condPlaceLibre.signal();
                }
                catch (Exception e){ }
                lock.unlock();
                return ret;
        }
}