/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.mavenproject1;
import java.util.Vector;
/**
 *
 * @author kasiordia
 */
public class DataManager {
    /**
    * Vecteur qui contient les personnes
    */
    protected Vector<Personne> personneVector = new Vector<Personne>();

    /**
     * Ajoute une personne dans la liste et retourne son
     * identificateur. Si la personne existait déjà, retourne
     * l'identificateur qu'elle avait dans la liste.
     * @param p la personne à ajouter dans la liste
     * @return l'identificateur de la personne
     */
    public synchronized int addPersonne(Personne p)
    {
	if (!personneVector.contains(p)) personneVector.add(p);
	return (personneVector.indexOf(p));
    }

    /**
     * Récupère une personne dans la liste à partir de son
     * identifiant.
     * @param id l'idenfiant de la personne à récupérer
     * @throws InvalidIdException dans le cas où l'identifiant
     * n'est attribué à aucune personne
     */
    public synchronized Personne getPersonne(int id) throws InvalidIdException
    {
	if (id >= personneVector.size()) throw new InvalidIdException("invalid index value : "+id);
	return (personneVector.elementAt(id));
    }

    /**
     * Récupére l'identifiant d'une personne.
     * @param p la personne dont on veut récupérer l'identifiant
     * @return l'identificateur de la personne. Si la personne n'est
     * pas dans la liste, retourne -1.
     */
    public synchronized int getId(Personne p)
    {
	return personneVector.indexOf(p);
    }


    /**
     * Programme qui permet de tester le fonctionnement de la classe
     * <code>DataManager</code> et de ses opérations de gestion de
     * personnes.
     */
    public static void main(String argv[])
    {
	DataManager dm = new DataManager();
	Personne p;
	int id;

	System.out.println("\n** Remplissage de la liste **\n");

	p = new Personne(29, "Gérard");
	id = dm.addPersonne(p);
	System.out.println("- Ajout de % "+p+" % avec identifiant = "+id);

	p = new Personne(20, "Marie-Germaine");
	id = dm.addPersonne(p);
	System.out.println("- Ajout de % "+p+" % avec identifiant = "+id);

	p = new Personne(29, "Gérard");
	id = dm.addPersonne(p);
	System.out.println("- Ajout de % "+p+" % avec identifiant = "+id);

	p = new Personne(42, "Saturnin");
	id = dm.addPersonne(p);
	System.out.println("- Ajout de % "+p+" % avec identifiant = "+id);

	System.out.println("\n** Interrogation de la liste **\n");

        try {
	    p = dm.getPersonne(2);
            System.out.println("- Personne d'identificateur 2 = "+p);
        }
        catch(InvalidIdException e)  {
	    System.err.println("[Erreur] Personne d'identificateur 2 : "+e);
	}

        try {
	    p = dm.getPersonne(5);
            System.out.println("- Personne d'identificateur 5 = "+p);
        }
        catch(InvalidIdException e) {
	    System.err.println("[Erreur] Personne identificateur 5 : "+e);
	}

        System.out.println("- Identificateur de Gérard, 29 ans = "+dm.getId(new Personne(29, "Gérard")));
        System.out.println("- Identificateur de Maurice, 54 ans = "+dm.getId(new Personne(54,"Maurice")));
	System.out.println("- Identificateur de Marie-Germaine, 20 ans = "+dm.getId(new Personne(20,"Marie-Germaine")));
    }
}
