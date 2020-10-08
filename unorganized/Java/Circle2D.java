class Circle2D 
{  //variables
   private double x, y;
   private double radius;
  
   //constructors
   public Circle2D() 
   {//default constructor no arg
      this.x = 0;
      this.y = 0;
      this.radius = 1;
   }
  
   public Circle2D(double x, double y, double radius) 
   {//3-variables constructor
     this.x = x;
     this.y = y;
     this.radius = radius;
   }
   
   //get and setters
   public double getX() 
   {
      return x;
   }

   public void setX(double x) 
   {
      this.x = x;
   }

   public double getY() 
   {
      return y;
   }

   public void setY(double y) 
   {
      this.y = y;
   }
  
   public double getRadius() 
   {
      return radius;
   }

   public void setRadius(double radius) 
   {
      this.radius = radius;
   }
  
   public double getPerimeter() 
   {
      return 2 * Math.PI * radius;
   }
  
   public double getArea() 
   {
      return radius * radius * Math.PI;
   }
  
   //functions
   public boolean contains(double x, double y) 
   {
      double distance = distance(x,y,this.x,this.y);
      if (distance <= this.radius)
      {
         return true;
      } 
      else 
      {
         return false;
      }//end if
   }//end contains(double, double)
  
   public boolean contains(Circle2D circle) 
   {    
      double distance = distance(circle.x,circle.y,this.x,this.y);
      if (distance <= Math.abs(this.radius - circle.radius))
      {
         return true;
      } 
      else 
      {
         return false;
      }//end if
   }//end contains(Circle2d)
  
   public boolean overlaps(Circle2D circle) 
   {//sees if circles overlap    
      double distance = distance(circle.x,circle.y,this.x,this.y);
      if (distance  <= this.radius + circle.radius)
      {
         return true;
      }
      else
      {
         return false;
      
      }//end if
   }//end overlaps(Circle2d)
  
   private static double distance(double x1, double y1, double x2, double y2) 
   {//finds distance between 2 points
      double distance = Math.sqrt(((x2-x1)*(x2-x1))+((y2-y1)*(y2-y1)));
      return distance;
   }//end distance(double, double, double, double)
   
}//end class
