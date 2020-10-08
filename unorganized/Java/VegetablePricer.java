//VegetablePricer.java
//Finn Raae
//2/5/17
//prompts the user for a vegetable from the table of choices shown below. The program will then display the cost per pound for that vegetable

       
import java.util.Scanner;
   
   public class VegetablePricer
   {
      public static void main(String[] args)
      {
         //declarations
         final String STR_ENTERPROMPT = "Please enter a vegetable name. Choices are: \n artichoke \n broccoli \n carrot \n okra \n tomato \n artichoke \n ";
         final String STR_INVALID = " Sorry, that vegetable is not recognized.";
         final String STR_CHOICE = "Your choice => ";
         Scanner input = new Scanner(System.in);
         String vg = "";
         String inVeg = "";
         boolean isValid = true;
                  
         // Prompt the user for vagetable
         System.out.print(STR_ENTERPROMPT);
         inVeg = input.nextLine();
        
         // Use a switch on the input char to show to price of the vegetable
         vg = "";
         switch (inVeg.toLowerCase())
         {         
            case "artichoke": vg = "artichoke: Price per lb. is $2.21"; 
            break;
            case "broccoli": vg = "broccoli: Price per lb. is $2.57";
            break;
            case "carrot": vg = "carrot: Price per lb. is $0.74"; 
            break;
            case "okra": vg = "okra: Price per lb. is $3.21"; 
            break;
            case "tomato": vg = "tomato: Price per lb. is $3.69"; 
            break;
            default:
               isValid = false;
               System.out.println(inVeg + STR_INVALID);
            break;
         }
         
         if (isValid == true)
             System.out.println(STR_CHOICE + inVeg);
             System.out.println(vg);
      }
 }