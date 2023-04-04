/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Interface.java to edit this template
 */
package com.mycompany.rmi;
import java.rmi.Remote;
import java.rmi.RemoteException;

/**
 * Interface qui définit les services appelables à distance.
 * Cette interface doit étendre l'interface Remote
 *
 * Chaque opération doit préciser qu'elle peut lever l'exception
 * RemoteException.
 */
public interface IRectangle extends Remote
{
    public int calculSurface(Rectangle rect) throws RemoteException;
    public Rectangle decalerRectangle(Rectangle rect, int x, int y) throws RemoteException;
}
