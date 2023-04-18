import java.io.IOException;
import java.rmi.Naming;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.MalformedURLException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.Scanner;
import java.util.Vector;

/**
 * Classe cliente qui va appeler les services à distance sur la partie serveur
 */

// partie client exemple rectangle TP7

public class Commande {

    private static void printBeerList(Vector<Biere> list) {
        System.out.println("Voici les bières disponibles : ");
        for(int i = 0; i < list.size()-1; i++) {
            System.out.print(list.get(i));
        }
        System.out.print(list.get(list.size()));
    }

    public static void main(String argv[]) {
        // to verify connexion via socket UDP TP1/TP6(asynchrones) ?
        DatagramPacket packet;
        DatagramSocket socket;

        try {
            socket = new DatagramSocket(7777); // define port later
            byte[] data = new byte[25];
            packet = new DatagramPacket(data, data.length);
            socket.receive(packet);
            String recievedData = new String(packet.getData(), 0, packet.getLength());
            System.out.println("recu " + recievedData);
            
            System.out.println("Connexion avec le socket réussie.");
        } catch (java.net.SocketException e) {
            System.err.println(e);
        } catch (IOException ex) {
            System.err.println(ex);
        }
        try {
            // création de fournisseurs pour l'appel des services
            Fournisseur f1;
            f1 = new Fournisseur();
            // on récupère une référence sur l'objet distant nommé "DedeLaChope" via
            // le registry de la machine sur laquelle il s'exécute
            IBiere opBiere = (IBiere) Naming.lookup("rmi://"+argv[0]+"/DedeLaChope");

            System.out.println("Quelle operation souhaitez-vous faire? (liste blondes/liste ambrees/acheter)");
            Scanner sc = new Scanner(System.in);
            String scPick = sc.next();
            
            switch(scPick.toLowerCase()) {
                case "liste blondes":
                    Vector<Biere> blondList = opBiere.listeBlondes();
                    printBeerList(blondList);
                    break;
                case "liste ambrees":
                    Vector<Biere> amberList = opBiere.listeAmbrees();
                    printBeerList(amberList);
                case "acheter":
                    System.out.println("Quelle biere voulez-vous acheter?");
                    Scanner scBeer = new Scanner(System.in);
                    String beerPick = scBeer.next();
                    // très dégeu mais fonctionne? a modifier plus propre genre un tableau qui contient toutes les bieres existantes
                    // verifier si beerPick appartient au tableau puis appeler f1.acheterBiere(beerPick);
                    switch(beerPick.toLowerCase()) {
                        case "paix dieu":
                            f1.acheterBiere(beerPick);
                            System.out.println("Biere" + beerPick + "achetée!");  
                            break;
                        case "goudale":
                            f1.acheterBiere(beerPick);
                            System.out.println("Biere" + beerPick + "achetée!");  
                            break;
                        case "delirium tremens":
                            f1.acheterBiere(beerPick);
                            System.out.println("Biere" + beerPick + "achetée!");  
                            break;
                        case "kwak":
                            f1.acheterBiere(beerPick);
                            System.out.println("Biere" + beerPick + "achetée!");  
                            break;
                        case "mousse ta shuc":
                            f1.acheterBiere(beerPick);
                            System.out.println("Biere" + beerPick + "achetée!");  
                            break;
                        case "queue de charrue":
                            f1.acheterBiere(beerPick);
                            System.out.println("Biere" + beerPick + "achetée!");  
                            break;
                        default:
                            System.err.println("La bière n'existe pas.");
                            break;
                    }
                    break;
                default:
                    System.out.println("Cette commande n'existe pas.");
            }
        } catch (MalformedURLException | NotBoundException | RemoteException e) {
            System.err.println(e);
        }
    }
}