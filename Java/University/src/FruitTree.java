

public class FruitTree extends Tree {

	private int weight;
	public double termin;
	public FruitTree()
	{
		super();
		weight = 0;
		termin = 0;
	}
	
	public FruitTree(String n, int a, String t, int wei, double ter)
	{
		super (n, a, t);
		weight = wei;
		termin = ter;
	}
	public String toString() {
		return (name + " " + age + " " + type + " " + weight + " " + termin + " ");
	}
	
	public boolean equals(Tree tree)
	{
	if (weight == ((FruitTree)tree).weight && age == ((FruitTree)tree).age && termin == ((FruitTree)tree).termin && name.equals(((FruitTree)tree).name) && type.equals(((FruitTree)tree).type))
		return true;
	else
		return false;
	}
}
