/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.net.*;
import java.io.*;
import java.util.*;

/**
 *
 * @author zuldyz
 */
public class Client implements Runnable {

    private Socket mySocket = null;
    private DataOutputStream send = null;
    private DataInputStream input = null;
    private Thread thread = null;
    private ClientThread client = null;

    public Client(String host, int port) {
        try {
            System.out.println("Connecting...");
            mySocket = new Socket(host, port);
            start();
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
        }
    }

    public void run() {
        while (thread != null) {
            try {
                send.writeUTF(input.readLine());
                send.flush();
            } catch (IOException ex) {
                System.out.println(ex.getMessage());
                stop();
            }
        }
    }

    public void handleMessages(String message) {
        if (message.equals("exit")) {
            System.out.println("Bye ...");
            stop();
        } else {
            System.out.println(message);
        }
    }

    public void start() throws IOException {
        input = new DataInputStream(System.in);
        send = new DataOutputStream(mySocket.getOutputStream());
        if (thread == null) {
            client = new ClientThread(this, mySocket);
            thread = new Thread(this);
            thread.start();
        }
    }

    public void stop() {
        if (thread != null) {
            thread.stop();
            thread = null;
        }
        try {
            if (send != null) {
                send.close();
            }
            if (input != null) {
                input.close();
            }
            if (mySocket != null) {
                mySocket.close();
            }
        } catch (IOException ex) {
            System.out.println("Cannot close");
            //client.close();

        }
        client.close();
        client.stop();

    }

    public static void main(String args[]) {
        Client client = new Client("localhost", Integer.parseInt("7867"));
    }
}
