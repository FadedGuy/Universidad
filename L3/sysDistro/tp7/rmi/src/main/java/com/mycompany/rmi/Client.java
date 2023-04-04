/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.rmi;
import java.rmi.Naming;

/**
 * Classe cliente qui va appeler les services à distance sur la partie serveur
 */

public class Client
{

    public static void main(String argv[])
    {

	try
	    {
		// création de rectangles pour l'appel des services
		Rectangle r1, r2;
		r1 = new Rectangle(10, 10, 20, 30);

		// on récupère une référence sur l'objet distant nommé "opRect" via
		// le registry de la machine sur laquelle il s'exécute
		IRectangle opRectangle = (IRectangle) Naming.lookup("rmi://"+argv[0]+"/opRect");

		// on appelle les services sur cet objet
		int surface = opRectangle.calculSurface(r1);
		r2 = opRectangle.decalerRectangle(r1, 15, 10);

		System.out.println(" surface de r1 = "+surface);
		System.out.println(" position de r2 = "+r2);
	    }
	catch (Exception e)
	    {
		System.err.println(e);
	    }
    }
}