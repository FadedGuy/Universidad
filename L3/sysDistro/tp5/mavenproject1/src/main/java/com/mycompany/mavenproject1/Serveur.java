/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */

package com.mycompany.mavenproject1;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.ServerSocket;
/**
 *
 * @author kasiordia
 */
public class Serveur extends Thread{
    protected Socket socket;
    
    public Serveur(Socket socket){
        this.socket = socket;
    }
    
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        System.out.println("Hello World!");
        try {
            DataManager dataManager = new DataManager();
            ServerSocket serverSocket = new ServerSocket(7777);

            Serveur cf;
            while(true){
                System.out.println("Att connexion!");
                Socket socket = serverSocket.accept();
                System.out.println("Connecte");
                cf = new Serveur(socket);
                cf.start();
            }
        } catch (Exception e) {
            System.err.println("erreur " + e);
        }
        
    }
    
    public void run(){
        System.out.println("Hello thread!");
        
        try{
            ObjectOutputStream output = new ObjectOutputStream(this.socket.getOutputStream());
            ObjectInputStream input = new ObjectInputStream(this.socket.getInputStream());

            String chaine = (String) input.readObject();
            System.out.println("recu: " + chaine);
            System.out.println("ca vient de: " + this.socket.getInetAddress() + " : " + this.socket.getPort());
            output.writeObject("bien recu");
        }
        catch(IOException | ClassNotFoundException ex){
            System.err.println(ex.getMessage());
        }
        
    }
}
    