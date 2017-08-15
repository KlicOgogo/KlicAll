import java.util.*;

public class TreeContainer<T extends Tree> extends ArrayList<T> {
	
public T findMin() throws EmptyContainerException
{
	/*if (this.isEmpty())
		throw new EmptyContainerException("Container is empty!");
	T min = get(0);
	Iterator<T> i = iterator();
	while (i.hasNext())
	{
		if (min.compareTo(i.next()) > 0)
			min = i.next();
	}
	return min;*/
	return (T)Collections.min(this);
}

public void out() throws EmptyContainerException 
{
	if (this.isEmpty())
		throw new EmptyContainerException("Container is empty!");
	
	Iterator<T> i = iterator();
	while (i.hasNext())
		System.out.println(i.next().toString());
}

public int countEqual(T value) throws EmptyContainerException
{
	if (this.isEmpty())
		throw new EmptyContainerException("Container is empty!");
	int result = 0;
	Iterator<T> i = iterator();
	while (i.hasNext())
	{
		if (i.next().equals(value))
			result++;
	}
	return result;
}


public int search(T value)
{
	Collections.sort(this);
	return Collections.binarySearch((List)this, value);
}

}
