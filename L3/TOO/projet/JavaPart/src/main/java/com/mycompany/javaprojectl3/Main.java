package com.mycompany.javaprojectl3;
import java.io.IOException;

public class Main {
    
//    static {
//            // https://docs.oracle.com/javase/8/docs/technotes/guides/net/proxies.html
//            System.setProperty("http.proxyHost", "cache.univ-pau.fr");
//            System.setProperty("http.proxyPort", "3128");
//        }
    
    /* Danger: 'My_ServerEndpoint' constructor must be accessed by the WebSockets server. Don't forget 'static'! */
    @javax.websocket.server.ServerEndpoint(value = "/ws_barcode")
    public static class My_ServerEndpoint { // It *MUST* be 'public'!

        @javax.websocket.OnClose
        public void onClose(javax.websocket.Session session, javax.websocket.CloseReason close_reason) {
            System.out.println("onClose: " + close_reason.getReasonPhrase());
        }

        @javax.websocket.OnError
        public void onError(javax.websocket.Session session, Throwable throwable) {
            System.out.println("onError: " + throwable.getMessage());
        }

        @javax.websocket.OnMessage
        public void onMessage(javax.websocket.Session session, String message) {
            System.out.println("Message from client: " + message);
        }

        @javax.websocket.OnOpen
        public void onOpen(javax.websocket.Session session, javax.websocket.EndpointConfig ec) throws java.io.IOException {
            System.out.println("OnOpen... " + ec.getUserProperties().get("Author"));
            session.getBasicRemote().sendText("{\"Handshaking\": \"Yes\"}");
        }
    }
    
    public static void main(String[] args) throws IOException {
        String bar_code = "716270001660"; // string given by WebSocket
        System.out.println("OpenFoodFacts: " + OpenFoodFacts.getNutriScore(bar_code)); 
        
        bar_code = "737628064502"; // string given by WebSocket
        System.out.println("OpenFoodFacts: " + OpenFoodFacts.getNutriScore(bar_code)); 
        
        java.util.Map<String, Object> user_properties = new java.util.HashMap();
        user_properties.put("Author", "FranckBarbier");

        org.glassfish.tyrus.server.Server server = new org.glassfish.tyrus.server.Server("localhost", 2021, "/FranckBarbier", user_properties /* or 'null' */, My_ServerEndpoint.class);
        try {
            server.start();
            System.out.println("\n*** Please press any key to stop the server... ***\n");
// The Web page (JavaScript client) is launched from Java:
            java.awt.Desktop.getDesktop().browse(java.nio.file.FileSystems.getDefault().getPath("web" + java.io.File.separatorChar + "index.html").toUri());
// The Java 11 client is launched as well:
            ws_client client = new ws_client(java.util.Optional.of(ws_client.class.getSimpleName()));
            java.io.BufferedReader reader = new java.io.BufferedReader(new java.io.InputStreamReader(System.in));
            reader.readLine();
            System.out.println("\n@@@\n" + client.get_log() + "@@@\n");
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            server.stop();
        }
    }
}
