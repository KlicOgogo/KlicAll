/**
 * Created by andrejka on 23.12.15.
 */
public abstract class DustCleaner implements Comparable {
    protected String industry;
    protected String color;
    protected Integer power;
    protected String wayToImage;

    public DustCleaner()
    {
        industry = new String();
        color = new String();
        power = 0;
        wayToImage = new String();
    }
    public DustCleaner(String ind, String col, int pow, String way)
    {
        industry = new String(ind);
        color = new String(col);
        power = pow;
        wayToImage =  new String(way);
    }
    public int compareTo(Object obj)
    {
        if (industry.compareTo(((DustCleaner)obj).industry)!=0)
            return industry.compareTo(((DustCleaner)obj).industry);
        else {
            if (power.compareTo(((DustCleaner)obj).power) !=0)
                return (-1)*power.compareTo(((DustCleaner)obj).power);
            else
                return color.compareTo(((DustCleaner)obj).color);
        }
    }
    public String toString()
    {
        return industry+" "+color+" "+power+" "+wayToImage;
    }

    public String getIndustry()
    {
        return industry;
    }

    public String getColor()
    {
        return color;
    }
}
