/**
 * Created by andrejka on 16.2.16.
 */
public class Message implements Comparable {
    private int id;
    private String message;
    private String author;
    long timestamp;

    public Message(int newId, String newMessage, String newAuthor, long newTimestamp) {
        id = newId;
        message = newMessage;
        author = newAuthor;
        timestamp = newTimestamp;
    }

    public int getId() {
        return id;
    }

    public String getAuthor() {
        return author;
    }

    public String getMessage()
    {
        return message;
    }

    public long getTimestamp()
    {
        return timestamp;
    }
    public String toString() {
        return id + " " + message + " " + author + " " + timestamp;
    }

    public int compareTo(Object object) {
        return ((Long)timestamp).compareTo(((Message) object).timestamp);
    }
}
