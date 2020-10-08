// GeometricObject.java
// Implements a Geometric Object class

import java.util.Date;

public class GeometricObject
{
    private String color = "no color";
    private boolean filled;
    private Date dateCreated;
    
    public GeometricObject()
    {
        dateCreated = new Date();
    }
    
    public GeometricObject(String color, boolean filled)
    {
        this();
        this.color = color;
        this.filled = filled;
    }
    
    public String getColor()
    {
        return this.color;
    }
    
    public void setColor(String color)
    {
        this.color = color;
    }
    
    
    public boolean isFilled()
    {
        return this.filled;
    }
    
    public void setFilled(boolean filled)
    {
        this.filled = filled;
    }
    
    public Date getDateCreated()
    {
        return this.dateCreated;
    }
    
    public String toString()
    {
        return "created " + dateCreated + ", color " + color +
                (filled ? ", filled\n" : ", not filled\n");
    }
}