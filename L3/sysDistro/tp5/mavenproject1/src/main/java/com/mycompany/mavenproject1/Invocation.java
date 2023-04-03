/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package com.mycompany.mavenproject1;

/**
 *
 * @author kasiordia
 */
import java.lang.reflect.Method;

/**
 * Objet "invocateur" qu'on associe à un objet, objet sur lequel on
 * appelera dynamiquement des méthodes à partir de leurs nom et
 * paramètres.
 */
public class Invocation {

    /**
     * L'objet sur lequel on appelera les méthodes
     */
    protected Object cible;

    /**
     * Invoque dynamiquement une méthode sur l'objet cible
     * @param nomMethode le nom de la méthode
     * @param types la liste des types des paramètres. Note : on ne
     * détermine pas automatiquement la liste des types à partir
     * de la liste des paramètres puisqu'il faut pouvoir
     * explicitement différencier, par exemple, le cas entre la
     * classe "Integer" et le type primitif "int" (représenté
     * alors par la valeur Integer.TYPE) et qu'on aura dans les 2 cas
     * une instance de la classe Integer en tant que paramètre.
     * @param params la liste des paramètres
     * @exception Exception deux cas sont à différencier : <ol>
     * <li>Un problème a eu lieu pour appeler la méthode
     * (paramètres non corrects, accès interdit, pas de
     * méthode de ce nom là ...) une exception
     * <code>UncallableMethodException</code> est alors levée</li>
     * <li>L'appel a bien eu lieu correctement mais la méthode a
     * levé une exception, cette exception est alors levée à
     * nouveau (d'où le type générique <code>Exception</code>
     * dans la signature de la méthode puisqu'on ne peut lever
     * n'importe quelle exception)</li></ol>.
     */
    public Object invoquer(String nomMethode, Class types[], Object params[]) throws Exception
    {

	Method met = null;
	Object result = null;
	Class cl;

	// recupere la classe de l'objet a invoquer
	cl = cible.getClass();

	// recupere la methode a appeler si elle existe
	// sinon renvoie une exception
	try {
	    met = cl.getMethod(nomMethode, types);
	}
	catch (java.lang.NoSuchMethodException e) {
	    throw new UncallableMethodException("Methode inexistante ["+e.getMessage()+"]");
	}

	try {
	    // la méthode est trouvée, on l'invoque dynamiquement
	    result =  met.invoke(cible, params);
	}
	catch(java.lang.IllegalAccessException e) {
	    throw new UncallableMethodException("Acces interdit a la methode ["+
						e.getMessage()+"]");
	}
	catch(java.lang.reflect.InvocationTargetException e) {
	    // la methode a leve une exception, on la leve
	    //System.out.println("Exception levee : "+e.getCause()+" type = "+e.getCause().getClass());
	    throw (Exception)e.getCause();
	}

	return result;
    }

    /**
     * @param cible l'objet sur lequel on appelera les méthodes
     */
    public Invocation(Object cible)
    {
	this.cible = cible;
    }

    // petit programme de test
    public static void main(String argv[])
    {
	try {
	    Invocation invoc = new Invocation(new DataManager());
	    String nom = "addPersonne";
	    Personne p = new Personne(14, "toto");
	    Object param[] = { p };
	    Class types[] = { p.getClass() };

	    Object res = invoc.invoquer(nom, types, param);
	    System.out.println(" Resultat : "+ res);

	    param = new Object[1];
	    param[0] = new Integer(2);
	    types = new Class[1];
	    types[0] = Integer.TYPE;
	    res = invoc.invoquer("getPersonne", types, param);
	    System.out.println(" Resultat : "+ res);
	}
	catch (Exception e) {
	    System.err.println("Erreur : "+e);
	}
    }
}
