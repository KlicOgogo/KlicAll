package data;


/**
 * Created by andrejka on 23.12.15.
 */
public class Toy implements Comparable {
    private String name;
    private Integer cost;
    private int minAge;
    private int maxAge;

    public Toy()
    {
        name = new String();
        cost = 0;
        minAge = 0;
        maxAge = 0;
    }

    public Toy(String name1, Integer cost1, int min, int max) throws AgeException, CostException
    {
        if (min >= max || min < 0 || max < 0)
            throw new AgeException("Wrong ages!");
        if (cost1 < 0)
            throw new CostException("Wrong cost!");
        name = new String(name1);
        cost = cost1;
        minAge = min;
        maxAge = max;
    }

    public int compareTo(Object obj)
    {
        return name.compareTo(((Toy)obj).name);
    }

    public String toString()
    {
        return name+" "+ cost + " " + minAge + " " + maxAge;
    }
    public int getMaxAge()
    {
        return maxAge;
    }
    public int getMinAge()
    {
        return minAge;
    }
    public Integer getCost()
    {
        return cost;
    }
}
