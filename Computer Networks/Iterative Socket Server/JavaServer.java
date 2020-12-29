/*
Finn Raae
Kate Wooley
10/21/20
Computer Networks - Iterative Socket Server
Server Side
*/

import java.net.ServerSocket;
import java.net.Socket;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;
import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;

public class JavaServer implements Runnable{
	//variables
	private ServerSocket serverSocket = null;
	private int port;
	private boolean dead = false;
	private Thread curThread = null;
	
	public JavaServer(int port) {
		this.port = port;
	}

	public void run(){

		synchronized(this){
			this.curThread = Thread.currentThread();
		}
		//open socket
		try {
			this.serverSocket = new ServerSocket(this.port);
		} catch (IOException e) {
			throw new RuntimeException("Cannot open on this port", e);
		}

		while(!this.dead) {

			Socket clientSocket = null;
			try {

				clientSocket = this.serverSocket.accept();
				System.out.println("client connected") ;

			} catch (IOException e) {

				if(this.dead) {
					System.out.println("Server Stopped because it didnt connect to client.") ;
					return;
				}
				throw new RuntimeException("Error accepting client connection", e);
			}
			try {

				clientRequest(clientSocket);

			} catch (Exception e) {
				throw new RuntimeException("Error processing request", e);
			}
		}

		System.out.println("Server Stopped.");
	}

	private void clientRequest(Socket socket) throws Exception {
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
			this.serverSocket.close();
			this.dead = true;
		}
		else {
			out.writeUTF("Please enter a Valid Command.");					//output
			out.flush();
		}

		//close everything
		out.close();
		in.close();
		System.out.println("client closed\n");
	}

	
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);  							// Create a Scanner object
		System.out.println("Please Enter Port Number: ");
		int portNum = Integer.parseInt(scan.nextLine());					// port number variable
		System.out.println("waiting for client on port number: " + portNum);
		JavaServer server = new JavaServer(portNum);
		new Thread(server).start();

	}
}
