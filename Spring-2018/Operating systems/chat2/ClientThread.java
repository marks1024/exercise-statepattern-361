/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
/**
 *
 * @author zuldyz
 */
public class ClientThread implements Runnable{
    private Socket csock = null;
    private String name;
    private String send;
    private String rec;
    private boolean isRunning;
    //int clID = -1;
    //    boolean isRunning = true;
    public ClientThread(Socket sock) {
        csock = sock;
        //name = myName;
        //clID = id;
    }
    public void run(){
        try{
            BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));
            DataOutputStream outToServer = new DataOutputStream(csock.getOutputStream());
            BufferedReader inFromServer = new BufferedReader(new InputStreamReader(csock.getInputStream()));
            
            while(true){
                //System.out.println("Enter something: ");
                send = inFromUser.readLine();
                outToServer.writeBytes(send + '\n');
                rec= inFromServer.readLine();
                System.out.println("FROM SERVER: " + rec);
                //              if(rec.equals("String's length: " + 0)){
                //                  csock.close();
                //                  break;
                //              }
            }
        }catch(IOException e){
            
        }
        
    }
}
