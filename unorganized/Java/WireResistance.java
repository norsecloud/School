//Finn Raae
//2/6/19
//COT3035
//question 2: This program computes and prints out the resistance of copper and aluminum wire
/*comments
   couldnt get the formula right for some reason i think it is the formula for diameter in computeDiameter 
   or it could be math.pow idk if there is a better way to do exponent 
*/

//imports
import java.util.Scanner;

public class WireResistance 
{//start prog
   //start methods
   public static double computeDiameter(int wireGauge) 
   {//Takes the write gauge and returns the corresponding wire diameter
      double n = wireGauge;
      double diameter = ((0.127 * Math.pow(92,((36-n)/39)))); //math * by 0.0254 for conversion to m from mm and math.pow = 92^((36-n)/39)
      return diameter;
   }//end computeDiameter
   
   public static double computeCopperWireResistance(double length, int wireGauge) 
   {// Takes the length and gauge of a piece of copper wire and returns the resistance of that wire.
      double resistivityC = 1.678 * Math.pow(10, -8); // copper resistivity in ohms m
      double diameter = computeDiameter(wireGauge);
      double resistance = ((4 * resistivityC * length)/(Math.PI * Math.pow(diameter,2)));  //resistance copper formula
      return resistance;
   }// end computeCopperWireResistance
   
      public static double computeAlumWireResistance(double length, int wireGauge)
   {// Takes the length and gauge of a piece of aluminum wire and returns the resistance of that wire. The resistivity
      double resistivityA = 2.82 * Math.pow(10, -8); // aluminum resistivity in ohms m
      double diameter = computeDiameter(wireGauge);
      double resistance = (4 * resistivityA * length)/(Math.PI * Math.pow(diameter,2)); //resistance Alluminum
      return resistance; 
   }//end computeAllumWireResistance
   //end methods

   public static void main(String[] args) 
   {//start main
   //scanner
   Scanner input = new Scanner(System.in);
   //variables
   int wireGauge = 0;      
   double length = 0;
   double resistanceA = 0; //Alluminum Resistance
   double resistanceC = 0; // Copper Resistance
   double diameterA;       //alluminum diameter
   double diameterC;       // copper diameter
   
   //input
   do
   {//start while
      System.out.print("Enter the wire gauge: ");
      wireGauge = input.nextInt();
   }
   while (wireGauge <= 0);
   //end while
   do
   {//start while
      System.out.print("Enter the wire length in inches: ");
      length = input.nextDouble();
   }//end while
   while (length <= 0);
   
   //calculations
   resistanceC = computeCopperWireResistance(length, wireGauge)*(Math.pow(1000,2)/39.320);
   resistanceA = computeAlumWireResistance(length, wireGauge)*(Math.pow(1000,2)/39.320);

   //output
   System.out.printf("The resistance of a %.0f = 65 inch piece of %d = 30 gauge copper wire is %.3f = 0.544 Ohms.\n", length, wireGauge, resistanceC);
   System.out.printf("The resistance of a %.0f = 65 inch piece of  %d = 30 gauge aluminum wire %.3f is 0.914 Ohms.", length, wireGauge, resistanceA);
   // first is my calc second is what calc are suppose to look like
   }//end main
}//end prog
