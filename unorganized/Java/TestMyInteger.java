public class TestMyInteger {
 public static void main(String[] args) 
 {
 MyInteger n1 = new MyInteger(5);
 System.out.println("n1 is even? " + n1.isEven());
 System.out.println("n1 is prime? " + n1.isPrime());
 System.out.println("15 is prime? " + MyInteger.isPrime(15));
 System.out.println("15 is even? " + MyInteger.isEven(15));

 MyInteger n2 = new MyInteger(24);
 System.out.println("n2 is odd? " + n2.isOdd());
 System.out.println("45 is odd? " + MyInteger.isOdd(45));
 System.out.println("n1 is equal to n2? " + n1.equals(n2));
 System.out.println("n1 is equal to 5? " + n1.equals(5));
 System.out.println("n2 is even? " + MyInteger.isEven(n2));
 System.out.println("n2 is odd? " + MyInteger.isOdd(n2));
 System.out.println("n2 is prime? " + MyInteger.isPrime(n2));
 MyInteger n3 = new MyInteger(-5);
 System.out.println("n3 is Prime? " + n3.isPrime()); // True
 MyInteger n4 = new MyInteger(-24);
 System.out.println("n4 is even? " + n4.isEven()); // True
 MyInteger n5 = new MyInteger(-15);
 System.out.println("n5 is odd? " + n4.isOdd()); // True
}
}