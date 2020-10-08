//Finn Raae
//2/8/19
//COT3035
//question 3: This program returns the location of the largest element in a two-dimensional array
import java.util.Scanner;
public class LargetElement 
{//start prog
//start methods
   public static int[] locateLargest(double[][] a) 
   {//finds largest number in a double 2d array
   double largest = a[0][0];                       //place holder for current largest element in array default set to array[0][0]
   int[] tempArray = new int[2];                   //array to hold location of largest element
   for(int i = 0; i < a.length; i++)               
      {//start while
         for(int j = 0; j < a[i].length; j++)
         {//start while
            if (a[i][j] > largest) 
            {//start if
               largest = a[i][j];
               tempArray[0] = i;
               tempArray[1] = j;
            }//end if
         }//end while
      }//end while
      return tempArray;
   }//end locateLargest   
   public static void printArray(double [][] array)
   {//prints array
      for(int i = 0; i < array.length; i++)
      {
         for(int j = 0; j < array[i].length; j++)
         {
            System.out.printf("%.0f ", array[i][j]);
         }
         System.out.println();
      }
   }//end printArray didnt need this for the hw but made it while doing this anyway
   //end methods
   
   public static void main(String[] args) 
   {//start main
   Scanner input = new Scanner(System.in);   //scanner
   //variables
   int sizeX;    //size of array pos 1
   int sizeY;    //size of array pos 2 
   int[] outArray = new int[2];                 //array of location of largest element
   
   //input
   System.out.print("Enter the number of rows and columns of the array: ");
   sizeX = input.nextInt();
   sizeY = input.nextInt();
   double[][] inpArray = new double[sizeX][sizeY];    //array of user inpuet
   
   
   System.out.println("Enter the array: ");
   for (int i = 0; i < inpArray.length; i++)          //loop for filling array
   {//start while
      for (int j = 0; j < inpArray[i].length; j++)
      {//start whike
        inpArray[i][j] = input.nextInt();
      }//end while
   }//end while
   
   //calc
   outArray = locateLargest(inpArray);      
   
   //output
   System.out.printf("The location of the largest element is at (%d, %d)", outArray[0], outArray[1]);
   
   }//end main
}//end prog
