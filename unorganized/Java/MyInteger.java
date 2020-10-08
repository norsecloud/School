class MyInteger 
{
   //variables
   private int value;
   
   //get function
   public int getValue() 
   {
      return value;
   }
   
   //constructor
   public MyInteger(int val) 
   {
      this.value = val;
   }
 
   //other functions
   public boolean isEven() 
   {
      if ((Math.abs(value)%2)==0)
         return true;
      else
         return false;  //end if
   }//end isEven() function

   public boolean isOdd() 
   {
      if ((Math.abs(value)%2)==0)
         return false;
      else
         return true;   //end if
   }//end isOdd() function
   
   public boolean isPrime() 
   {
   //check if n is a multiple of 2 if is not a prime
   if ((value%2==0)) return false;
   //if not, then just check the odds
   for(int i=3;i*i<=value;i+=2) 
      {
      if(value%i==0)
           return false;   //end if
      }//end while
   return true;
   }//end isPrime() function
   
   public static boolean isEven(int n)
   {
      if ((Math.abs(n)%2)==0)
         return true;
      else
         return false;  //end if
   }//end isEven(int) function
   
   public static boolean isOdd(int n) 
   {
      if ((Math.abs(n)%2)==0)
         return false;
      else
         return true;   //end if
   }//end isOdd(int) function
   
   public static boolean isPrime(int n) 
   {
      //check if n is a multiple of 2
      if (n%2==0) return false;           //end if
      //if not, then just check the odds
      for(int i=3;i*i<=n;i+=2) 
      {
         if(n%i==0)
            return false;
      }//end for loop
      return true;
   }//end isPrime(int) function
   
   public static boolean isEven(MyInteger o) 
   {
      if ((Math.abs(o.value)%2)==0)
         return true;
      else
         return false;  //end if
   }//end isEven(Myinteger) function
   
   public static boolean isPrime(MyInteger o) 
   {
      //check if n is a multiple of 2
      if (o.value%2==0) return false;     //end if
      //if not, then just check the odds
      for(int i=3;i*i<=o.value;i+=2) 
      {
          if(o.value%i==0)
              return false;               
      }//end for loop
      return true;
   }//end isPrime(Myinteger) function
   
   public static boolean isOdd(MyInteger o) 
   {
      if ((Math.abs(o.value)%2)==0)
         return false;
      else
         return true;   //end if 
   }//end isOdd(MyInteger) function
   public boolean equals(int anotherNum) 
   {
      if (anotherNum == value)
         return true;
      else
         return false;  //end if
   }//end equals(int) function
   
   public boolean equals(MyInteger o) 
   {
   if (o.value == value)
      return true;
   else
      return false;
   }//end equals(MyInteger) function
   
}//end class
