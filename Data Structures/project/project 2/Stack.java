package project2;

class Stack {
 private int count = 0; //number of elements in the stack
 private int top = -1; //top element of the stack.
 //top == -1 if the stack is empty
 private int MAXSIZE = 1000; //Physical size of the stack
 private char [ ] array = new char [MAXSIZE];
 //constructor
 Stack( ) 
 {
	 
 }
 //inspectors
 public boolean stackEmpty() {
 //Returns true if the stack is empty. Otherwise returns false.
	 return top == -1;
 }
 public char stackTop() {
 //Returns the top element of the stack
	 return array[top];
 }
 public int stackCount() {
 //Returns the number of elements in the stack
	 return count;
 }
 public String toString() {
 //Returns the elements of the stack with the following format:
 //< E1 E2 E3 ... En> where E1 is at the bottom of the stack
 //and En is at the top of the stack.
	 String temp = "< ";
	 for (int i = 0; i <= top; i++)
	 {
		 temp = temp + " " + array[i];
	 }
	 temp = temp + " >";
	 return temp;
 }
/* public String printCharStack() {
 //Returns the elements of the stack with the following format:
 //< E1 E2 E3 ... En> where E1 is at the bottom of the stack
 //and En is at the top of the stack.
 //The elements are printed to the returning string as chars.

 }*/
 //modifiers
 public void stackPush(char element) {
 //Pushes element to the top of the stack.
 //Assumes that we will not run out of space in the stack.
	 top++;
	 count++;
	 array[top] = element;
 }
 
 public char stackPop() {
 //Pops out the top element of the stack.
 //Returns true if the operation was successful.
 //Returns false otherwise.
		/*if (stackEmpty())
		{
			return false;
		}
		else
		{
			System.out.println(array[top]);
			count--;
			top--;
			return true;
		} this is for boolean stackpop() but i dont know why this function would be a boolean it dumb im changing to char*/
		count--;
		top--;
		return array[top+1];
 }
 //im adding a remove to
 public void stackRemove()
 {
	 count--;
	 top--;
 }
}