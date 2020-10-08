// Circle.java
// Implements a circle class which inherits from GeometricObject

public class Circle extends GeometricObject
{
    private double radius = 0.0;
    
    public Circle()
    {
        super();
    }
    
    public Circle(double radius)
    {
        super();
        this.radius = radius;
    }
    
    public Circle(double radius, String color, boolean filled)
    {
        super(color, filled);
        this.radius = radius;
    }
    
    public double getRadius()
    {
        return this.radius;
    }
    
    public void setRadius(double radius)
    {
        this.radius = radius;
    }
    
    public double getArea()
    {
        return this.radius * this.radius * Math.PI;
    }
    
    public double getPerimeter()
    {
        return 2 * this.radius * Math.PI;
    }
    
    public double getDiameter()
    {
        return 2 * this.radius;
    }
    
    public String toString()
    {
        return "Circle with radius " + radius +
                 " " + super.toString();
    }
}