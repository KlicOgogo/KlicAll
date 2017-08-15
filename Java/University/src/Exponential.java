public class Exponential extends Series {

    public Exponential ()
    {
        super();
    }

    public Exponential (double x, double den, int qua)
    {
        super(x, den, qua);
    }

    public double getElement (int j) throws IllegalArgumentException
    {
        if (j > quant)
            throw new IllegalArgumentException ("Wrong parameter!");
        return x0 * Math.pow(denom, j);
    }

}