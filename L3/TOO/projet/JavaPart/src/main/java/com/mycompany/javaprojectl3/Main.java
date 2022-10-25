package com.mycompany.javaprojectl3;
import org.glassfish.tyrus.server.*;

public class Main {
    
    static {
            // https://docs.oracle.com/javase/8/docs/technotes/guides/net/proxies.html
            System.setProperty("http.proxyHost", "cache.univ-pau.fr");
            System.setProperty("http.proxyPort", "3128");
        }
    
    public static void main(String[] args) throws java.io.IOException, javax.websocket.DeploymentException {
        String bar_code = "716270001660"; // string given by WebSocket
        System.out.println("OpenFoodFacts: " + OpenFoodFacts.getNutriScore(bar_code)); 
//        
//        bar_code = "737628064502"; // string given by WebSocket
//        System.out.println("OpenFoodFacts: " + OpenFoodFacts.getNutriScore(bar_code)); 
        
        Server server = new Server("localhost", 19992, "/", null, Endpoint.class);
        try {
            server.start();
            System.out.println("\n**Press any key to stop the server..**\n");
            java.awt.Desktop.getDesktop().browse(java.nio.file.FileSystems.getDefault().getPath("frontend/index.html").toUri());
            
            java.io.BufferedReader reader = new java.io.BufferedReader(new java.io.InputStreamReader(System.in));
            reader.readLine();
            
            System.out.println("\n@@@\n" + "@@@\n");
        } catch(Exception e){
            e.printStackTrace();
        } finally {
            server.stop();
        }
    }
}
