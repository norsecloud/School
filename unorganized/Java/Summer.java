//Summer.java
//F. Raae
//3/5/2017
//prompts for numeric values and displays their sums
 
import java.util.Scanner; 
public class Summer
{//program start
   public static void main(String[] args)
   {
      final double MINDOUBLE = 1.0;
      final double MAXDOUBLE = 20.0;
      final int    MININT = 10;
      final int    MAXINT = 20;
             
      Scanner in = new Scanner(System.in);
         
      // show the result of promptAndSum for doubles
      System.out.printf("The sum of your values is %.2f\n", promptAndSum(in, MINDOUBLE, MAXDOUBLE));
      // show the result of promptAndSum for ints
      System.out.printf("The sum of your values is %d\n", promptAndSum(in, MININT, MAXINT)); 
   }
     
   public static double promptAndSum(Scanner in, double min, double max)
   {//double module
      final String STR_PROMPTANDSUM = "Please enter a floating point value between " +min + " and " + max + ":";
      final String STR_PROMPTANDSUMS = "Please enter another floating point number in the same range: " +min + " and " + max + ":";
                 
      double d =  0.0;
      double i =  0.0;
                
      while (d < min || d > max && i < min || i > max)
      {//while loop
                      
         System.out.print(STR_PROMPTANDSUM);
         d = in.nextDouble();
                                           
         System.out.print(STR_PROMPTANDSUMS);
         i = in.nextDouble();
                      
                      
      }//end while loop
      double s = d + i;
      return s;
   }//end double module
       
   public static int promptAndSum(Scanner in, int min, int max)
   {//int overload
      final String STR_PROMPTANDSUM = "Please enter an integer between " + min + " and " + max + ": ";
      final String STR_PROMPTANDSUMS = "Please enter another integer in the same range: "+ min + " and " + max + ":";
                  
      int i = 0;
      int d = 0;     
         
      while (d < min || d > max && i < min || i > max )
      {//while loop
         System.out.print(STR_PROMPTANDSUM);
         d = in.nextInt();
                                           
         System.out.print(STR_PROMPTANDSUMS);
         i = in.nextInt();
      }//end while loop
      int s = d + i;//calculation
      return s;
    }//end int module
}//end program