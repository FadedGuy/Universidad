public class Biere implements java.io.Serializable {

    protected String nom;

    protected int couleur;

    protected int degre;

    public static int AMBREE=1;

    public static int BLONDE=2;

    public String getNom() {
        return nom;
    }

    public int getCouleur() {
        return couleur;
    }

    public int getDegre() {
        return degre;
    }

    public Biere(String nom, int couleur, int degre) {
        this.nom = nom;
        this.couleur = couleur;
        this.degre = degre;
    }

    public String toString() {
        String coul = "couleur inconnue";
        if (couleur == Biere.AMBREE) coul = "ambree";
        if (couleur == Biere.BLONDE) coul = "blonde";

        return nom + ", "+couleur+ ", "+ degre +"�";
    }
}