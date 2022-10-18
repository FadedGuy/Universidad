package com.mycompany.javaprojectl3;
import java.io.IOException;

public class Main {
    
    static {
            // https://docs.oracle.com/javase/8/docs/technotes/guides/net/proxies.html
            System.setProperty("http.proxyHost", "cache.univ-pau.fr");
            System.setProperty("http.proxyPort", "3128");
        }

    public static void main(String[] args) throws IOException {
        String bar_code = "716270001660"; // string given by WebSocket
        System.out.println("OpenFoodFacts: " + OpenFoodFacts.getNutriScore(bar_code)); 
    }
}
