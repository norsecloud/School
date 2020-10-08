package myPractice;

import java.util.Arrays;

public class Stacks 
{
	private int[] stackArray;
	
	private int stackSize;
	
	private int topOfStack = -1;
	
	void theStack(int size)
	{
		stackSize = size;
		
		stackArray = new int[size];
		
	}
	
	public void push(int input) 
	{
		if(topOfStack + 1 < stackSize)
		{
			topOfStack++;
			
			stackArray[topOfStack] = input;
			
		}
		else System.out.println("Sorry but the Stack is Full");
	}
	public int pop()
	{
		int data;
		topOfStack--;
		data = stackArray[topOfStack];
		stackArray[topOfStack] = null;
		return data;
	}
	public int peek()
	{
		int data;
		data = stackArray[topOfStack];
		return data;
	}
	public boolean isEmpty()
	{
		return topOfStack<=0;
	}
}
