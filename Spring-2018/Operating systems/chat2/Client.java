

/**
 *
 * @author zuldyz
 */
import java.io.*;
import java.net.*;
import java.util.*;

class Client {
    
    public static void main(String argv[]) throws Exception
    {
        
        //        System.out.println("Please, enter your name: ");
        //        Scanner scan = new Scanner(System.in);
        //        String name = scan.nextLine();
        //        scan.close();
        
        Socket clientSocket = new Socket("localhost", 7867);
        Thread.sleep(1000);
        ClientThread serThread = new ClientThread(clientSocket);
        Thread server = new Thread(serThread);
        server.start();
        
        
    }
}
