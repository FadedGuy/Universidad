/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.client;

import java.io.IOException;
import java.net.Socket;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

/**
 *
 * @author kasiordia
 */
public class ThreadClient extends Thread{
    private Socket socket;
    private DataManager dataManager;
    
    public void run(){
        ObjectOutputStream output = null;
        ObjectInputStream input = null;
        try{
            output = new ObjectOutputStream(socket.getOutputStream());
            input = new ObjectInputStream(socket.getInputStream());
            while(true){
                Message msg = (Message) input.readObject();
                if(msg instanceof AddPersonneMessage){
                    Personne p = ((AddPersonneMessage) msg).getPersonne();
                    int nb = dataManager.addPersonne(p);
                    output.writeObject(new IdMessage(nb));
                }
                if(msg instanceof GetIdPersonne){
                    int id = ((GetIdPersonne)msg).getID();
                    Personne p = dataManager.getPersonne(id);
                    output.writeObject(new GetIdPersonne());
                }
            }
            
        }catch(IOException | ClassNotFoundException ex){
            System.err.println(ex);
        }
    }
}
