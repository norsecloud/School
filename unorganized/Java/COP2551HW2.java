// COP2551HW2.java
//Finn Raae
//1/29/17
//"KitchenConverter" which converts cups to tablespoons using the formula 1 cup = 16 tablespoons.

import java.util.Scanner;

public class COP2551HW2{
   public static void main(String[]args){
      // declare
  
      final int t_constant = 16; //tablespoon constant to
    
      //input
      Scanner input = new Scanner(System.in);
      System.out.println("This program converts cups to tablespoons");
      System.out.print("Please enter the number of cups: ");
      double cups = input.nextDouble();
   
      //calculations
      double tablespoons = (cups * t_constant);
   
      //output
   
      System.out.printf("%.2f cups is %.2f tablespoons\n", cups, tablespoons);
   }
}