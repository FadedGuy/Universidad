package com.mycompany.n_insee;

/**
 *
 * @author kasiordia
 */
public class Main {
    //Toujours appelle main. Pour l'usage exterieur
    public static void main(String[] args){
        N_INSEE n_insee = new N_INSEE("1630125388055");
        System.out.println("Clef de 1630125388055 est : " + n_insee.clef());
        N_INSEE n_insee1 = new N_INSEE("3630125388055");
        System.out.println("Clef de 1630125388055 est : " + n_insee1.clef());
    }
}
