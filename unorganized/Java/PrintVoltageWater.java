//Finn Raae
//2/6/19
//COT3035
//question 1: This program prints out a table of the temperature and the corresponding voltage as it moves through the water
public class PrintVoltageWater 
{//start program   
   public static void main(String[] args)
   {//start main
      // variables
      //constants
      final double R0 = 50;   //for Resistor variable
      final double K0 = 0.5;  //for Resistor variable
      final double Rs = 75;   //in Ohms resistor located on device
      final double Vs = 20;   //in Volts located on device
      
      double temp = 00;       //temperature
      double resistor = 0;    //R0 + K0 * temp;
      double voltageM = 0;    //Voltmeter displays value of the voltage across the sensor
   
      //output
      System.out.println("\tT\t\tVM");
      System.out.println("_________________");
          while ( temp <= 100)
          {//start while
            //calculations
            resistor =  R0 + K0 * temp;
            voltageM = (resistor/(Rs + resistor))*Vs ;
            if (temp != 100)
            {
               System.out.printf("\t%.0f\t\t%.2f\n",temp,voltageM); 
            }//end if
            else
            {
               System.out.printf("\t%.0f\t%.2f\n",temp,voltageM);
            }//end else
            temp = temp + 10; //count increase
          }//end while
   }//end main
}//end program