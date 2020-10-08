//SubstringTester.java
//Finn Raae
//2/11/2017
//see if one string is a sub string of the other

 import java.util.Scanner;
 
 public class SubstringTester 
 {
    public static void main(String[] args) 
    {
    Scanner input = new Scanner(System.in);
    
    //Prompt the user to enter the two strings
    System.out.print("Please enter a string: ");
    String string1 = input.nextLine();
    System.out.print("Please enter another string: ");
    String string2 = input.nextLine(); 
    
    //compare the strings 
    int x =(string1.indexOf(string2));
    
       if (string1.indexOf(string2) >= 0) //if is a substring
       {
          System.out.println(string2 +" is a substring of "+ string1);
       }  
       else {//if not
          System.out.println(string2 +" is not a substring of " + string1);           
            }
            
    }
 }  