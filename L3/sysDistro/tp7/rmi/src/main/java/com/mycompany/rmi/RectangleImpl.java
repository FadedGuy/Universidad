/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.rmi;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
/**
 *
 * @author kasiordia
 */
public class RectangleImpl implements IRectangle {
    // on implémente les services comme des opérations Java standard
    // à l'exception de RemoteException en signature

    public int calculSurface(Rectangle rect) throws RemoteException
    {
	return ( (rect.x2 - rect.x1) * (rect.y2 - rect.y1));
    }

    public Rectangle decalerRectangle(Rectangle rect, int x, int y) throws RemoteException
    {
	return new Rectangle(rect.x1 + x, rect.y1 + y, rect.x2 + x, rect.y2 + y);
    }

    /**
     * Le constructeur doit préciser que l'exception RemoteException
     * peut être levée
     * @throws java.rmi.RemoteException
     */
    public RectangleImpl() throws RemoteException
    {
	// exportation de l'objet afin de créer la mécanique TCP pour
	// pouvoir appeler les opérations à distance sur cet objet
	UnicastRemoteObject.exportObject(this, 0);
    }
}
