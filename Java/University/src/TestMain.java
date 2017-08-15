import java.util.*;
import java.io.*;

public class TestMain {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws EmptyContainerException {
		try
		{
			Scanner scan = new Scanner (new File("in.txt"));
			int mySize = scan.nextInt();
			TreeContainer<ForestTree> cont = new TreeContainer<ForestTree>();
			int i1;
			int i3;
			double d2;
			String s1 = new String();
			String s2 = new String();
			FruitTree tree = new FruitTree("Tree1", 100, "type1", 20, 23.0);
			ForestTree tree2 = new ForestTree("Tree1", 100, "type1", 20, 23);
			//System.out.println(cont.countEqual(tree2));
			for (int i = 0; i < mySize; i++)
			{
				s1 = scan.next();
				i1 = scan.nextInt();
				s2 = scan.next();
				i3 = scan.nextInt();
				d2 = scan.nextDouble();
				cont.add(new ForestTree(s1, i1, s2, i3, d2));
			}	
			Scanner scan2 = new Scanner (new File("in2.txt"));
			int mySize2 = scan2.nextInt();
			TreeContainer<FruitTree> cont2 = new TreeContainer<FruitTree>();
			for (int i = 0; i < mySize2; i++)
			{
				s1 = scan2.next();
				i1 = scan2.nextInt();
				s2 = scan2.next();
				i3 = scan2.nextInt();
				d2 = scan2.nextDouble();
				cont2.add(new FruitTree(s1, i1, s2, i3, d2));
			}
		//	FruitTree tree = new FruitTree("Tree1", 100, "type1", 20, 23.0);
			//ForestTree tree2 = new ForestTree("Tree1", 100, "type1", 20, 23);
			System.out.println("Output1:");
			cont.out();
			System.out.println("Output2:");
			cont2.out();
			System.out.println("Min1:");
			System.out.println(cont.findMin().toString());
			System.out.println("Min2:");
			System.out.println(cont2.findMin().toString());
			System.out.println("Count1:");
			System.out.println(cont.countEqual(tree2));
			System.out.println("Count2:");
			System.out.println(cont2.countEqual(tree));
			System.out.println("Search1:");
			System.out.println(cont.search(tree2));
			System.out.println("Search2");
			System.out.println(cont2.search(tree));
		}
		catch (FileNotFoundException exc)
		{
			System.out.println("File does not exist!");
		}
		catch (NoSuchElementException exc)
		{
			System.out.println("Please, check your input file!");
		}
		catch (EmptyContainerException exc)
		{
			System.out.println(exc.getMessage());
		}
		catch (Exception exc)
		{
			System.out.println(exc.getClass().toString());
		}
		catch (Error err) {
			System.out.println(err.getClass().toString());
		}
		// TODO Auto-generated method stub

	}

}
