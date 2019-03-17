import java.io.*;
import java.net.*;

public class server
{
	public static void main(String[] args) {
		try {
			ServerSocket sock = new ServerSocket(6013);
			System.out.println("Server opened");
			while(true){
	     			Socket client = sock.accept();
				System.out.println("Server: Client connected");
				DataOutputStream out = new DataOutputStream(client.getOutputStream());
				ByteArrayOutputStream buffer = new ByteArrayOutputStream();
				InputStream in = client.getInputStream();
	     
				while(true){
					int NR;
					byte[] line = new byte[20000];

					if ((NR = in.read(line, 0, line.length)) != -1){
						buffer.write(line,0,NR);
					} 
					else if ((NR = in.read(line, 0, line.length)) == -1){
						break;
					}

					buffer.flush();

					byte[] byteMsg = buffer.toByteArray();

					String msg = new String(byteMsg, "UTF-8");

					System.out.println("Client sent: " + msg);
					       
					out.write(byteMsg);
					out.flush();
					buffer.reset();
				} 
				break;
  			}
			sock.close();
		}
		catch (IOException ioe) {
		System.err.println(ioe);
		}
	}
}
