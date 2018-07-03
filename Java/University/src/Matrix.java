import java.io.*;
import java.util.*;

public class Matrix {
	
private	int dim;

private	double[][] matrix;

public Matrix (double[][] array, int d) throws IllegalArgumentException
	{
		if (array.length != d)
			throw new IllegalArgumentException("Illegal constructor!");
		dim = d;
		matrix = new double[dim][dim];
		for (int i = 0; i < dim; i++)
			for (int j = 0; j < dim; j++)
				matrix[i][j] = array[i][j];
	}

public Matrix (Matrix matr)
{
	dim = matr.dim;
	matrix = new double[dim][dim];
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
			matrix[i][j] = matr.matrix[i][j];
}
private	void lineExchange (int line1, int line2) throws IllegalArgumentException
	{
		if (line1 >= dim || line2 >= dim || line1 < 0 || line2 < 0)
			throw new IllegalArgumentException("Exchanging is impossible!");
		double[] arr = new double [dim];
		for (int k = 0; k < dim; k++)
		{
			arr[k] = matrix[line1][k];
			matrix[line1][k] = matrix[line2][k];
			matrix[line2][k] = arr[k];
		}
	}
	
private	void lineOnNumber (int line, double number) throws IllegalArgumentException
	{
		if (line >= dim || line < 0)
			throw new IllegalArgumentException ("Line does not exist!");
		for (int j = 0; j < dim; j++)
			matrix[line][j] *= number;
	}
	
private	void addLineMultipiedOnNumber (int l1, int l2, double num) throws IllegalArgumentException
	{
		if (l1 >= dim || l1 < 0 || l2 < 0 || l2 >= dim)
			throw new IllegalArgumentException ("Wrong multipying line!");
		for (int i = 0; i < dim; i++)
			matrix[l1][i] = matrix[l1][i] + num * matrix[l2][i];
	}
	
public double[] gaussianMethod (double[] result) throws IllegalArgumentException
	{
		if (dim != result.length)
			throw new IllegalArgumentException ("Different dimensions!");
		double value;

		//Matrix matr1 = new Matrix(matrix, 
		double[][] array = new double[dim][dim];
		for (int i = 0; i < dim; i++)
			for (int j = 0; j < dim; j++)
			{
				array[i][j] = matrix[i][j];
			}
		Matrix matr = new Matrix(array, dim);
		for (int i = 0; i < dim; i++)
		{
			for (int j = i; j < dim; j++)
				if (matrix[j][i] != 0)
				{
					//matr.lineExchange(i, j);
					lineExchange(i, j);
					value = result[i];
					result[i] = result[j];
					result[j] = value;
					j = dim - 1;
				}
			//matr.lineOnNumber(i, 1.0 / matrix[i][i]);
			result[i] /= matrix[i][i];
			lineOnNumber(i, 1.0 / matrix[i][i]);
			/*for (int t = 0; t < dim; t++)
				System.out.print(result[t] + " ");
			System.out.println();*/
			for (int k = i + 1; k < dim; k++)
			{
				//matr.addLineMultipiedOnNumber(k, i, -matrix[k][i]);
				result[k] = result[k] - result[i] * matrix[k][i];
				addLineMultipiedOnNumber(k, i, -matrix[k][i]);
			}
			/*for (int t = 0; t < dim; t++)
				System.out.print(result[t] + " ");
			System.out.println();
			out();*/
		}
		for (int i = dim - 1; i > -1; i--)
		{
			for (int j = i - 1; j > -1; j--)
			{
				result[j] = result[j] - result[i] * matrix[j][i];
			//	matr.addLineMultipiedOnNumber(j, i, -matrix[j][i]);
				addLineMultipiedOnNumber(j, i, -matrix[j][i]);
			}/*
			for (int t = 0; t < dim; t++)
				System.out.print(result[t] + " ");
			System.out.println();
			matr.out();
			out();*/
		}
		return result;
		//return matr;
	}

public void out()
{
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
			System.out.print(matrix[i][j] + "   ");
		System.out.println();
	}
	System.out.println();
}

public double[] residual (double[] x, double[] b) throws IllegalArgumentException
{
	if (x.length != dim || b.length != dim)
		throw new IllegalArgumentException ("Different dimensions!");
	double[] result = new double [dim];
	for (int i = 0; i < dim; i++)
		result[i] = 0;
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			result[i] += matrix[i][j] * x[j];
		}
	}
	for (int i = 0; i < dim; i++)
		result[i] -= b[i];
	return result;
}

public static void main (String args[])
{
	try 
	{
	Scanner in = new Scanner (new File("file.txt"));
	int dimM = in.nextInt();
	double[][] array = new double[dimM][dimM];
	for (int i = 0; i < dimM; i++)
		for (int j = 0; j < dimM; j++)
			array[i][j] = in.nextDouble();
	int dimV = in.nextInt();
	double[] answer = new double[dimV];
	for (int i = 0; i < dimV; i++)
		answer[i] = in.nextDouble();
	double[] vector = new double[dimV];
	for (int i = 0; i < dimV; i++)
		vector[i] = answer[i];
	Matrix matr = new Matrix (array, dimM);
	Matrix matr1 = new Matrix (array, dimM);
	System.out.println("Solution:");
	for (int i = 0; i < dimV; i++)
		System.out.print(matr.gaussianMethod(answer)[i] + "	");
	System.out.println();
	System.out.println("Residual:");
	for (int i = 0; i < dimV; i++)
		System.out.print(matr1.residual(answer, vector)[i] + " ");
	System.out.println();
	//matr.gaussianMethod(answer).out();
	}
	catch (IllegalArgumentException exc)
	{
		System.out.println(exc.getMessage());
	}
	catch (FileNotFoundException exc)
	{
		System.out.println(exc.getMessage());
	}
	catch (NoSuchElementException exc)
	{
		System.out.println("Can't find element");
	}
}

}

