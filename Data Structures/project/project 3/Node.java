//Finn Raae
//6/19/19
//COP3530
//Node
public class Node 
{
	//variables
	int data;
	Node left;
	Node right;

	Node() 
	{//constructor
		data = 0;
		left = null;
		right = null;
	}//end Node()
	Node(int datas) 
	{//constructor int parameter
		data = datas;
		left = null;
		right = null;
	}//end Node()

	//getters
	public int getData() 
	{
		return data;
	}

	public Node getLeft() 
	{
		return left;
	}

	public Node getRight() 
	{
		return right;
	}
	
	//setters
	public void setData(int newData) 
	{
	data = newData;
	}

	public void setLeft(Node newLink) 
	{
		left = newLink;
	}

	public void setRight(Node newLink) 
	{
		right = newLink;
	}

}//end public class Node
