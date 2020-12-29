//Finn Raae
//11/11/2020
//Operating Systems - Programming assignment #2
//Bankers algorithm

import java.io.*;
import java.util.*;

public class BankersAlg
{
	//variables
	static int numberOfProcess;
	static int numberOfResources;

	public static void main(String args[]) throws IOException {
		//var
		Scanner scan = new Scanner(System.in);
		ArrayList<String> safeSEQ = new ArrayList<String>();
		ArrayList<Integer> unSafeSEQ = new ArrayList<Integer>();

		//		input
		System.out.println("enter number of processes: ");
		numberOfProcess = scan.nextInt();
		System.out.println("enter number of resources: ");
		numberOfResources = scan.nextInt();
		//create matrixes
		int allocation[][] = new int[numberOfProcess][numberOfResources];
        int maximum[][] = new int[numberOfProcess][numberOfResources];
        int need[][] = new int[numberOfProcess][numberOfResources];
        int available[] = new int[numberOfResources];
        //fill matrixes
        System.out.println("Enter Allocation's Matrix: ");
        for(int i = 0; i<numberOfProcess ; i++){
            for(int j = 0; j<numberOfResources; j++){
                allocation[i][j] = scan.nextInt();
            }
        }
        System.out.println("Enter Maximum's Matrix: ");
        for(int i = 0; i<numberOfProcess ; i++){
            for(int j = 0; j<numberOfResources; j++){
                maximum[i][j] = scan.nextInt();
            }
        }
        System.out.println("Enter Available's Matrix: ");
        for(int i = 0; i<numberOfResources ; i++){
                available[i] = scan.nextInt();
        }
        //end input

		//fill up unSafeSEQ
		for(int i = 0; i < numberOfProcess; i++) {
			unSafeSEQ.add(i);
		}
		//create need matrix
		for (int i = 0; i < numberOfProcess; i++) {
			for (int j = 0; j < numberOfResources; j++) {
				need[i][j] = maximum[i][j] - allocation[i][j];
			}
		}
		//print matrixes
		System.out.println("Allocation Matrix:");
		print2dArray(allocation);
		System.out.println("Maximum Matrix:");
		print2dArray(maximum);
		System.out.println("Need Matrix:");
		print2dArray(need);


		//banker algorithm
		if (bankersAlg(need, allocation, available, safeSEQ, unSafeSEQ)) {
			System.out.print("\nThe Sequence is Safe.\nSafe Sequence: ");
			for(int i=0; i < safeSEQ.size(); i++){
				System.out.print(safeSEQ.get(i) + " ");
			}//end for
		}//end if
		else {
			System.out.print("\nThe Sequence is not Safe.\nUnsafe Sequence: ");
			for(int i=0; i < unSafeSEQ.size(); i++){
				System.out.print(unSafeSEQ.get(i) + " ");
			}//end for
		}//end else
	}//end main


	//functions
	//prints
	static void print2dArray(int[][] x) {
		for (int i = 0; i < x.length; i++) {
			for (int j = 0; j < x[i].length; j++) {
				System.out.print(x[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();
	}
	static void print1Row2dArray(int[][] x, int i) {
		for (int j = 0; j < x[i].length; j++) {
			System.out.print(x[i][j] + " ");
		}
	}

	static void print1dArray(int[] available, int i) {
		for (int j = 0; j < available.length; j++) {
			System.out.print(available[j] + " ");
		}
	}
	//end prints
	//math
	static int[] updateAvailable(int[] available, int[][] allocation, int i) {
		System.out.print("New Available: ");
		print1Row2dArray(allocation, i);
		System.out.print(" + ");
		print1dArray(available, i);
		//add 2 together
		System.out.print(" = ");
		for (int j = 0; j < available.length; j++) {
			available[j] = allocation[i][j] + available[j]; 
			System.out.print(available[j] + " ");
		}
		System.out.println("");
		return available;
	}//end update available
	static boolean bankersAlg(int[][] need, int[][] allocation, int[] available, ArrayList<String> safeSEQ, ArrayList<Integer> unSafeSEQ) {
		System.out.println("Bankers Algorithm:");
		int breakLoop = numberOfProcess * 2;									//break loop variable
		int counter = 0;														//counter to see if stuck in loop
		while (!unSafeSEQ.isEmpty()) {											//while unsafeSEQ is not empty
			if (counter == breakLoop) {											// if stuck in loop
				return false;
			}
			counter++;															//update break loop counter
			boolean work = true;												//variable if
			int currentP = unSafeSEQ.get(0);
			//			System.out.println(currentP);
			for (int j = 0; j < numberOfResources; j++) {						//check if any need number is greater than available
				if (need[currentP][j] > available[j]) {
					work = false;
				}//end if
			}//end for
			//print stuff
			System.out.print("P"+currentP+": ");
			print1Row2dArray(need, currentP);
			System.out.print(" <= ");
			print1dArray(available, currentP);
			System.out.print(" = " + work + "\n");

			if (work == true) {
				unSafeSEQ.remove(0);
				safeSEQ.add("P"+currentP);
				available = updateAvailable(available, allocation, currentP);
			}//end if
			else {
				unSafeSEQ.remove(0);
				unSafeSEQ.add(currentP);
			}//end else
		}//end for 
		return true;
	}//end bankersAlg
}

