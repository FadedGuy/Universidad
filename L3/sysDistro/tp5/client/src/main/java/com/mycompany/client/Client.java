/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */

package com.mycompany.client;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.net.InetAddress;
import java.net.UnknownHostException;
/**
 *
 * @author kasiordia
 */
public class Client {
    
    Socket socket = null;
    ObjectInputStream input = null;
    ObjectOutputStream output = null;
    
    public void openConnection(String site, int port) throws Exception {
        InetAddress adr = InetAddress.getByName(site);
        socket = new Socket(adr, port);
        output = new ObjectOutputStream(socket.getOutputStream());
        input = new ObjectInputStream(socket.getInputStream());
    }
    
    public int addPersonne(Personne p) {
        try {
            output.writeObject(new AddPersonneMessage(p));
            GetIdMessage reponse = (GetIdMessage)input.readObject();
            return reponse.getID();
        } catch (Exception e){
            System.err.println("erreur " + e);
        }
        return -1;
    }
    
    public Personne getPersonne(int id) throws InvalidExceptionMessage {
        try {
            output.writeObject(new GetIdPersonne(id));
            Object obj = input.readObject();
            if(obj instanceof PersonneMessage) {
                return ((PersonneMessage)obj).getPersonne();
            }
            if(obj instanceof InvalidExceptionMessage) {
                throw (((InvalidExceptionMessage)obj).getException());
            }
        } catch (Exception e) {
            System.err.println("erreur " + e);
        }
        return null;
    }

    public static void main(String[] args) throws UnknownHostException, IOException, ClassNotFoundException {
        System.out.println("Hello World Client!");
        
        InetAddress adr = InetAddress.getByName("localhost");
        Socket socket = new Socket(adr, 7777);
        
        ObjectOutputStream output = new ObjectOutputStream(socket.getOutputStream());
        ObjectInputStream input = new ObjectInputStream(socket.getInputStream());
        
        output.writeObject("youpi");
        String chaine = (String)input.readObject();
        System.out.println("recu du serveur: " + chaine);
    }
}
