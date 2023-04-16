import java.rmi.Naming;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

/**
 * Classe cliente qui va appeler les services à distance sur la partie serveur
 */

// partie client exemple rectangle TP7

public class Commande {

    private void printBeerList(vector<Biere> list) {
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

        DatagramSocket socket = new DatagramSocket(7777); // define port later
        byte[] data = new byte[25];
        packet = new DatagramPacket(data, data.length);
        socket.recieve(packet);
        String recievedData = new String(packet.getData(), 0, packet.getLength());
        System.out.println("recu " + recievedData);

        System.out.println("Connexion avec le socket réussie.");
        try {
            // création de fournisseurs pour l'appel des services
            Fournisseur f1;
            f1 = new Fournisseur();
            // on récupère une référence sur l'objet distant nommé "DedeLaChope" via
            // le registry de la machine sur laquelle il s'exécute
            IBiere opBiere = (IBiere) Naming.lookup("rmi://"+argv[0]+"/DedeLaChope");

            System.out.println("Quelle operation souhaitez-vous faire? (liste blondes/liste ambrees/acheter)");
            Scanner sc=new Scanner(System.in);

            switch(sc) {
                case "liste blondes":
                    vector<Biere> blondList = opBiere.listeBlondes();
                    printBeerList(blondList);
                    break;
                case "liste ambrees":
                    vector<Biere> amberList = opBiere.listeAmbrees();
                    printBeerList(amberList);
                case "acheter":
                    System.out.println("Quelle biere voulez-vous acheter?");
                    Scanner scBeer=new Scanner(System.in);
                    String beerPick = scBeer.next();
                    // très dégeu mais fonctionne? a modifier plus propre genre un tableau qui contient toutes les bieres existantes
                    // verifier si beerPick appartient au tableau puis appeler f1.acheterBiere(beerPick);
                    switch(beerPick) {
                        beerPick.toLowerCase();
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
        } catch (Exception e) {
            System.err.println(e);
        }
    }
}