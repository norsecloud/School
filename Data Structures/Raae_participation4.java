import java.util.ArrayList;
import java.util.Arrays;

//Finn Raae
//5/23/19
//
//class participation #3

public class participation3 
{
	//#1
	public static <E> ArrayList <E> removeDuplicates(ArrayList<E> list) 
	{
		int x = 0; //counter for seeing if in nonDAL
		ArrayList<E> nonDAL = new ArrayList<E>(); //nonDAL = non-duplicate array list
		for (int i = 0; i < list.size(); i++)
		{//this loop goes through input list 
			for (int j = 0; j < nonDAL.size(); j++)
			{//make a loop that goes that sees if inputList[i] is in nonDAL				
				if ( list.get(i) == nonDAL.get(j))
				{//if inputList[i] is in nonDAL x++
					x++;
				}
			}//end for
			if (x > 0)
			{//add inputList[i] into nonDAL
				nonDAL.add(list.get(i));
			}//end if
			x = 0;
		}//end for
		
		return nonDAL;		//return statement
	}//end public ArrayList<E> nonDuplicateList(Array inputList)
	
	//#2
	public static <E extends Comparable<E>> E max(E[] list)
	{
		E max = list[0];
		for (int i = 0; i < list.length; i++)
		{
			if(list[i].compareTo(max) > 0)
			{
				max = list[i];
			}
		}//end for
		return max;
	}//public static <E extends Comparable<E>> E max(ArrayList<E> list)
	
	
	//#3
	public static <E extends Comparable<E>> E max(ArrayList<E> list)
	{
		E max = list.get(0);
		for (int i = 0; i < list.size(); i++)
		{
			if ((list.get(i).compareTo(max) > 0))				//Fix this line
			{
				max = list.get(i);
			}//end if
		}//end for
		return max;
	}//public static <E extends Comparable<E>> E max(ArrayList<E> list)
	
	//#4
	//recursive method that displays an int value reversely on the console
	public static void reverseDisplay(int value)
	{
		if (value < 10)
		{
			System.out.println(value);		//print last number
			return;							//leave recursion
		}//end if 
		else
		{
			System.out.print(value % 10);  //only shows the last number
			reverseDisplay(value/10); 		//recursion without last number
		}//end else
		
	}// end public static void reverseDisplay(int value)
	
	//#5
	//recursive method that displays a string reversely on the console
	public static void reverseDisplay(String value)
	{
		if (value.length() == 0 )
		{
			System.out.println(value.substring(value.length()));	//print last char
			return ;												//leave recursion
		}//end if
		else
		{
			System.out.print(value.substring(value.length()-1));	//print outs last number in string
			reverseDisplay(value.substring(0, value.length() - 1));	//recursion without last string
		}//end else
		
	}//end public static void reverseDisplay(String value)
	
	//#6
	//recursive method that computes the sum of the digits in an integer
	public static int sumDigits(int n)
	{
		int lastNum = (n%10);			//the last number in n
		int otherNums = (n/10);			//all the numbers except the last one
		if (otherNums == 0)
		{
			return n;					//leave recursion
		}//end if 
		else
		{
			return sumDigits(otherNums) + lastNum; 		//recursion adds last number 
		}//end else
	}//end public static int sumDigits(long n)



}//end public class participation3
