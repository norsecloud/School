//Finn Raae
//5/16/19
//cop3530
//prog that merges two arrays and sorts them

import java.util.Arrays;
import java.util.Scanner;

public class arrayMerger 
{
	public static void main(String[] args) 
	{
		//variables
		int listLength1;
		int listLength2;
		
		int[] mergedArray;
		
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
			
		//merge the lists
		 mergedArray = merge(list1, list2);
			
		//output
		System.out.println(Arrays.toString(mergedArray));
	}//end public static void main(String[] args) 
	
	
	//start methods
	public static int[] merge (int[] list1, int[] list2)
	{
		int[] mergedArray = new int[list1.length + list2.length];
		int x = 0; //this variable is for the list2 adding to merged array
		
		//merge list1 into mergedArray
		for (int i = 0; i < list1.length; i++)
		{
			mergedArray[i] = list1[i];
		}// end for
		//merge list2 into mergerdArray
		for (int i = list1.length; i < list1.length + list2.length; i++)
		{	
			mergedArray[i] = list2[x];
			x++;
		}// end for
		
		//bubble sort cause whatever
		mergedArray = bubbleSort(mergedArray);
		
		return mergedArray;
	}//end public static int[] merge (int[] list1, int[] list2)
	
	public static int[] bubbleSort (int[] list)
	{
		int i,j, temp = 0;
		for (i = 0; i<list.length -1; i++)
		{
			for (j=0;j<list.length -1 -i; j++)
			{
				if (list[j] > list[j+1])
				{
					temp = list[j];
					list[j] = list[j+1];
					list[j+1] = temp;
				}// end if
			}// end for
		}// end for
		return list;
	}//end  public static int[] bubbleSort (int[] list)
}//end prog
