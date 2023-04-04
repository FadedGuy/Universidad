/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.rmi;

import java.rmi.Naming;

/**
 * Classe qui intancie un objet implémentant les services et le met en
 * attente d'appels de services de la part des clients distants.
 */

public class Serveur
{
    public static void main(String argv[])
    {
	try
	    {
		// on instancie normalement l'objet implémentant les services
		RectangleImpl rect = new RectangleImpl();

		// on l'enregistre auprès du registry local sous le nom "opRect"
		Naming.rebind("opRect", rect);

		// si l'enregistrement s'est bien déroulé, cet objet est prêt
		// à recevoir des requêtes d'appels de services
	    }
	catch (Exception e)
	    {
		System.err.println(e);
	    }
    }
}
