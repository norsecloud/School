import java.io.*;
import java.util.*;
import java.io.PrintWriter;

public class ReadFileLineByLine 
{
   public static void main(String[] args) 
   { 
     
      String line;
      try { 
         //open file for reading the calculated formulas "formulas.txt"
         Scanner read = new Scanner(new File("formulas.txt"));          
         // read one line at a time   
         while(read.hasNextLine()) {      
            line = read.nextLine();
      
            System.out.println("read <" + line + ">"); // Display message to commandline
            //tokenizer
            StringTokenizer tooken = new StringTokenizer(line);
            // Declare ArrayList of for storing tokenized formula from String line
            String [] form = new String [3];
            
            form[0] = tooken.nextToken(); 
            form[1] = tooken.nextToken(); 
            form[2] = tooken.nextToken(); 
            double result = 0; // The variable to store result of the operation

            // Determine the operator and calculate value of the result
            //turn string into double
            double var1 = Double.parseDouble(form[0]);
            double var2 = Double.parseDouble(form[2]);
            //find what to do to those var
            //if statements to see what math thingy to do
            if(form[1].equals("*"))
            {
               result = var1 * var2;
            }
            else if(form[1].equals("/"))
            {
               result = var1 / var2;
            }
            else if(form[1].equals("+"))
            {
               result = var1 + var2;
            }
            else if(form[1].equals("-"))
            {
               result = var1 - var2;
            }
            
            //output
            System.out.println(form[0] + ' ' + form[1] + ' ' + 
            form[2] + " = " + result); // Display result to command line

            // Write result to file
            //open file for storing the calculated formulas "results.txt"
            FileWriter fw = new FileWriter("result.txt", true);//apends result.txt
            //PrintWriter pw = new PrintWriter(writ);
            BufferedWriter bw = new BufferedWriter(fw);
            //pw.println(form[0] + " "+ form[1] +" " + form[2] + " +" + result + "\");
            //pw.close();
            bw.write(line + " = " + result); //write
            bw.newLine();//new line
            bw.close();//closes the file
          }//end while 
          read.close();
      }//end try 
      catch (FileNotFoundException e) 
      { 
         e.printStackTrace();
      }//end catch 
      catch (NumberFormatException e) 
      { 
         e.printStackTrace();
      }//end catch
      catch (IOException e)
      {
         e.printStackTrace();
      }
      
   }//end main 
}//end class
