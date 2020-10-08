package myPractice;

public class runner 
{
	public static void main(String args)
	{
		Queue q = new Queue();
		q.enQueue(5);
		q.enQueue(3);
		q.enQueue(2);
		q.enQueue(1);
		
		q.deQueue();
		
		q.show();
	}
}
