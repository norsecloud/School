/*
Finn Raae
Kate Wooley
10/21/20
Computer Networks - Iterative Socket Server
Client Side
*/


import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.Timer;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.TimeUnit;

public class JavaClient {

	public static void main(String[] args) {
		ArrayList<Long> allTimes = new ArrayList<Long>(); // Create an ArrayList object

		try {
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			System.out.println("IP address: ");
			String addressStr = reader.readLine();
			InetAddress address = InetAddress.getByName(addressStr);  //localhost for server use "139.62.210.153"

			System.out.println("Port Number: ");
			String portNumStr = reader.readLine();
			int portNum = Integer.parseInt(portNumStr);

			String userCmd = "";
			while(!userCmd.toUpperCase().contains("7") && !userCmd.toUpperCase().contains("EXIT")) {
				
				System.out.println("1. Date and Time\t2. Uptime\t3. Memory Use\t4. Netstat\t5. Current Users\t6. Running Processes\t7. Exit");
				//save user command
				userCmd = reader.readLine();
				int userRNum = 1;
				System.out.println();
				if(!userCmd.toUpperCase().contains("7") && !userCmd.toUpperCase().contains("EXIT")) {
					
					System.out.println("How many requests?");
					//convert str to int
					userRNum = Integer.parseInt(reader.readLine());
				}
				System.out.println();
				int count = 0;
				CountDownLatch cdl = new CountDownLatch(userRNum);
				while(count < userRNum) {
					new ClientConnection(cdl, portNum, address, userCmd, allTimes).start();
					count++;
				}
				cdl.await();
				//calc total time
				if (!userCmd.contains("7") && !userCmd.contains("EXIT")) {
					long totalTime = 0;
					for (int i = 0; i < allTimes.size(); i++) {
						totalTime = totalTime + (allTimes.get(i));
					}
					//printout total and avg times
					System.out.println("The total duration of all the threads is: " + totalTime + " microseconds.");
					totalTime = totalTime/allTimes.size();
					System.out.println("The avg duration of all the threads is: " + totalTime + " microseconds.\n");
					allTimes.clear(); //clear arraylist
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		} 
	}
}


class ClientConnection extends Thread{
	private String userInput;
	private CountDownLatch cdl;
	private InetAddress address;
	private int portNum;
	public ArrayList<Long> allTimes;

	public ClientConnection(CountDownLatch cdl, int portNum, InetAddress address,  String userCmd, ArrayList<Long> allTimes) {
		this.userInput = userCmd;
		this.cdl = cdl;
		this.portNum = portNum;
		this.address = address;
		this.allTimes = allTimes;
	}

	public void run() {
		try {
			Socket socket = new Socket(address, portNum);

			//output and input stream variables
			OutputStream output = socket.getOutputStream();
			InputStream input = socket.getInputStream();

			DataInputStream in = new DataInputStream(new BufferedInputStream(input));		   
			DataOutputStream writer = new DataOutputStream(output);

			long startTime = System.nanoTime(); //timer start

			//send request to server
			String userInputU = userInput.toUpperCase();
			if (userInput.contains("1") || userInputU.contains("DATE")) {
				writer.writeUTF("1");
				writer.flush();
			}
			else if (userInput.contains("2") || userInputU.contains("UPTIME")) {
				writer.writeUTF("2");
				writer.flush();
			}
			else if (userInput.contains("3") || userInputU.contains("MEMORY")) {
				writer.writeUTF("3");
				writer.flush();
			}
			else if (userInput.contains("4") || userInputU.contains("NETSTAT")) {
				writer.writeUTF("4");
				writer.flush();
			}
			else if (userInput.contains("5") || userInputU.contains("CURRENT") || userInputU.contains("USERS")) {
				writer.writeUTF("5");
				writer.flush();
			}
			else if (userInput.contains("6") || userInputU.contains("RUNNING") || userInputU.contains("PROCESS")) {
				writer.writeUTF("6");
				writer.flush();
			}
			else if (userInput.contains("7") || userInputU.contains("EXIT")) {
				writer.writeUTF("7");
				writer.flush();
			}
			else
			{
				writer.writeUTF(userInput);
				writer.flush();
			}
			//read data from server
			String fromServer = null;
			do {
				fromServer = in.readUTF();
				System.out.println(fromServer);
			} while (in.available() > 0) ;
			
			if (!userInput.contains("7") && !userInputU.contains("EXIT")) {	//only print elapsed time if not exiting
				long endTime = System.nanoTime();		//timer end
				long duration = (endTime - startTime)/1000; //divide  by 1000 to turn into microseconds  
				System.out.println("Elapsed Time: " + duration + " microseconds.\n");
				allTimes.add(duration);
			}

			//close everything
			cdl.countDown();
			output.close();
			input.close();
			writer.close();
			in.close();
			socket.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}