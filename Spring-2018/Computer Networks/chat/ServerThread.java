/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.net.*;
import java.io.*;
import java.util.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author zuldyz
 */
public class ServerThread extends Thread {

    private Server serv = null;
    private Socket csock = null;
    private int socketId = -1;
    private DataInputStream from = null;
    private DataOutputStream to = null;
    private String username = null;
    private int group = -1;

    public ServerThread(Server serv, Socket csock) {
        super();
        this.serv = serv;
        this.csock = csock;
        socketId = csock.getPort();
    
    }

    public boolean send(String message) {
        try {
            to.writeUTF(message);
            to.flush();
        } catch (IOException ex) {
            System.out.println("Client is unreachable!");
            serv.remove(socketId);
            stop();
            return false;
        }
        return true;
    }

    public int getID() {
        return socketId;
    }
    
     public String getUsername() {
        return username;
    }
     
      public int getGroup() {
        return group;
    }
     
      public void setUsername(String name){
        username = name;
    }
      
        public void setGroup(int groupNum){
        group = groupNum;
    }

    public void run() {
        System.out.println("Hello from thread: " + socketId);
        while (true) {
            try {
            serv.handleClients(socketId, from.readUTF());

            } catch (IOException ex) {
                System.out.println(ex.getMessage());
                serv.remove(socketId);
                stop();
            }
        }
    }

    public void openConnection() throws IOException {

        from = new DataInputStream(new BufferedInputStream(csock.getInputStream()));
        to = new DataOutputStream(new BufferedOutputStream(csock.getOutputStream()));

    }

    public void close() throws IOException {
        if (csock != null) {
            csock.close();
        }
        if (from != null) {
            from.close();
        }
        if (to != null) {
            to.close();
        }
    }
}
