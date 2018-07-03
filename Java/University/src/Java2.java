import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;


public class Java2 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			if (args.length!=1)
				throw new IllegalArgumentException ("Not 1 argument!");
			TreeMap <Character, Integer> myTable = new TreeMap <Character, Integer>();
				for (int i=0; i<args[0].length(); i++)
				{
					if (myTable.containsKey(args[0].charAt(i)))
					{
						int keyValue = myTable.get(args[0].charAt(i));
						myTable.put(args[0].charAt(i), keyValue+1);
					}
					else
						myTable.put(args[0].charAt(i), 1);
					
				}
			while (myTable.size()!=0)
			{
				System.out.println(myTable.firstKey()+"	"+myTable.get(myTable.firstKey()));
				myTable.remove(myTable.firstKey());
			}
		}
		catch (IllegalArgumentException exc)
		{	
			System.out.println(exc.getMessage());
		}
	}

}
