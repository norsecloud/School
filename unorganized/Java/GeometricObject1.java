abstract class GeometricObject1 {
   protected String color;
   protected double weight;

   // Default construct
   protected GeometricObject1() {
      color = "white";
      weight = 1.0;
   }

   // Construct a geometric object
   protected GeometricObject1(String color, double weight) {
      this.color = color;
      this.weight = weight;
   }

   // Getter method for color
   public String getColor() {
      return color;
   }

   // Setter method for color
   public void setColor(String color) {
      this.color = color;
   }

   // Getter method for weight
   public double getWeight() {
      return weight;
   }

   // Setter method for weight
   public void setWeight(double weight) {
      this.weight = weight;
   }

   //Write code here for Abstract method for area
   public abstract double findArea(); 

   //Write code here Abstract method for perimeter
   public abstract double findPerimeter();
    
}//end class
