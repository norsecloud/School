//Finn Raae
//5/16/19
//cop3530
//prog that checks if two arrays are identical 
import java.util.Arrays;
import java.util.Scanner;

public class equals
{

	public static void main(String[] args) 
	{
		//variables
		int listLength1;
		int listLength2;
		boolean isIdentical = false;
		//scanner variable
		Scanner input = new Scanner(System.in);
		
		//array creation list1
		System.out.print("Enter length for list 1: ");
		listLength1 = input.nextInt();
		int[] list1= new int[listLength1];
		
		System.out.print("Enter List 1: ");
		for (int i = 0; i < list1.length; i++)
		{
			list1[i] = input.nextInt();
		}
		
		//array creation list2
		System.out.print("Enter length for list 2: ");
		listLength2 = input.nextInt();
		int[] list2= new int[listLength2];
				
		System.out.print("Enter List 2: ");
		for (int i = 0; i <list2.length; i++)
		{
			list2[i] = input.nextInt();
		}
		
		//identical checker
		isIdentical = equals(list1, list2);
		
		//output
		if (isIdentical == true)
		{
			System.out.println("Two list are identical");
		}
		else
		{
			System.out.println("Two list are not identical");
		}
	}
	
	public static boolean equals(int[] list1, int[] list2)
	{
		boolean isIdentical = true;
		if (list1.length == list2.length)
		{
			//sort list 1 and 2
			Arrays.sort(list1);
			Arrays.sort(list2);
			
			for (int i = 0; i <list1.length; i++)
				{
					if (list1[i] != list2[i])	//identical check location
					{
						isIdentical = false;
						break;					//breaks loop
					}//end if
				}//end for
		}//end if
		else
		{
			isIdentical = false;
		}//end else
		return isIdentical;
	}// end public static boolean equals(int[] list1, int[] list2)

}//end prog
