package myPractice;

public class stackSingleLinkList 
{
	Node head;
	
	static class Node 
	{
		int data;
		Node next;
		
		public node(int data)
		{
			this.data=data;
			next = null;
		}
	}
	
	private int top;
	
	public stackLinkList()
	{
		top = -1;
	}
	
	//stack is empty
	public boolean isEmpty()
	{
		return (top == -1);
	}
	
	public void push(int value)
	{
		//insert at head
		Node temp = new Node(value);
		temp.next = head;
		head = temp;
		top++;
	}
	
	public int pop()
	{
		//delete the head element
		if(head != null)
		{
			Node temp = head;
			head = head.next;
			--top;
		}
		else
			System.out.println("stack is empty");
}
