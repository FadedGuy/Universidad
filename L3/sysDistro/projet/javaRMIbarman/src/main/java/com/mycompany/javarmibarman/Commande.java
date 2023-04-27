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
        
/**
 * Classe cliente qui va appeler les services à distance sur la partie serveur
 */


public class Commande {
    private static Fournisseur f1;
    private static final int PORT_RECEIVE = 7777;
    private static final int PORT_SEND = 7778;
    
    // found on https://stackoverflow.com/questions/1892765/how-to-capitalize-the-first-character-of-each-word-in-a-string
    // could not find a way to import and use WordUtils.capitalizeFully(string)
    private static String toTitleCase(String givenString) {
        String[] arr = givenString.split(" ");
        StringBuffer sb = new StringBuffer();

        for (int i = 0; i < arr.length; i++) {
            sb.append(Character.toUpperCase(arr[i].charAt(0)))
                .append(arr[i].substring(1)).append(" ");
        }          
        return sb.toString().trim();
    }  
    
    private static String returnScanner(Scanner scOperations) {
        String nextRead = "";
        nextRead += scOperations.nextLine();
        nextRead = nextRead.trim().toLowerCase(); // deleting spaces in the string and lowercase to avoid bugs
        return nextRead;
    }
    
    private static void operationMenu(Scanner scOperations, IBiere opBiere, Vector<String> availableOperations, String machineName, DatagramSocket socket) throws RemoteException, IOException {
        String operationPick;
            
            do {
                System.out.println("\nWhat operation would you like to do? (liste blondes/liste ambrees/acheter/cancel)");
                operationPick = returnScanner(scOperations);
                
                // determines whether user wants to print lists or buy a beer
                switch(operationPick) {
                    case "liste blondes":
                        Vector<Biere> blondList = opBiere.listeBlondes();
                        printBeerList(blondList);
                        operationMenu(scOperations, opBiere, availableOperations, machineName, socket);
                        break;
                    case "liste ambrees":
                        Vector<Biere> amberList = opBiere.listeAmbrees();
                        printBeerList(amberList);
                        operationMenu(scOperations, opBiere, availableOperations, machineName, socket);
                        break;
                    case "acheter":
                        boolean isBought = buyABeer(f1, scOperations, socket, machineName);
                        if(!isBought) {
                            operationMenu(scOperations, opBiere, availableOperations, machineName, socket);
                        }
                        break;
                    case "cancel":
                        sendPacket(socket, "1", machineName);
                        break;
                    default:
                        System.out.println("This operation doesnt exist.");
                }
            } while(!availableOperations.contains(operationPick));
    }
    
    private static boolean buyABeer(Fournisseur f1, Scanner sc, DatagramSocket socket, String machineName) throws RemoteException, IOException {
        boolean purchaseWentWell = false;
        String beerPick;
        do {
            System.out.println("Which beer do you want to buy? (enter \"none\" to go back to operations menu)");
            beerPick = returnScanner(sc);
            if("none".equals(beerPick)) {
                break;
            }
            purchaseWentWell = treatBeerPurchase(beerPick, f1, socket, machineName);
        } while(!purchaseWentWell);
        return purchaseWentWell;
    }

    private static boolean treatBeerPurchase(String beerPick, Fournisseur f1, DatagramSocket socket, String machineName) throws RemoteException, IOException {        
        String beerType;
        Biere beerBought = f1.acheterBiere(toTitleCase(beerPick));
        if(beerBought != null) {
            System.out.println("Beer " + beerPick + " bought!");
            beerType = f1.ambrees.contains(beerBought) ? "ambree" : "blonde";
            sendPacket(socket, "0 " + beerPick + " " + beerType, machineName);
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
    
    private static void sendPacket(DatagramSocket socket, String beerInformations, String machineName) throws IOException {
        InetAddress adr = InetAddress.getByName(machineName);
        byte[] data = beerInformations.getBytes();
        DatagramPacket packetToSend = new DatagramPacket(data, data.length, adr, PORT_SEND); // 2 different ports to send and receive otherwise it receives its own packet
        System.out.println(beerInformations);
        socket.send(packetToSend);
    }
    
    private static void processRequest(DatagramSocket socket_receive, DatagramPacket receivedPacket, String[] argv) throws IOException, NotBoundException {
        Scanner scOperations = new Scanner(System.in);
        String receivedData;
        String beerType;
        String buySameOrNewBeerChoice;
        String beerWanted;
        
        // on récupère une référence sur l'objet distant nommé "DedeLaChope" via
        // le registry de la machine sur laquelle il s'exécute
        IBiere opBiere = (IBiere) Naming.lookup("rmi://"+argv[1]+"/DedeLaChope"); // argv[1] = pc ip adress on which we execute the server, ifconfig in terminal to get ip
        Vector<String> availableOperations = new Vector<>();
        availableOperations.add("liste blondes");
        availableOperations.add("liste ambrees");
        availableOperations.add("acheter");
        availableOperations.add("cancel");

        Vector<String> sameOrNewChoiceVector = new Vector<>();
        sameOrNewChoiceVector.add("same");
        sameOrNewChoiceVector.add("new");
        sameOrNewChoiceVector.add("cancel");
        
        while(true) {
            System.out.println("\n------------------------\n" + 
                                "Waiting for a new request");
            socket_receive.receive(receivedPacket);
            receivedData = new String(receivedPacket.getData(), 0, receivedPacket.getLength()).trim();            
            beerType = receivedData.substring(receivedData.lastIndexOf(" ") + 1);
            beerWanted = receivedData.replace(beerType, "").trim();
            
            
            System.out.println("\nREQUEST FOUND\n"
                              + "You want to buy " + beerWanted + " of type " + beerType + ".\n");
            
                do {
                    System.out.println("Do you want to buy " + beerWanted + " or buy a new beer ? (same/new/cancel)");
                    buySameOrNewBeerChoice = returnScanner(scOperations);
                    switch(buySameOrNewBeerChoice) {
                        case "same":
                            treatBeerPurchase(beerWanted, f1, socket_receive, argv[0]);
                            break;
                        case "new":
                            operationMenu(scOperations, opBiere, availableOperations, argv[0], socket_receive);
                            break;
                        case "cancel":
                            sendPacket(socket_receive, "1", argv[0]);
                            break;
                        default:
                            System.out.println("This operation doesnt exist.");
                    }

                 } while (!sameOrNewChoiceVector.contains(buySameOrNewBeerChoice));
        }    
    }

    public static void main(String argv[]) throws java.net.SocketException, IOException, InterruptedException, NotBoundException {
        DatagramPacket receivedPacket;
        DatagramSocket socket_receive;
        f1 = new Fournisseur();
        

        socket_receive = new DatagramSocket(PORT_RECEIVE);
        byte[] data = new byte[25];
        receivedPacket = new DatagramPacket(data, data.length);
                     
        if(argv.length > 0) {
            processRequest(socket_receive, receivedPacket, argv);  
        } else {
            System.err.println("Missing arguments (first: barman ip, second: fournisseur ip)");
        }
    }
}
