//Finn Raae
//5/17/19
//cop3530
//DriverExam Class object
public class DriverExam 
{
	//variables
	private char[] correct = {'B', 'D', 'A', 'A', 'C', 'A', 'B', 'A', 'C', 'D', 'B', 'C', 'D', 'A', 'D', 'C', 'C', 'B', 'D', 'A'};
	private char[] student = new char[20];
	private int [] missed;
	private int numCorrect = 0;
	private int numIncorrect = 0;
	
	//constructor
	public DriverExam(char[] s)
	{
		student = s;
		gradeExam();
		makeMissedArray();
	}
	
	//methods
	private void gradeExam()
	{
		for (int i = 0; i <correct.length; i++)
		{
			if (student[i] == correct[i])	
			{
				numCorrect += 1;
			}//end if
			else
			{
				numIncorrect += 1;
			}//end else
		}//end for
	}//end private void gradeExam()
	
	private void makeMissedArray()
	{
		int count = 0;
		missed = new int[numIncorrect];
		for (int i = 0; i < correct.length; i++)
		{
			if (student[i] != correct[i])
			{
				missed[count] = i+1;
				count++;
			}//end if
		}//end while
	}//end private void makeMissedArray()
	
	public boolean passed()
	{
		if (numCorrect >= 15)
			return true;
		
		else
			return false;
	}//end public boolean passed()
	
	public int totalCorrect()
	{
		return numCorrect;
	}//end public int totalCorrect()
	
	public int totalIncorrect()
	{
		return numIncorrect;
	}//end public int totalIncorrect()
	
	public int[] questionsMissed()
	{
		return missed;
	}//end public int[] questionsMissed()
}//end public class DriverExam 
