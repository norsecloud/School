class Triangle extends GeometricObject 
{
   //variables
   double side1 = 1;
   double side2 = 1;
   double side3 = 1;
   
   //constructors
   public Triangle()
   {//default
      super();
   }
   
   public Triangle(double s1, double s2, double s3)
   {//3-arg constructor
      super();
      side1 = s1;
      side2 = s2;
      side3 = s3;
   }
   
   //get and set functions
   public double getSide1()
   {
      return side1;
   }
   public double getSide2()
   {
      return side2;
   }
   public double getSide3()
   {
      return side3;
   }
   public void setSide1(double s1)
   {
      this.side1 = s1;
   }
   public void setSide2(double s2)
   {
      this.side2 = s2;
   }
   public void setSide3(double s3)
   {
      this.side3 = s3;
   }
   
   //other functions
   public double getArea()
   {
      double s = (side1+side2+side3)/2;   //heron's formula
      double a = Math.sqrt(s*(s-side1)*(s-side2)*(s-side3));   //more heron's
      return a;
   }//end getArea()
   
   public double getPerimeter()
   {
      return side1 + side2 + side3;
   }//end getPerimeter()
   
   public String toString()
   {
      return "Triangle: side1 = " + side1 + " side2 = " + side2 + " side3 = " + side3;
   }//end toString()  
   
}//end class