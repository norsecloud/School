// Rectangle.java
// F. Raae
// 4/9/2017
// rectangle class calculate area inherits from GeometricObject 

public class Rectangle extends GeometricObject
{// start rectangle class

      // width member
      private double width = 0.0;
      
      // height member 
      private double height = 0.0;
      
      // constructors
      public Rectangle()
      {
         super();
      }
      
      public Rectangle(double width, double height)
      {
         super();
         this.width = width;
         this.height = height;
      }
      
      public Rectangle(double width, double height, String color, boolean filled)
      {
         super(color, filled);
         this.width = width;
         this.height = height;
      }
      
      // accessors
      public double getWidth()
      {
         return this.width;
      }
      
      public double getHeight()
      {
         return this.height;
      }
      
      // mutators
      public void setWidth(double width)
      {
         this.width = width;
      }
      
      public void setHeight(double height)
      {
         this.height = height;
      }
      // calculated value
      public double getArea()
      {
         return this.width * this.height;
      }
      
      public double getPerimeter()
      {
         return 2 * (this.width + this.height);
      }
      
      // output String
      public String toString()
      {
         return "Rectangle with width " +  this.width + " " +
         "height" + " " + this.height + 
                 " " + super.toString();
      }//end rectangle class
}            
        

