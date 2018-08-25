/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
//package sockettcp;

import java.io.*;
import java.net.*;

class TCPClient {

    public static void main(String argv[]) throws Exception
    {
        String send;
        String rec;

        BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));

        Socket clientSocket = new Socket("localhost", 6788);
        DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
        BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

        while(true){
              System.out.println("Enter something: ");
              send = inFromUser.readLine();
              outToServer.writeBytes(send + '\n');
              rec= inFromServer.readLine();
              System.out.println("FROM SERVER: " + rec);
              if(rec.equals("String's length: " + 0)){
                  clientSocket.close();
                  break;
              }
           }
         

    }
}
