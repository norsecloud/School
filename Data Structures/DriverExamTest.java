//Finn Raae
//5/17/19
//cop3530
//prog that is a driver exam
import java.util.Arrays;
import java.util.Scanner;

public class DriverExamTest 
{
	public static void main(String[] args) 
	{
		//var
		Scanner input = new Scanner(System.in);
		char[] studentAnswers = new char[20];
		int questionCounter = 1;
		//input
		System.out.println("Enter your answers to the exam questions. (Make sure Caps Lock is On)\n");
		
		for (int i = 0; i < 20; i++)
		{
			System.out.print("Question " + questionCounter + ": " );
			studentAnswers[i] = input.next().charAt(0);
			while (studentAnswers[i] != 'A' && studentAnswers[i] != 'B' && studentAnswers[i] != 'C' && studentAnswers[i] != 'D')
			{
				System.out.println("Only accept the letters A, B, C or D as answers.");
				System.out.print(" Question " + questionCounter + ": " );
				studentAnswers[i] = input.next().charAt(0);
			}
			questionCounter++;
		}
		//calc
		DriverExam s1 = new DriverExam(studentAnswers);
		
		//output
		System.out.println("\nCorrect Answers: " + s1.totalCorrect());
		System.out.println("InCorrect Answers: " + s1.totalIncorrect());
		System.out.println(s1.passed() ? "You passed the exam." : "You failed the exam.");
		System.out.println("You missed the following questions:\n" + Arrays.toString(s1.questionsMissed()));
		
	}//end main
}//end prog
