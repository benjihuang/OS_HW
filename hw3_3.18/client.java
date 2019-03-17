import java.io.*;
import java.net.*;
import java.util.*;
public class client
{
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		try {	
			
			Socket client = new Socket("127.0.0.1",6013);
   			DataOutputStream out = new DataOutputStream(client.getOutputStream());
   			InputStream in = client.getInputStream();
   			ByteArrayOutputStream buffer = new ByteArrayOutputStream();

   
   			while(true){
	      			String m = sc.nextLine();

	      			byte[] byteMsg = m.getBytes();
	      			String message = new String(byteMsg, "UTF-8");
	     			if(message.equals("-1")){
					client.close();
					break;
			      	} 
			     	else {
					out.write(byteMsg);
				}
				int NR;
				byte[] line = new byte[20000];
				if ((NR = in.read(line, 0, line.length)) != -1){
				      buffer.write(line,0,NR);
				}

				buffer.flush();

				String res = new String(buffer.toByteArray(), "UTF-8");

				System.out.println("Server sent: " + res);
				buffer.reset();
   			 }
		}
		catch (IOException ioe) {
		System.err.println(ioe);
		}
	}
}
