package com.mycompany.javaprojectl3;
import javax.websocket.*;
import javax.websocket.server.ServerEndpoint;

@ServerEndpoint(value="/bc_ws")
public class Endpoint {
    @OnOpen
    public void onOpen(Session session){
        System.out.println("Websocket opened: " + session.getId());
    }
    
    @OnMessage
    public void onMessage(String txt, Session session) throws java.io.IOException, javax.websocket.DeploymentException {
        System.out.println("Message received: " + txt);
        System.out.println("OpenFoodFacts: " + OpenFoodFacts.getNutriScore(txt)); 
        session.getBasicRemote().sendText(OpenFoodFacts.getNutriScore(txt));
    }

    @OnClose
    public void onClose(CloseReason reason, Session session) {
        System.out.println("Closing a WebSocket (" + session.getId() + ") due to: " + reason.getReasonPhrase());
    }

    @OnError
    public void onError(Session session, Throwable t) {
        System.out.println("Error in WebSocket session: " + session == null ? "null" : session.getId() + "due to: " + t);
    }
    
}
