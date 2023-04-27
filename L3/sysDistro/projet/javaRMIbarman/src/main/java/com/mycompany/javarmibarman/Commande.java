import java.io.IOException;
import java.rmi.Naming;
import java.net.InetAddress;
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
    private static Fournisseur f1;
    public static final int PORT_RECEIVE = 7777;
    public static final int PORT_SEND = 7778;
    
    // found on https://stackoverflow.com/questions/1892765/how-to-capitalize-the-first-character-of-each-word-in-a-string
    // could not find a way to import and use WordUtils.capitalizeFully(string)
    public static String toTitleCase(String givenString) {
        String[] arr = givenString.split(" ");
        StringBuffer sb = new StringBuffer();

        for (int i = 0; i < arr.length; i++) {
            sb.append(Character.toUpperCase(arr[i].charAt(0)))
                .append(arr[i].substring(1)).append(" ");
        }          
        return sb.toString().trim();
    }  
    
    private static void operationMenu(Scanner scOperations, IBiere opBiere, Vector<String> availableOperations, String machineName, DatagramSocket socket) throws RemoteException, IOException {
        String operationPick = "";
            
            do {
                System.out.println("\nWhat operation would you like to do? (liste blondes/liste ambrees/acheter/cancel)");
                
                operationPick = "";
                operationPick += scOperations.nextLine();
                operationPick = operationPick.trim().toLowerCase();
                
                switch(operationPick) {
                    case "liste blondes":
                        Vector<Biere> blondList = opBiere.listeBlondes();
                        printBeerList(blondList);
                        break;
                    case "liste ambrees":
                        Vector<Biere> amberList = opBiere.listeAmbrees();
                        printBeerList(amberList);
                        break;
                    case "acheter":
                        buyABeer(f1, scOperations, socket, machineName);
                        break;
                    case "cancel":
                        sendASocket(socket, "1", machineName);
                        break;
                    default:
                        System.out.println("This operation doesnt exist.");
                }
            } while(availableOperations.contains(operationPick));

    }
    
    private static boolean buyABeer(Fournisseur f1, Scanner sc, DatagramSocket socket, String machineName) throws RemoteException, IOException {
        boolean purchaseWentWell = false;
        String beerPick;
        do {
            System.out.println("Which beer do you want to buy? (enter \"none\" to go back to operations menu)");
            beerPick = "";
            beerPick += sc.nextLine();
            beerPick = beerPick.trim();
            if("none".equals(beerPick)) {
                break;
            }
            purchaseWentWell = treatBeerPurchase(beerPick, f1, sc, socket, machineName);
        } while(!purchaseWentWell);
        return purchaseWentWell;
    }

    private static boolean treatBeerPurchase(String beerPick, Fournisseur f1, Scanner sc, DatagramSocket socket, String machineName) throws RemoteException, IOException {        
        String beerType = "TYPE_NOT_INITIALIZED";
        if(f1.acheterBiere(toTitleCase(beerPick)) != null) {
            System.out.println("Beer " + beerPick + " bought!");
            if(f1.ambrees.contains(f1.acheterBiere(toTitleCase(beerPick)))) {
                beerType = "ambree";
            } else {
                beerType = "blonde";
            }
            sendASocket(socket, (new String("0 " + beerPick + " " + beerType)), machineName);        
            return true;
        } else {
            System.err.println("The beer doesnt or no longer exists.");
            return false;
        }
    }

    private static void printBeerList(Vector<Biere> list) {
        System.out.println("\nHere are the available beers : \n"
                + "\tMENU\n"
                + "-------------------");
        for(int i = 0; i < list.size(); i++) {
            System.out.println(list.get(i));
        }
        System.out.println("-------------------\n");
    }
    
    private static void sendASocket(DatagramSocket socket, String beerInformations, String machineName) throws IOException {
        InetAddress adr = InetAddress.getByName(machineName);
        byte[] data = beerInformations.getBytes();
        DatagramPacket packetToSend = new DatagramPacket(data, data.length, adr, PORT_SEND); // changer port pour renvoyer sinon ça récup direct l'envoi
        System.out.println(beerInformations);
        socket.send(packetToSend);
    }

    public static void main(String argv[]) throws java.net.SocketException, IOException, InterruptedException {
        Scanner scOperations = new Scanner(System.in);
        DatagramPacket receivedPacket;
        DatagramSocket socket_receive;
        DatagramPacket packetToSend;
        InetAddress adr;
        String receivedData;
        String beerType;
        String buySameOrNewBeerChoice;
        String beerWanted;

        socket_receive = new DatagramSocket(PORT_RECEIVE);
        byte[] data = new byte[25];
        receivedPacket = new DatagramPacket(data, data.length);
        
        while(true) {
            System.out.println("\n------------------------\n" + 
                                "Waiting for a new request");
            socket_receive.receive(receivedPacket);
            receivedData = new String(receivedPacket.getData(), 0, receivedPacket.getLength()).trim();            
            System.out.println("\nREQUEST FOUND\n"
                              + "You want to buy " + receivedData + ".\n");

            beerType = receivedData.substring(receivedData.lastIndexOf(" ") + 1);
            beerWanted = receivedData.replace(beerType, "").trim();
            
            try {
                f1 = new Fournisseur();
                // on récupère une référence sur l'objet distant nommé "DedeLaChope" via
                // le registry de la machine sur laquelle il s'exécute
                IBiere opBiere = (IBiere) Naming.lookup("rmi://"+argv[0]+"/DedeLaChope"); // argv[0] = pc ip adress on which we execute the server, ifconfig in terminal to get ip
                Vector<String> availableOperations = new Vector<>();
                availableOperations.add("liste blondes");
                availableOperations.add("liste ambrees");
                availableOperations.add("acheter");
                availableOperations.add("cancel");

                Vector<String> sameOrNewChoiceVector = new Vector<>();
                sameOrNewChoiceVector.add("same");
                sameOrNewChoiceVector.add("new");
                sameOrNewChoiceVector.add("cancel");


                do {
                    System.out.println("Do you want to buy " + beerWanted + " or buy a new beer ? (same/new/cancel)");
                    buySameOrNewBeerChoice = "";
                    buySameOrNewBeerChoice += scOperations.nextLine();
                    buySameOrNewBeerChoice = buySameOrNewBeerChoice.trim().toLowerCase(); // deleting spaces in the string and lowercase to avoid bugs

                    switch(buySameOrNewBeerChoice) {
                        case "same":
                            boolean purchaseWentWell = treatBeerPurchase(beerWanted, f1, scOperations, socket_receive, argv[0]);
                            /*if(purchaseWentWell) {
                                String beerInformations = new String("0 " + beerWanted + " " + beerType);    
                                sendASocket(socket_receive, beerInformations, argv[0]);
                            }*/
                            operationMenu(scOperations, opBiere, availableOperations, argv[0], socket_receive);
                            break;
                        case "new":
                            operationMenu(scOperations, opBiere, availableOperations, argv[0], socket_receive);
                            break;
                        case "cancel":
                            sendASocket(socket_receive, "1", argv[0]);
                            break;
                        default:
                            System.out.println("This operation doesnt exist.");
                    }

                 } while (!sameOrNewChoiceVector.contains(buySameOrNewBeerChoice));


            } catch (MalformedURLException | NotBoundException | RemoteException e) {
                    System.err.println("ERROR : " + e);
            }

        }
        
        /* System.out.println("beerType : " + beerType + "test espace\n"
                          + "nom de la biere : " + beerWanted + "test espace");*/
        
                    
    }
}