import java.net.*;
import java.io.*;
import java.util.Random;
public class server
{
	public static void main(String[] args) {
		try {
			String[] word = {
			"Good Job!",
			"Thank you!",
			"Are you alright?",
			"Nice Dude!",
			"Nice work!"}; 
			ServerSocket sock = new ServerSocket(6013);
			/* now listen for connections */
			while (true) {
				Socket client = sock.accept();
				PrintWriter pout = new
				PrintWriter(client.getOutputStream(), true);
				/* write the Date to the socket */
				Random r=new Random();
        		int randomN=r.nextInt(word.length);
				pout.println(word[randomN]);
				/* close the socket and resume */
				/* listening for connections */
				client.close();
			}
		}
		catch (IOException ioe) {
			System.err.println(ioe);
		}
	}
}
