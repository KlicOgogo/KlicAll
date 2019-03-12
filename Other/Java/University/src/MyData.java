import java.util.*;

public class MyData implements Comparable {

private int data1;
private double data2;
private String data3;
private String data4;

public MyData()
{
	data1 = 0;
	data2 = 0;
	data3 = new String("");
	data4 = new String("");
}

public MyData(int d1, double d2, String d3, String d4)
{
	data1 = d1;
	data2 = d2;
	data3 = new String (d3);
	data4 = new String (d4);
}

public MyData(MyData data)
{
	data1 = data.data1;
	data2 = data.data2;
	data3 = new String (data.data3);
	data4 = new String (data.data4);
}

public String toString()
{
	StringBuilder str = new StringBuilder("");
	str.append(data1 + " ");
	str.append(data2 + " ");
	str.append(data3 + " ");
	str.append(data4 + " ");
	return str.toString();
}

public int compareTo(Object data)
{
	int i;
	Random rand = new Random();
	if (data1 > ((MyData)data).data1)
		i = Math.abs(rand.nextInt());
	else if (data1 < ((MyData)data).data1)
		i = -Math.abs(rand.nextInt());
	else
	{
		if (data3.compareTo(((MyData)data).data3) != 0)
			return data3.compareTo(((MyData)data).data3);
		else
			return 0;
	}
	return i;
}

public int getData1()
{
	return data1;
}

public double getData2()
{
	return data2;
}

public String getData3()
{
	return data3;	
}

public String getData4()
{
	return data4;
}

public void setData1(int d1)
{
	data1 = d1;
}

public void setData2(double d2)
{
	data2 = d2;
}

public void setData3(String d3)
{
	data3 = d3;
}

public void setData4(String d4)
{
	data4 = d4;
}

}