//Finn Raae
//6/28/19
//data structures
//counts the occurrence of numbers in a string that ends in 0
import java.util.*;
public class CountOccurenceOfNumbers 
{
	public static void main(String[] args) 
	{
		//Variables
		Scanner scan = new Scanner(System.in);
		ArrayList<Integer> highestKeys;
		//input
		System.out.println("Enter a bunch of numbers: ");
		String numInp = scan.nextLine();
		
		//calc
		Map<Integer, Integer> numOccurs = countOccurenceOfNumbers(numInp);
		highestKeys = highestCount(numOccurs);
		//output
		System.out.println("Numbers that occured the most are: " + highestKeys);
		scan.close();
	}
	
	
	public static Map<Integer, Integer> countOccurenceOfNumbers(String numInp)
	{
		Map<Integer, Integer> numOccurs = new HashMap<Integer, Integer>();
		String temp = "";
		int x;
		for (int i = 0; i < numInp.length(); i++)
		{//loop through string
			if (numInp.charAt(i) == ' ')
			{// when meets a space puts number in map
				x  = Integer.parseInt(temp);
				Integer count = numOccurs.get(x);
				if (numOccurs.get(x) == null)
					numOccurs.put(x, 1);
				else
					numOccurs.put(x, ++count);
				temp = "";
			}//end if
			else if (temp == " 0")
			{//break the loop when it hits 0
				break;
			}
			else
			{//makes string to put into map
				temp = temp + numInp.charAt(i);
			}//end else
		}//end loop
		return numOccurs;
	}//end 	public static Map<Integer, Integer> countOccurenceOfNumbers(String numInp)
	
	public static ArrayList<Integer> highestCount(Map<Integer, Integer> numOccurs)
	{
		int highest = 0;	//highest variable
		ArrayList<Integer> temp = new ArrayList<Integer>();
		
		for(Map.Entry<Integer, Integer> keys : numOccurs.entrySet())
		{//cycle through map
			 if (keys.getValue() >  highest)
			 {//if find a higher value clear the array and put in in array
				 highest = keys.getValue();
				 temp.clear();
				 temp.add(keys.getKey());
			 }//end if
			 else if (keys.getValue() == highest)
			 {// if finds equal value put it into array
				 temp.add(keys.getKey());
			 }//end else if
		}//end for
		return temp;
	}//end 	public static ArrayList highestCount(Map<Integer, Integer> numOccurs)

}
