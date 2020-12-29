/*
Finn Raae
Kate Wooley
11/18/20
Computer Networks - Concurrent Socket Server
Server Side
 */

import java.io.*;
import java.net.*;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

public class MultiThreadedServer {
	public static void main(String[] args) { 
		Scanner scan = new Scanner(System.in);  							// Create a Scanner object
		System.out.println("Please Enter Port Number: ");
		int portNum = Integer.parseInt(scan.nextLine());					// port number variable
		try (ServerSocket serverSocket = new ServerSocket(portNum)) {
			System.out.println("Server is listening on port " + portNum);
			while (true) {
				Socket socket = serverSocket.accept();
				System.out.println("New client connected");
				new ServerThread(socket).start();
			}
		} catch (IOException ex) {
			System.out.println("Server exception: " + ex.getMessage());
			ex.printStackTrace();
		}
	}
}//end MultiThreadedServer class

class ServerThread extends Thread {
	private Socket socket;
	public ServerThread(Socket socket) {//constructor
		this.socket = socket;
	}
	public void run() {
		try {
			String s;
			DataInputStream in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));		   
			DataOutputStream out = new DataOutputStream(socket.getOutputStream());
			String input = in.readUTF();										//input variable
			if (input.equals("1")) {
				Date date = new Date(); // This object contains the current date value
				SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss");			
				s = ("Current Date and Time: " + formatter.format(date));
				out.writeUTF(s);			//output
				out.flush();
			}
			else if (input.equals("2")) {
				Process p = Runtime.getRuntime().exec("uptime");
				BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
				s = stdInput.readLine();
				out.writeUTF(s);				//output
				out.flush();
			}
			else if (input.equals("3")) {
				String ret = "";
				Process p = Runtime.getRuntime().exec("free -m");
				BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
				while ((s = stdInput.readLine()) != null) {
					ret = ret + s + "\n";
				}
				out.writeUTF(ret);				//output
				out.flush();
			}
			else if (input.equals("4")) {
				String ret = "";
				Process p = Runtime.getRuntime().exec("netstat -natp");
				BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
				while ((s = stdInput.readLine()) != null) {
					ret = ret + s + "\n";
				}
				out.writeUTF(ret);				//output
				out.flush();
			}
			else if (input.equals("5")) {
				String ret = "";
				Process p = Runtime.getRuntime().exec("w");
				BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
				while ((s = stdInput.readLine()) != null) {					//read linux terminal
					ret = ret + s + "\n";
				}
				out.writeUTF(ret);											//output
				out.flush();
			}
			else if (input.equals("6")) {
				String ret = "";
				Process p = Runtime.getRuntime().exec("ps");
				BufferedReader stdInput = new BufferedReader(new InputStreamReader(p.getInputStream()));
				while ((s = stdInput.readLine()) != null) {
					ret = ret + s + "\n";
				}
				out.writeUTF(ret);								//output
				out.flush();
			}
			else if (input.equals("7")) {
				out.writeUTF("GoodBye.");						//output

				//closing server
				out.close();
				in.close();
				socket.close();
				this.socket.close();
				//				this.dead = true;
			}
			else {
				out.writeUTF("Please enter a Valid Command.");					//output
				out.flush();
			}

			//close everything
			out.close();
			in.close();
			System.out.println("client closed\n");
		} catch (IOException ex) {
			System.out.println("Server exception: " + ex.getMessage());
			ex.printStackTrace();
		}
	}
}//end serverThread
