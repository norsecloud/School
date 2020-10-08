//Finn Raae
//6/28/19
//data structures
//counts the amount of times a word appears in a string
import java.util.*;
import java.util.Map.Entry;

public class WordsInAscending 
{
	public static void main(String[] args) 
	{
		// Set text in a string
		String text = "Good morning. Have a good class. " +
		"Have a good visit. Have fun!";
		// Create a TreeMap to hold words as key and count as value
		Map<String, Integer> map = new TreeMap<>();
		String[] words = text.split("[ \n\t\r.,;:!?(){]");
		for (int i = 0; i < words.length; i++) 
		{//loop through words
			String key = words[i].toLowerCase();
			if (key.length() > 0) 
			{
				if (!map.containsKey(key)) 
				{//if not in map add it
					map.put(key, 1);
				}//end if 
				else 
				{//if not in 
					int value = map.get(key);
					value++;
					map.put(key, value);
				}//end else 
			}//end if
		}//end for
		// Get all entries into a set
		Set<Map.Entry<String, Integer>> entrySet = map.entrySet();
		//make arrayList
		ArrayList<WordOccurrence> list = new ArrayList<>();
		//cycle through map
		for (Map.Entry<String, Integer> entry : map.entrySet())
			//add to list
			list.add(new WordOccurrence(entry.getKey(), entry.getValue()));
			
		//sort in ascending order
		Collections.sort(list, Collections.reverseOrder());
		//output
		System.out.println(list);
	}//end main
}//end public class WordsInAscending 	