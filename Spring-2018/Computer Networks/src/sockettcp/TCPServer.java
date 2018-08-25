/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package sockettcp;

import java.io.*;
import java.net.*;
import java.util.*;
/**
 *
 * @author zuldyz
 */
class TCPServer{
    
//    public void run(){
//        while(th != NULL){
//            try{
//                ServerSocket welcomeSocket = new ServerSocket(6788);
//            }catch(IOException e){
//                System.out.println(e.getMessage());
//            }
//        }
//
//
//    }
    
    public static void main(String argv[]) throws Exception{
        int id = 0;
        private ClientThread clients[] = new ClientThread[50];
        ServerSocket welcomeSocket = new ServerSocket(6788);
        Thread th = null;
        ClientThread clThread = null;
        while(true){
            try{
                Socket connectionSocket = welcomeSocket.accept();
                clThread = new ClientThread(connectionSocket, id++);
                clThread.start();
            }catch(IOException e){
                System.out.println(e.getMessage());
            }
        }
        
       // welcomeSocket.close();
        
    }
    
}

class ClientThread extends Thread {
    Socket csock;
    int clID = -1;
    boolean isRunning = true;
    
    ClientThread(Socket sock, int id) {
        csock = sock;
        clID = id;
    }

    public void run() {
//        System.out.println("Accepted Client : ID - " + clientID + " : Address - "
//                           + clientSocket.getInetAddress().getHostName());
        try {

            BufferedReader inFromClient =
            new BufferedReader(new InputStreamReader(csock.getInputStream()));
            
            DataOutputStream  outToClient =
            new DataOutputStream(csock.getOutputStream());

            while (isRunning) {
//                String clientCommand = in.readLine();
//                System.out.println("Client Says :" + clientCommand);
//                if (clientCommand.equalsIgnoreCase("quit")) {
//                    running = false;
//                    System.out.print("Stopping client thread for client : " + clientID);
//                } else {
//                    out.println(clientCommand);
//                    out.flush();
//                }
                String clientSend;
                
                //csock.clientID
                
                System.out.println("I received: ");
                clientSend = inFromClient.readLine() + '\n';
                System.out.println(clientSend);
                String strs[] = clientSend.split(" ");
                String username = strs[2].substring(0);
                
                //           length = clientSend.length() - 1;
                System.out.println(username + "\n");
                String greeting = "hi " + username;
                outToClient.writeBytes(greeting + '\n');
                
                if(clientSend.equals("")){
                    //stringLength = "END";
                    //outToClient.writeBytes(stringLength);
                    
                    
                    csock.close();
                    break;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
////package sockettcp;
//
//import java.io.*;
//import java.net.*;
///**
// *
// * @author zuldyz
// */
// class TCPServer {
//
//    public static void main(String argv[]) throws Exception{
//        String clientSend;
//        int length;
//
//        ServerSocket welcomeSocket = new ServerSocket(6788);
//
//
//          Socket connectionSocket = welcomeSocket.accept();
//                BufferedReader inFromClient =
//                    new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
//
//             DataOutputStream  outToClient =
//             new DataOutputStream(connectionSocket.getOutputStream());
//
//        while(true){
//
//
//             System.out.println("I received: ");
//             clientSend = inFromClient.readLine() + '\n';
//             System.out.println(clientSend);
//            String strs[] = clientSend.split(" ");
//            String username = strs[2].substring(0);
//
////           length = clientSend.length() - 1;
//           System.out.println(username + "\n");
//           String greeting = "hi " + username;
//           outToClient.writeBytes(greeting + '\n');
//
//           if(clientSend.equals("")){
//               //stringLength = "END";
//               //outToClient.writeBytes(stringLength);
//
//                 welcomeSocket.close();
//                 connectionSocket.close();
//                 break;
//             }
//
//        }
//
//    }
//
//}

