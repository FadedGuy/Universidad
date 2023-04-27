/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
*/
import java.rmi.RemoteException;
import java.util.Vector;

/**
 *
 * @author bgenthon
 */
public class BiereImpl implements IBiere {
    
    protected Vector<Biere> blondes;

    protected Vector<Biere> ambrees;

    /**
     * Retourne la liste des bieres blondes
     */
    public Vector<Biere> listeBlondes() throws RemoteException {
        return blondes;
    }

    /**
     * Retourne la liste des bieres ambrees
     */
    public Vector<Biere> listeAmbrees() throws RemoteException {
        return ambrees;
    }

    /**
     * Retourne un fut de biere de la biere dont on passe le nom en parametre.
     * Si cette biere n'existe pas, retourne <code>null</code>
     */
    public Biere acheterBiere(String nom) throws RemoteException {
        Vector<Biere> toutes = new Vector<Biere>();
        Biere b;
        toutes.addAll(ambrees);
        toutes.addAll(blondes);

        for (int i=0; i<toutes.size(); i++) {
            b = (Biere)toutes.elementAt(i);
            if (b.getNom().equals(nom)) return b;
        }
        return null;
    }
}
