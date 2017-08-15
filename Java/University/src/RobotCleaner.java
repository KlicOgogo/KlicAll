/**
 * Created by andrejka on 23.12.15.
 */
public class RobotCleaner extends DustCleaner {
    private Boolean screen;

    public RobotCleaner()
    {
        super();
        screen = false;
    }
    public RobotCleaner(String ind, String col, int pow, String way, boolean screen1)
    {
        super(ind, col, pow, way);
        screen = screen1;
    }

    public String toString()
    {
        return super.toString()+" "+screen.toString();
    }
}
