
public class ForestTree extends Tree {

	private int number;
	public double termin;
	public ForestTree()
	{
		super();
		number = 0;
		termin = 0;
	}
	
	public ForestTree(String n, int a, String t, int num, double ter)
	{
		super (n, a, t);
		number = num;
		termin = ter;
	}
	public String toString() {
		return (name + " " + age + " " + type + " " + number + " " + termin + " ");
	}
	
	public boolean equals(Tree tree)
	{
	if (number == ((ForestTree)tree).number && age == ((ForestTree)tree).age && termin == ((ForestTree)tree).termin && name.equals(((ForestTree)tree).name) && type.equals(((ForestTree)tree).type))
		return true;
	else
		return false;
	}
	
	public int compareTo(Object tree) 
	{
		System.out.println("Forest");
		return ((Tree)this).compareTo(tree);
		//return Treesuper.compareTo(tree);
	}

}
