
import java.io.*;
import java.net.*;
import java.util.Date;

class TCPServer {

    public static void main(String argv[]) throws Exception {
        String clientSentence;
        String responseMessage;

        ServerSocket welcomeSocket = new ServerSocket(2509);

        Socket connectionSocket = welcomeSocket.accept();
        BufferedReader inFromClient
                = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));

        DataOutputStream outToClient
                = new DataOutputStream(connectionSocket.getOutputStream());

        clientSentence = inFromClient.readLine();
        System.out.println("from client: " + clientSentence);
        String strs[] = clientSentence.split(" ");
        for (int i = 0; i < strs.length; i++) {
            //System.out.println(strs[i]);
        }
        String fileName = strs[1].substring(1);

        String format[] = fileName.split("\\.");
        //System.out.println(format[1]); //to see format

        //File fileToCheck = new File(new File("/Users/zuldyz/NetBeansProjects/TestServer/src/"), fileName);
        File fileToCheck = new File(new File("./SharedFiles"),fileName);
        boolean check = fileToCheck.exists();
        //System.out.println(check);
        
        URL location = TCPServer.class.getProtectionDomain().getCodeSource().getLocation();
        System.out.println("My loc" + location.getFile());
        ///ArrayList<String> results = new ArrayList<>();
        //        URL pathForFiles = ClassLoader.getSystemResource("TCPServer.java");
        File[] files = new File("./SharedFiles").listFiles();
        ////If this pathname does not denote a directory, then listFiles() returns null.
        //
        for (File file : files) {
            if (file.isFile()) {
                //results.add(file.getName());
                System.out.println(file.getName()+"\n");
            }
        }
        System.out.println(check);

        if (check == true) {
            FileInputStream fileStream = new FileInputStream(fileToCheck);

            byte fileBytes[] = new byte[(int) fileToCheck.length()];
            fileStream.read(fileBytes);

            long timestamp = fileToCheck.lastModified();
            Date now = new Date();

            responseMessage = strs[2] + " 200 OK";

            responseMessage = responseMessage + "\r\n"; // other header fields,
            responseMessage = responseMessage + "Date: " + now + "\r\n";
            if (format[1].equals("jpeg")) {
                responseMessage = responseMessage + "Content-Type: imagejpeg\r\n";
            } else {
                responseMessage = responseMessage + "Content-Type: text/html; charset=utf-8\r\n";
            }
            responseMessage = responseMessage + "Content-Length: " + fileToCheck.length()+ "\r\n";
            responseMessage = responseMessage + "Connection: close\r\n"; // we can't handle persistent
            responseMessage = responseMessage + "Last-Modified: " + new Date(timestamp) + "\r\n"; 
            responseMessage = responseMessage + "\r\n"; // this marks the end of the httpheader
            outToClient.writeBytes(responseMessage);
            //System.out.println(responseMessage);
            outToClient.write(fileBytes);
        } else {
            responseMessage = strs[2] + "404 Not Found";
            responseMessage = responseMessage + "\r\n\r\n";
            responseMessage = responseMessage + "<html><body><h1>404 Not Found</h1></body></html>";

            outToClient.writeBytes(responseMessage);
        }

        connectionSocket.close();
        welcomeSocket.close();
    }
}
