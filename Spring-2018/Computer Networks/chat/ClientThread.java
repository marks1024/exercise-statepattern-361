/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.net.*;
import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author zuldyz
 */
public class ClientThread extends Thread {

    private Client client = null;
    private Socket sock = null;
    private DataInputStream in = null;

    public ClientThread(Client client, Socket sock) {
        this.client = client;
        this.sock = sock;
        open();
        start();

    }

    public void close() {
        try {
            if (in != null) {
                in.close();
            }
        } catch (IOException ioe) {
            System.out.println("Error closing input stream: " + ioe);
        }
    }

    public void open() {
        try {
            in = new DataInputStream(sock.getInputStream());
        } catch (IOException ex) {
            System.out.println("Client is disconnected!!!" + ex.getMessage());
            client.stop();
        }
    }

    public void run() {
        while (true) {
            try {
                client.handleMessages(in.readUTF());
            } catch (IOException ex) {
                System.out.println("Client is disconnected " + ex.getMessage());
                //client.handleMessages("server discon");
                client.stop();
            }
        }
    }

}
