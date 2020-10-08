//Finn Raae
//6/19/19
//COP3530
//tree implementation
import java.util.Scanner;

public class Project3 
{
	
	 public static void main(String args[]) 
	 {
		 int inp;
		 //tree set up
		 Node N55 = new Node();
		 Node N60 = new Node();
		 Node N20 = new Node();
		 Node N85 = new Node();
		 Node N70 = new Node();
		 Node N10 = new Node();
		 Node N30 = new Node();
		 Node N15 = new Node();
		 Node N75 = new Node();
		 Node N50 = new Node();
		 Node N65 = new Node();
		 Node N25 = new Node();
		 Node N80 = new Node();
		 Node N35 = new Node();
		 Node N5 = new Node();
		 
		 N55.setData(55);
		 N60.setData(60);
		 N20.setData(20);
		 N85.setData(85);
		 N70.setData(70);
		 N10.setData(10);
		 N30.setData(30);
		 N15.setData(15);
		 N75.setData(75);
		 N50.setData(50);
		 N65.setData(65);
		 N25.setData(25);
		 N80.setData(80);
		 N35.setData(35);
		 N5.setData(5);
		 
		 N55.setLeft(N60);
		 N55.setRight(N20);
		 N60.setLeft(N85);
		 N60.setRight(N70);
		 N85.setLeft(N15);
		 N85.setRight(N75);
		 N70.setLeft(N50);
		 N70.setRight(N65);
		 N20.setLeft(N10);
		 N20.setRight(N30);
		 N10.setLeft(N25);
		 N10.setRight(N80);
		 N30.setLeft(N35);
		 N30.setRight(N5);
		 
		 
		//scanner create
		 Scanner scan = new Scanner(System.in);
		 //tree create
		 Tree T1 = new Tree();
		 
		 T1.root = N55;
		 //testing
		 //count.()
		 System.out.println("");
		 System.out.println("Checking function count()");
		 System.out.println("---------------------------");
		 System.out.println("The size of the tree num is: " + T1.count());
		 System.out.println("The size of the tree N50 is: " + T1.countNodes(N50));
		 System.out.println("");
		 
		 //height
		 System.out.println("");
		 System.out.println("Checking function height()");
		 System.out.println("---------------------------");
		 System.out.println("The height of the tree num is: " + T1.height());
		 System.out.println("The height of the tree N50 is: " + T1.heightNodes(N50));
		 System.out.println("");
		 
		//leaves()
		 System.out.println("");
		 System.out.println("Checking function leaves()");
		 System.out.println("---------------------------");
		 System.out.println("The leaves of the binary tree num is: : ");
		 T1.leaves();
		 System.out.println("");
		 
		//internal()
		 System.out.println("");
		 System.out.println("Checking internal()");
		 System.out.println("---------------------------");
		 System.out.println("The internal nodes of the binary tree num are: ");
		 T1.internal();
		 System.out.println("");
		 
		//printLDR(), printDLR(), printLRD
		 System.out.println("");
		 System.out.println("Checking functions printLDR(), printDLR(), and printLRD()");
		 System.out.println("---------------------------");
		 System.out.println("Enter 1 (in-order traversal of T1");
		 System.out.println("      2 (pre-order traversal of T1");
		 System.out.println("      3 (post-order traversal of T1");
		 inp = scan.nextInt();
		 if(inp == 1)
		 {
			 T1.printLDR();
		 }
		 if(inp == 2)
		 {
			 T1.printDLR();
		 }
		 if(inp == 3)
		 {
			 T1.printLRD();
		 }
		 System.out.println("");
		 
		//search()
		 System.out.println("");
		 System.out.println("Checking function search()");
		 System.out.println("---------------------------");
		 System.out.print("Enter element to search: ");
		 inp = scan.nextInt();
		 if(T1.search(inp) == true)
		 {
			 System.out.println(inp + " belongs in the binary tree T1");
		 }
		 else
			 System.out.println(inp + " doesn't belong in the binary tree T1");

		 System.out.println("");
		 
		//path()
		 System.out.println("");
		 System.out.println("Checking function path()");
		 System.out.println("---------------------------");
		 System.out.print("Enter element to find path for: ");
		 inp = scan.nextInt();
		 System.out.println("The path from the root of T1 to node " + inp + " is:");
		 T1.path(inp);
		 System.out.println("");
		 
		//descendents()
		 System.out.println("");
		 System.out.println("Checking function descendents()");
		 System.out.println("---------------------------");
		 System.out.println("Enter element to find descendents for: ");
		 inp = scan.nextInt();
		 System.out.println("the descendents of " + inp + " in T1 are: ");
		 T1.descendents(inp);
		 System.out.println("");
		 
		 //copy()
		 System.out.println("");
		 System.out.println("Checking function copy()");
		 System.out.println("---------------------------");
		 System.out.println("Let T2 be a copy of T1");
		 Tree T2 = new Tree();
		 T2 = T1.copy();
		 System.out.println("The nodes of binary tree T2 in  in-order traversal are: ");
		 T2.printLDR();
		 System.out.println("");
		 
		 
		 //T4
		 Tree T4 = new Tree();
		 T4.root = T1.copyNodes(N30);
		 //equal
		 System.out.println("");
		 System.out.println("Checking function equal()");
		 System.out.println("---------------------------");
		 
		 System.out.println("Let data part of node 80 be 80 in binary tree T1");
		 if(T1.equal(T2) == true)
		 {
			 System.out.println("Binary trees T1 and T2 are equal");
		 }
		 else
			 System.out.println("Binary tree T1 and T2 are not equal");
		 System.out.println("Let data part of node 80 be 90 in binary tree T1");
		 N80.setData(90);
		 if(T1.equal(T2) == true)
		 {
			 System.out.println("Binary trees T1 and T2 are equal");
		 }
		 else
			 System.out.println("Binary tree T1 and T2 are not equal");
		 System.out.println("");
		 
		 //this comment section is to make a third tree to test the equal because 
		 //the above way of doing it does not work but the below way will show them not equal
		//tree 3
//		 Node tN55 = new Node();
//		 Node tN60 = new Node();
//		 Node tN20 = new Node();
//		 Node tN85 = new Node();
//		 Node tN70 = new Node();
//		 Node tN10 = new Node();
//		 Node tN30 = new Node();
//		 Node tN15 = new Node();
//		 Node tN75 = new Node();
//		 Node tN50 = new Node();
//		 Node tN65 = new Node();
//		 Node tN25 = new Node();
//		 Node tN80 = new Node();
//		 Node tN35 = new Node();
//		 Node tN5 = new Node();
//		 
//		 tN55.setData(55);
//		 tN60.setData(60);
//		 tN20.setData(20);
//		 tN85.setData(85);
//		 tN70.setData(70);
//		 tN10.setData(10);
//		 tN30.setData(30);
//		 tN15.setData(15);
//		 tN75.setData(75);
//		 tN50.setData(50);
//		 tN65.setData(65);
//		 tN25.setData(25);
//		 tN80.setData(80);
//		 tN35.setData(35);
//		 tN5.setData(5);
//		 
//		 tN55.setLeft(tN60);
//		 tN55.setRight(tN20);
//		 tN60.setLeft(tN85);
//		 tN60.setRight(tN70);
//		 tN85.setLeft(tN15);
//		 tN85.setRight(tN75);
//		 tN70.setLeft(tN50);
//		 tN70.setRight(tN65);
//		 tN20.setLeft(tN10);
//		 tN20.setRight(tN30);
//		 tN10.setLeft(tN25);
//		 tN10.setRight(tN80);
//		 tN30.setLeft(tN35);
//		 tN30.setRight(tN5);
//		 
//		 Tree T3 = new Tree();
//		 T3.root = tN55;
//		 
//		//equal
//		 System.out.println("");
//		 System.out.println("Checking function equal()");
//		 System.out.println("---------------------------");
//		 N80.setData(90);
//		 System.out.println("Let data part of node 80 be 80 in binary tree T1");
//		 if(T1.equal(T3) == true)
//		 {
//			 System.out.println("Binary trees T1 and T3 are equal");
//		 }
//		 else
//			 System.out.println("Binary tree T1 and T3 are not equal");
//		 System.out.println("Let data part of node 80 be 90 in binary tree T1");
//		 N80.setData(90);
//		 if(T1.equal(T3) == true)
//		 {
//			 System.out.println("Binary trees T1 and T3 are equal");
//		 }
//		 else
//			 System.out.println("Binary tree T1 and T3 are not equal");
//		 System.out.println("");
	 }//end main
}//end public class Project3
