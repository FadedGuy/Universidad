import java.io.IOException;
import java.rmi.Naming;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.MalformedURLException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.Scanner;
import java.util.Vector;
import java.util.Arrays;

/**
 * Classe cliente qui va appeler les services à distance sur la partie serveur
 */


public class Commande {

    private static Vector<String> availableBeers = new Vector<>(Arrays.asList(
        "paix dieu",
        "goudale",
        "delirium tremens",
        
        "kwak",
        "mousse ta shuc",
        "queue de charrue"
    ));

    private static boolean treatBeerPurchase(String beerPick, Fournisseur f1) throws RemoteException {
        if(availableBeers.contains(beerPick.toLowerCase())) {
            f1.acheterBiere(beerPick);
            System.out.println("Beer " + beerPick + " bought! \n");
            return true;
        } else {
            System.err.println("The beer doesnt exist.");
            return false;
        }
    }

    private static void printBeerList(Vector<Biere> list) {
        System.out.println("Here are the available beers : ");
        for(int i = 0; i < list.size(); i++) {
            System.out.println(list.get(i));
        }
        System.out.println("");
    }

    public static void main(String argv[]) {
        DatagramPacket packet;
        DatagramSocket socket;

        try {
            socket = new DatagramSocket(7777); // define port later
            byte[] data = new byte[25];
            packet = new DatagramPacket(data, data.length);
            System.out.println("Waiting");
            socket.receive(packet);
            String receivedData = new String(packet.getData(), 0, packet.getLength());
            System.out.println("received " + receivedData);
            
            System.out.println("Socket connection succeed.");
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
            IBiere opBiere = (IBiere) Naming.lookup("rmi://"+argv[0]+"/DedeLaChope"); // argv[0] = l'ip de la machine sur laquelle on exec le serveur, ifconfig
            Vector<String> availableOperations = new Vector<>();
            availableOperations.add("liste blondes");
            availableOperations.add("liste ambrees");
            availableOperations.add("acheter");
            
            String operationPick = "";
            
            do {
                System.out.println("What operation would you like to do? (liste blondes/liste ambrees/acheter/quit)");
                Scanner scOperations = new Scanner(System.in);
                operationPick = "";
                operationPick += scOperations.nextLine();
                
                switch(operationPick.toLowerCase()) {
                    case "liste blondes":
                        Vector<Biere> blondList = opBiere.listeBlondes();
                        printBeerList(blondList);
                        break;
                    case "liste ambrees":
                        Vector<Biere> amberList = opBiere.listeAmbrees();
                        printBeerList(amberList);
                        break;
                    case "acheter":
                        String beerPick = "";
                        boolean purchaseWentWell;
                        do {
                            System.out.println("Which beer do you want to buy?");
                            beerPick = "";
                            beerPick += scOperations.nextLine();
                            purchaseWentWell = treatBeerPurchase(beerPick, f1);
                        } while(!purchaseWentWell);
                        break;
                    case "quit":
                        break;
                    default:
                        System.out.println("This operation doesnt exist.");
                }
            } while(availableOperations.contains(operationPick));
        } catch (MalformedURLException | NotBoundException | RemoteException e) {
                System.err.println(e);
        }
            
    }
}