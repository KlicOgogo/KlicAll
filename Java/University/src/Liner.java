public class Liner extends Series {

public Liner()
{
	super();
}

public Liner (double x, double den, int qua)
{
	super(x, den, qua);
}

public double getElement (int j) throws IllegalArgumentException
{
	if (j > quant)
		throw new IllegalArgumentException ("Wrong parameter!");
	return x0 + denom * j;
} 

public void toFile (String file)
{
	super.toFile(file);	
}

}
