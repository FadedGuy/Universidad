/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */

package com.mycompany.asyncudpsocket;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.SocketException;
import java.net.DatagramSocket;
import java.util.PriorityQueue;
import java.util.Queue;

/**
 *
 * @author kasiordia
 */
public class AsyncUDPSocket{
    protected DatagramSocket socket;
    private Queue<DatagramPacket> packets;
    
    public AsyncUDPSocket() throws SocketException{
        this.packets = new PriorityQueue<>();
//        Cree une socket et la lie sur un port quelconque
        try{
            this.socket = new DatagramSocket();
        }
        catch(SocketException ex){
            throw new SocketException("A new socket cannot be created\n");
        }
    }
    
    public AsyncUDPSocket(int port) throws SocketException{
        this.packets = new PriorityQueue();
//        Cree une socket et la lie sur le port passe
        try{
            this.socket = new DatagramSocket(port);
        }
        catch(SocketException ex){
            throw new SocketException("A new socket cannot be created at port: "+port+"\n");
        }
    }
    
    void send(DatagramPacket dp) throws IOException{
        this.socket.send(dp);
    }
    
    boolean asyncReceive(DatagramPacket dp) throws IOException{
        DatagramPacket in = null; 
        if(available()){
            dp = this.packets.poll();
            return true;
        }
        
        this.socket.setSoTimeout(2000);
        try {
            this.socket.receive(in);
            this.packets.add(in);            
        } catch (java.net.SocketTimeoutException e) {
            return false;
        }
        return true;
    }
    
    void syncReceive(DatagramPacket dp) throws IOException{
        if(available()){
            dp = this.packets.poll();
        }
        else{
            this.socket.setSoTimeout(0);
            this.socket.receive(dp);    
        }
    }
    
    boolean available(){
        return this.packets.peek() != null;
    }
    
    void close(){
        this.socket.close();
    }
    
    public static void main(String[] args) {
        System.out.println("Hello World!");
    }
}
