
public class Java1 {

	/**
	 * @param args
	 */
	public static void main(String[] args) 
	{
		// TODO Auto-generated method stub
		try
		{
			if (args.length!=2)
				throw new IllegalArgumentException ("Not 2 arguments!");
			double x = Double.parseDouble(args[0]);
			double e = Double.parseDouble(args[1]);
			System.out.println("sum = " + sum(x, e));
		}
		catch (NumberFormatException exc)
		{
			System.out.println("Converting mistake: "+exc.getMessage());
		}
		catch (IllegalArgumentException exc)
		{
			System.out.println(exc.getMessage());
		}
		finally
		{}
	}
	
	public static double sum ( double x, double eps)
	{
		double sum=0, addValue=(x+1)/2;
		double k=1;
		while (Math.abs(addValue) > eps)
		{
			sum+=addValue;
			k++;
			addValue*=(x+Math.pow(k, -1.0/2))/(k+1)/(x+Math.pow(k-1, -1.0/2));
		}
		return sum;
	}
}
