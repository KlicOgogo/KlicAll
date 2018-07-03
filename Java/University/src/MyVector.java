
public class MyVector {
	
private:
	double[] vector;
	int dim;
public:
	MyVector (MyVector v)
	{
		vector = v.vector;
		dim = v.dim; 
	}
		
	MyVector (double[] arr, int d)
	{
		try
		{
			if (d < 0)
				throw new IllegalArgumentException ("Wrong parameters!");
		}
		catch (IllegalArgumentException exc)
		{
			System.out.println(exc.getMessage());
		}
		vector = arr;
		dim = d;		
	}
	
	void coordExchange (int c1, int c2)
	{
		try 
		{
			if (c2 >= dim || c2 < 0 || c1 < 0 || c1 >= dim)
				throw new IllegalArgumentException ("Wrong parameters!");
		}
		catch (IllegalArgumentException exc)
		{
			System.out.println(exc.getMessage());
		}
		double value;
		value = vector[c1];
		vector[c1] = vector[c2];
		vector[c2] = value;
	}
	
	void coordOnNumber (int c, double num)
	{
		try
		{
			if (c < 0 || c >= dim)
				throw new IllegalArgumentException("Wrong parameters!");
		} 
		catch (IllegalArgumentException exc)
		{
			System.out.println(exc.getMessage());
		}
		vector[c] *= num;
	}
	
	void addCoordMultipiedOnNumber (int k1, int k2, double num)
	{
		try
		{
			if (k1 >= dim || k2 >= dim || k1 < 0 || k2 < 0)
				throw new IllegalArgumentException ("Wrong parameters!");
		}
		catch (IllegalArgumentException exc)
		{
			System.out.println(exc.getMessage());
		}
		vector[k1] = vector[k1] + vector[k2] * num; 
	}
	
	double[] getCoordinates()
	{
		return vector;
	}
	
	int getDim()
	{
		return dim;
	}
}
