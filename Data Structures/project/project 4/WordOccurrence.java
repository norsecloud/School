//Finn Raae
//6/28/19
//data structures
//Word occurrence node
import java.util.*;
	
	public class WordOccurrence implements Comparable<WordOccurrence> 
	{
		//variables
		String word;
		Integer count;
	
		public WordOccurrence(String word, int count)
		{//constructor
			this.word = word;
			this.count = count;
		}//end 	public WordOccurrence(String word, int count)

		public int compareTo(WordOccurrence o) 
		{//compare to method
			return o.count.compareTo(count);
		}//end public int compareTo(WordOccurrence o) 

		public String toString() 
		{//to make output
			return word + "     " + count;
		}//end 	public String toString() 
	}//end public class WordOccurrence implements Comparable<WordOccurrence> 

	
