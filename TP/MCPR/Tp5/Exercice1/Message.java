public class Message {

        public String value;
        public int type;

        public Message()
        {}

        public Message(int type, String value)
        {
                this.type = type;
                this.value = value;
        }

        public String toString()
        {
            return "type = " + type + "\t value = " + value.toString();
        }
}