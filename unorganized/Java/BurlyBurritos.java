// BurlyBurritos.java
// Finn Raae
// 2/21/17
// displays a menu to the customer which allows them to place an order consisting of one or more items
 
 import java.util.Scanner;
 class  BurlyBurritos
 {
     public static void main(String[] args) 
     {
         Scanner input=new Scanner(System.in);
         double Total_Price = 0;//order price
         //price of all itmes
         final double TACO_PRICE = 3.39;
         final double ENCHILADA_PRICE = 4.59;
         final double BURRITO_PRICE = 5.79;
         final double End = 0.0; // to end order
         // this is how many tacos, enchiladas, and burritos are purchased
         int Tacos = 0;
         int Enchiladas = 0;
         int Burritos = 0;
 
         boolean check=false;
         do{
         //output
         System.out.println("Welcome to Burly Burritos!");
         System.out.println("Please enter an item to order, or 0 to complete your order.");
         System.out.println("Enter 1 to order a taco for $3.39");
         System.out.println("Enter 2 to order an enchilada for $4.59");
         System.out.println("Enter 3 to order a burrito for $5.79");
 
         //menu
         System.out.print("Order: ");
         int choice=input.nextInt();
 
             switch(choice){
             
                 case 1:
                     Total_Price += TACO_PRICE;
                     Tacos++;
                 break;
                 
                 case 2:
                     Total_Price += ENCHILADA_PRICE;
                     Enchiladas++;
                 break;
                 
                 case 3:
                     Total_Price += BURRITO_PRICE;
                     Burritos++;
                 break;
                 
                 case 0:
                 check = true;
                 break;
             }
         }
         while(!check);
               System.out.println("Your order is complete!");
               System.out.println("You have ordered\n   "+Tacos+" tacos\n   "+Enchiladas+" enchiladas\n   "+Burritos+" burritos");
               System.out.println("Your total cost is $"+Total_Price);
 
     }
 }