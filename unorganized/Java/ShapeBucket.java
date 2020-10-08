// ShapeBucket.java
// Store geometric shapes in an ArrayList

import java.util.ArrayList;

public class ShapeBucket
{
    public static void main(String[] args)
    {
        ArrayList<GeometricObject> shapeList = new ArrayList<>();
        
        shapeList.add(new Circle(2, "green", false));
        shapeList.add(new Circle(3, "blue", true));
        shapeList.add(new Rectangle(4,5, "black", false));
        shapeList.add(new Rectangle(6,7, "white", true));
        
        // circle
        for (GeometricObject g: shapeList)
        {
            if (g instanceof Circle)
            {
                System.out.println(g + "Area of circle is " + ((Circle)g).getArea());
            }
       
        // rectangle     
            if (g instanceof Rectangle)
            {  
               System.out.println(g + "Perimeter of rectangle is " + ((Rectangle)g).getPerimeter());  
            
            }
        }
    }           
}

