//Finn Raae
//6/28/19
//data structures
//reads a text file and gets the words and counts them
import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class CountWordsInTextFile 
{
	public static void main(String[] args) throws FileNotFoundException 
	{
		//variables
		Map<String, Integer> map = new TreeMap<>();
		ArrayList<String> words = new ArrayList<String>();
		
		if (args.length != 1)
		{
			System.out.println("invalid filename");
			System.exit(1);
		}//end if
		//file make and see if its real
		File file = new File(args[0]);
		//File file = new File("text.txt");		//will test with regular opening file
		if(!file.exists())
		{//if can't find file  do this
			System.out.println("The file does not exist.");
			System.exit(1);
		}//end if
		try 
		(//input
			Scanner input = new Scanner(file);
		) 
		{
			while (input.hasNext()) 
			{// make array list of words in text file
				words.add(input.next());
			}//end while
		}	
		//count 	
		countWordsInTextFile(map, words);
			
		// Get all entries into a set
		Set<Map.Entry<String, Integer>> entrySet = map.entrySet();

		// Get key and value from each entry
		for (Map.Entry<String, Integer> entry: entrySet)
			//output
			System.out.println(entry.getKey() + "\t\t" + entry.getValue());
	}//end main
	
	//methods
	private static void countWordsInTextFile(Map<String, Integer> inpMap, ArrayList<String> words)
	{
		for (int i = 0; i < words.size(); i++)
		{//loop though words array
			//make word all lower case
			String key = words.get(i).toLowerCase();
			if (key.length() > 0) 
			{
				if (!inpMap.containsKey(key)) 
				{// if not in map put it in
					inpMap.put(key, 1);
				}//end if
				else 
				{//if in there add +1 to the count = x
					int x = inpMap.get(key);
					inpMap.put(key, ++x);
				}//end else
			}//end if
		}//end for
	}//end 	private static void sort(Map<String, Integer> inpMap, String[] words)
}//end program