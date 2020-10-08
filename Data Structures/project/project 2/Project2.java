package project2;

import java.util.Scanner;
class Project2 {
	 public static void main(String args[]) 
	 {
		 String infixExp; //infix expression to be read
		 String postfixExp; //postfix expression to be computed
		 Stack S = new Stack(); //stack for converting the infix expression
		 //to postfix notation
		 Scanner scan = new Scanner(System.in);
		 
		 //input
		 System.out.print("Enter the infix expression: ");
		 infixExp = scan.nextLine();
		 
		//calc
		postfixExp = in2Post(infixExp, S);
		 
		 //output
		 System.out.println("The expression in postfix notation is "+ postfixExp);
		 
	 }//end main
	 
	 
	 public static String in2Post(String input, Stack operators)
	 {
		 String temp = "";
		 for (int i = 0; i <= input.length() -1; i++)
		 {//loop through the string
			 if (input.charAt(i) == '*' || input.charAt(i) == '/')
			 {//pushes * and / onto stack
				 operators.stackPush(input.charAt(i));
				 operators.toString();
			 }//end if
			 
			 else if (input.charAt(i) == '+')
			 {//
				 if(operators.stackEmpty() == true || operators.stackTop() == '+' || operators.stackTop() == '(')
				 {
					 operators.stackPush(input.charAt(i));
				 }//end if
				 
				 else
				 {
					 while (operators.stackEmpty() != true)
					 {//empty the stack out
						 temp = temp + operators.stackPop();
					 }//end while
					 operators.stackPush(input.charAt(i));
				 }//end else
			 }//end else if
			 else if (input.charAt(i) == '(')
			 {
				 operators.stackPush(input.charAt(i));
			 }
			 else if (input.charAt(i) == ')')
			 {
				 while(operators.stackTop() != '(')
				 {//pop stack until get to (
					 temp = temp + operators.stackPop();
				 }
				 operators.stackRemove();//remove ( from stack
			 }
			 else 
			 {//pushes all the individual char to string
				 temp = temp + input.charAt(i);
			 }//end else
			 
			 System.out.println(input.charAt(i) + ":\t" + temp + "\t" + operators.toString());
		 }//end for loop
		 while (operators.stackEmpty() != true)
		 {//empty the stack out after the string is done son
			 temp = temp + operators.stackPop();
			 System.out.println("\t" + temp + "\t" + operators.toString());
		 }//end while

		 return temp;
	 }//end  public String in2Post(String input, Stack operators)
}//end class Project2
