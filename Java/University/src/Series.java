import java.io.*;

public abstract class Series {
	double x0;
	double denom;
	int quant;

public Series()
{
	x0 = 0;
	denom = 0;
	quant = 0;
}

public Series (double x, double den, int qua)
{
	x0 = x;
	denom = den;
	quant = qua;
}

public abstract double getElement (int j);

public double countSum()
{
	double sum = 0;
	for (int i = 0; i < quant; i++)
		sum += getElement (i);
	return sum;
}

public String toString()
{
	StringBuilder str = new StringBuilder ("");
	for (int i = 0; i < quant; i++)
		str.append (getElement(i) + " ");
	return str.toString();	
}

public void toFile (String fileName) throws IOException
{
	FileWriter writer = new FileWriter (new Flie(flleName));
	writer.write(toString());
	writer.close();	
}

}
