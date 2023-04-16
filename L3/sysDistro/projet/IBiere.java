import java.rmi.RemoteException;
import java.rmi.Remote;

import java.util.Vector;

// partie IRectangle de l'exemple rectangles TP7

public interface IBiere extends Remote {

    /**
     * Retourne la liste des bieres blondes
     */
    public Vector<Biere> listeBlondes() throws RemoteException;

    /**
     * Retourne la liste des bieres ambrees
     */
    public Vector<Biere> listeAmbrees() throws RemoteException;

    /**
     * Retourne un fut de biere de la biere dont on passe le nom en parametre.
     * Si cette bier n'existe pas, retounre <code>null</code>
     */
    public Biere acheterBiere(String nom) throws RemoteException;

}