import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

//Finn Raae
// 9/9/2020
//Operating Systems - Assignment 1
//Write a program in Java which creates producer and consumer threads. The
//producer should “produce” by setting the elements of an array of integers to
//FULL. The consumer should “consume” by setting the elements of an array of
//integers to EMPTY.

public class ProducerConsumerMultiThread {

	public static void main(String[] args) {
		//variables
		List<Integer> array = new ArrayList<Integer>();
		Thread prodThread = new Thread(new Producer(array));
		Thread consThread = new Thread(new Consumer(array));
		
		//run threads
		prodThread.start();
		consThread.start();
	}

}

class Producer implements Runnable{//produces numbers to fill array
	//variables
	List<Integer> array = null;		//array that will be filled and emptied
	final int SIZE = 10;			//size of array
	private int i = 1; 				//add variable
	
	//constructor	
	public Producer(List<Integer> Array) {
		super();
		this.array = Array;
	}

	@Override
	public void run() {
		while(true) {
			try {
				produce(i++);			//call produce
			}catch(InterruptedException exception) {
				
			}
		}	
	}
	
	public void produce(int x) throws InterruptedException {
		
		synchronized (array) {
			while(array.size() == SIZE){ //while full
				System.out.println(Arrays.toString(array.toArray()));
				System.out.println("Array is Full: Start Consume");
				array.wait();
			}
		}
		
		synchronized (array) { //when not full
			System.out.println("Produced the element: " + x);
			array.add(x);
			Thread.sleep(500);		//wait so its not super fast
			array.notify();
		}
		
	}
}
class Consumer implements Runnable{//produces numbers to fill array
	//variables
//	int[] arr = null;
	List<Integer> array = null;		//array that will be filled and emptied

	//constructor
	public Consumer(List<Integer> Array) {
		super();
		this.array = Array;
	}

	@Override
	public void run() {
		while(true) {
			try {
				consume();			//call consume
			}catch(InterruptedException exception) {
				
			}
		}
		
	}
	
	public void consume() throws InterruptedException {
		
		synchronized (array) {
			while(array.isEmpty()){ //while empty
				System.out.println(Arrays.toString(array.toArray()));
				System.out.println("Array is Empty: Start Produce");
				array.wait();
			}
		}
		
		synchronized (array) { //when not full
			Thread.sleep(500);
			System.out.println("Consume the element: " + array.remove(0));
			array.notify();
		}
		
	}
}