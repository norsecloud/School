class Circle1 extends GeometricObject1 implements Comparable
{ 
   protected double radius;

   // Default constructor
   public Circle1() {
      this(1.0, "white", 1.0);
   }

   // Construct circle with specified radius
   public Circle1(double radius) {
      super("white", 1.0);
      this.radius = radius;
   }

   // Construct a circle with specified radius, weight, and color
   public Circle1(double radius, String color, double weight) {
      super(color, weight);
      this.radius = radius;
   }

   // Getter method for radius
   public double getRadius() {
      return radius;
   }

   // Setter method for radius
   public void setRadius(double radius) {
      this.radius = radius;
   }

   // Implement the findArea method defined in GeometricObject
   public double findArea() {
      return radius * radius * Math.PI;
   }
   
   // Implement the findPerimeter method defined in GeometricObject
   public double findPerimeter() {
      return 2*radius*Math.PI;
   }

   // Override the equals() method defined in the Object class
   public boolean equals(Circle1 circle) {
      return this.radius == circle.getRadius();
   }
   // Override the toString() method defined in the Object class
   public String toString() {
      return "Circle radius = " + radius;
   }

   // Implement the compareTo method defined in Comparable
   public int compareTo(Object o) 
   {
      return Double.compare(radius, ((Circle1)o).radius);
   }

   public static Circle1 max(Comparable o1, Comparable o2) 
   {
      Circle1 c1 = ((Circle1)o1);
      Circle1 c2 = ((Circle1)o2);
      if ((c1.compareTo(c2) > 0))
      {
         return c1;
      }
      else 
      {
         return c2;
      }
   }
}//end class
