public abstract class Tree implements Comparable {

protected int age;
protected String name;
protected String type;

public Tree()
{
	setAge(0);
	setName(new String());
	setType(new String());
}

public Tree(String n, int a, String t)
{
	setAge(a);
	setName(new String(n));
	setType(new String(t));
}

public int compareTo(Object tree)
{
		return name.compareTo(((Tree)tree).name);
	}
	//return name.compareTo(((Tree)tree).name);

public abstract String toString();

public abstract boolean equals(Tree tree);

public String getType() {
	return type;
}

public void setType(String type) {
	this.type = type;
}

public String getName() {
	return name;
}

public void setName(String name) {
	this.name = name;
}

public int getAge() {
	return age;
}

public void setAge(int age) {
	this.age = age;
}

}
