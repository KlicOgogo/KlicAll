import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;
import java.util.TreeSet;


public class MatrixMain {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
	    Scanner in = new Scanner(System.in);
        System.out.print("Enter n: ");
        int n = in.nextInt();
        if ( n <= 1 ) {
            System.err.println("Invalid n value (require: n > 1");
            System.exit( 1 );
        }
        int[][] a = new int [n][n];
        Random rnd = new Random();
        rnd.setSeed( System.currentTimeMillis() );
        int max = -n;
        System.out.println("Source values: ");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int temp = rnd.nextInt();
                a[i][j] = temp % (n + 1);
                System.out.print(a[i][j] + "  ");
                if (a[i][j] >= max) {
                    max = a[i][j];
                }
            }
            System.out.println();
        }
        TreeSet<Integer> indI = new TreeSet<Integer>();
        TreeSet<Integer> indJ = new TreeSet<Integer>();
        for (int i = 0; i < n; i++)
        	for (int j = 0; j < n; j++)
        		if (a[i][j] == max)
        		{
        			indJ.add(j);
        			indI.add(i);
        		}
        System.out.println(indJ.toString());
        System.out.println(indI.toString());
        ArrayList<Integer> numbers = new ArrayList<Integer>();
        for (int i = 0; i < n; i++)
        {
        	if (!indI.contains(i))
        		for (int j = 0; j < n; j++)
            	{
            		if (!indJ.contains(j))
            			numbers.add(a[i][j]);
            	}
        }
        	
        int count = 0;
        int[][] result = new int[n - indI.size()][n - indJ.size()];
        for (int i = 0; i < n - indI.size(); i++)
        	for (int j = 0; j < n - indJ.size(); j++)
        	{
        		result[i][j] = numbers.get(count);
        		count++;
        	}
        System.out.println("Result:");
        for (int i = 0; i < n - indI.size(); i++)
        {
        	for (int j = 0; j < n - indJ.size(); j++)
        	{
        		System.out.print(result[i][j] + "  ");
        	}
        	System.out.println();
        }
	}

}
