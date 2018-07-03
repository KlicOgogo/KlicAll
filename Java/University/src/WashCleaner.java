/**
 * Created by andrejka on 23.12.15.
 */
public class WashCleaner extends DustCleaner {
    private int capacity;

    public WashCleaner()
    {
        super();
        capacity = 0;
    }

    public WashCleaner(String ind, String col, int pow, String way, int capa)
    {
        super (ind, col, pow, way);
        capacity = capa;
    }

    public String toString()
    {
        return super.toString()+" "+capacity;
    }

}
