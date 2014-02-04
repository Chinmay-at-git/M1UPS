import java.io.*;
import java.lang.*;
import java.util.concurrent.locks.*;

public class HoareMonitor
{
        static ReentrantLock lock;
        private int numPlayer;
        private static int nbusers;
        static private Condition player0Cond;
        static private Condition player1Cond;

        public HoareMonitor()
        {
                numPlayer = 0;
                nbusers = 0;
                lock = new ReentrantLock();
                player0Cond = lock.newCondition();
                player1Cond = lock.newCondition();
        }

        public void accessTable(int number)
        {
                lock.lock();
                try
                {
                        if( nbusers != 0 )
                        {
                                if( number == 0) player0Cond.await();
                                else player1Cond.await();
                        }
                        else
                                numPlayer = number;
                }
                catch (Exception e) {}
                nbusers = 1;

                lock.unlock();
        }

        public void freeTable()
        {
                lock.lock();
                if (numPlayer == 0) numPlayer = 1;
                else numPlayer = 0;
                if( numPlayer == 0) player0Cond.signal();
                else player1Cond.signal();
                lock.unlock();
        }
}