/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

import java.net.*;
import java.io.*;
import java.util.*;
//help from http://pirate.shu.edu/~wachsmut/Teaching/CSAS2214/Virtual/Lectures/chat-client-server.html
/**
 *
 * @author zuldyz
 */
public class Server implements Runnable {

    private ServerSocket connectionSocket = null;
    private Thread cthread = null;
    private Socket clientSocket = null;
    private ServerThread client[] = new ServerThread[100];
    private String[] groups = {"Philosophers", "Historians", "Politicians", "BookPeople", "Financists"};
    private int numberOfClients = 0;

    public Server(int port) {
        try {
            connectionSocket = new ServerSocket(port);
            System.out.println("Server is running on port: " + connectionSocket);
            start();
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
        }
    }

    @Override
    public void run() {
        while (cthread != null) {
            try {
                System.out.println("Client is arriving...");
                clientSocket = connectionSocket.accept();
                addThread(clientSocket);

            } catch (IOException ex) {
                System.out.println(ex.getMessage());
            }
        }
    }

    public void start() {
        if (cthread == null) {
            cthread = new Thread(this);
            cthread.start();
        }
    }

    public void stop() {
        if (cthread != null) {
            cthread.stop();
            cthread = null;
        }
    }

    public int findByName(String name) {
        for (int i = 0; i < numberOfClients; i++) {
            System.out.println("I look for  user:" + name);
            if (client[i].getUsername().equals(name)) {
                System.out.println("Me" + client[i].getUsername());
                return client[i].getID();
            }
        }
        return -1;
    }

    public int findByGroupName(String gname) {
        for (int i = 0; i < 5; i++) {
            System.out.println("I look for  user:" + gname);
            if (groups[i].equals(gname)) {
                System.out.println("Me" + groups[i].equals(gname));
                return i;
            }
        }
        return -1;
    }

    public int findBySocket(int Id) {
        for (int i = 0; i < numberOfClients; i++) {
            if (client[i].getID() == Id) {
                return i;
            }
        }
        return -1;
    }

    public synchronized void handleClients(int Id, String inp) {
        String line = inp;
        String strs[] = line.split(" ");

        if (strs[0].equals("server")) {
            if (strs[1].equals("hello")) {
                client[findBySocket(Id)].setUsername(strs[2]);
                String message = "hi " + strs[2];
                client[findBySocket(Id)].send(message);
            } else if (client[findBySocket(Id)].getUsername() == null) {
                client[findBySocket(Id)].send("First need to establish the connection!");
            } else if (strs[1].equals("groupslist")) {
                String message = "";
                for (int i = 0; i < 5; i++) {
                    System.out.println(groups[i]);
                    String members = "";
                    for (int j = 0; j < numberOfClients; j++) {
                        if (client[j].getGroup() == i) {
                            System.out.println("I am a mem " + client[j].getUsername());
                            members += client[j].getUsername();
                            if (j != numberOfClients - 1) {
                                members += ", ";
                            }
                        }
                    }
                    message += groups[i] + ": " + members;
                    if (i != 4) {
                        message += " | ";
                    }
                }
                client[findBySocket(Id)].send(message + "\n");
            } else if (strs[1].equals("join")) {
                String response;
                if (client[findBySocket(Id)].getGroup() != -1) {
                    response = "You cannot be a member of more than one group!";
                } else if (findByGroupName(strs[2]) > -1) {
                    client[findBySocket(Id)].setGroup(findByGroupName(strs[2]));
                    response = "Successfully joined to the group: " + strs[2];
                } else {
                    response = "Group doesn't exist";
                }
                client[findBySocket(Id)].send(response);
            } else if (strs[1].equals("members")) {
                String response = "";
                int group = client[findBySocket(Id)].getGroup();
                if (group == -1) {
                    response = "You do not have a group";
                } else {
                    for (int j = 0; j < numberOfClients; j++) {
                        if (client[j].getGroup() == group) {
                            response += client[j].getUsername();
                            if (j != numberOfClients - 1) {
                                response += ", ";
                            }
                        }

                    }
                }
                client[findBySocket(Id)].send(response + "\n");
            } else if (strs[1].equals("leave")) {
                if (client[findBySocket(Id)].getGroup() == -1) {
                    client[findBySocket(Id)].send( "You do not have a group to leave!\n");
                } else {
                    client[findBySocket(Id)].setGroup(-1);
                    client[findBySocket(Id)].send( "You left the group.\n");
                }
            } else if (strs[1].equals("exit")) {
                client[findBySocket(Id)].send("Bye!");
                remove(Id);
                try{
                clientSocket.close();
                }catch(IOException ex){
                    System.out.println(ex.getMessage());
                }
            }

        } else if (strs[0].equals("toall")) {
            String mssg[] = line.split(" ", 2);
            for (int i = 0; i < numberOfClients; i++) {
                if (client[i].getGroup() == client[findBySocket(Id)].getGroup() && client[i].getID() != Id) {
                    client[i].send(client[findBySocket(Id)].getUsername() + ": " + mssg[1]);
                }
            }
        } else {
            String mssg[] = line.split(" ", 2);
            int receiver = findByName(mssg[0]);
            if (receiver < 0) {
                client[findBySocket(Id)].send(mssg[0] + " disconnected!\n");
            } else if (client[findBySocket(receiver)].getGroup() == client[findBySocket(Id)].getGroup()) {
                client[findBySocket(receiver)].send(client[findBySocket(Id)].getUsername() + ": " + mssg[1]);
            } else {
                client[findBySocket(Id)].send(mssg[0] + " is not in your group!\n");
            }

        }

    }

    public synchronized void remove(int Id) {
        int position = findBySocket(Id);
        if (position >= 0) {
            ServerThread toRemove = client[position];
            //System.out.println("Removing client thread " + ID + " at " + pos);
            if (position < numberOfClients - 1) {
                for (int i = position + 1; i < numberOfClients; i++) {
                    client[i - 1] = client[i];
                }
            }
            numberOfClients--;
            try {
                toRemove.close();
            } catch (IOException ioe) {
                System.out.println("Error closing thread: " + ioe);
            }
            toRemove.stop();
        }
    }

    public void addThread(Socket sock) {
        if (numberOfClients < client.length) {
            System.out.println("New client has arrived: " + sock);
            client[numberOfClients] = new ServerThread(this, sock);

            try {
                client[numberOfClients].openConnection();
                client[numberOfClients].start();
                numberOfClients++;
            } catch (IOException ex) {
                System.out.println(ex.getMessage());
            }
        } else {
            System.out.println("Cannot accept more clients.");
        }
    }

    public static void main(String[] argc) {
        Server server = new Server(Integer.parseInt("7867"));
    }

}
