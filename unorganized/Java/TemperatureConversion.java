// COP2551lab2.java
//F. Raae, M.Pike, C.Smith 
//1/23/17
//Second lab for COP2551, Temperature converter

import java.util.Scanner;

public class TemperatureConversion{
   public static void main(String[]args){
      // declare
  
      final double DIVISION = 5.0 / 9.0;
      final int F_CONSTANT = 32;
    
      //input
      Scanner input = new Scanner(System.in);
      System.out.print("Please enter an integer for the fahrenheit temperature: ");
      int f = input.nextInt();
   
      //calculations
      double c = ((f - F_CONSTANT) * DIVISION);
   
      //output
   
      System.out.printf("You entered %d degrees fahrenheit; this is %.2f degrees celsius\n", f, c);
   }
}