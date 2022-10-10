/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Project/Maven2/JavaApp/src/main/java/${packagePath}/${mainClassName}.java to edit this template
 */

package com.mycompany.tp3;

/**
 *
 * @author faded
 */
public class Yesterday {
    public static final String avant_hier = "Avant hier";
    public static final String hier = "Hier";
    public static final String aujourd_hui = "Aujourd'hui";
    public static final String demain = "Demain";
    public static final String apres_demain = "Apres demain";
    public static final String jsp = "Je n'es sais rien";
    
    private final Integer jour;
    private final Integer mois;
    private final Integer annee;
    
    Yesterday(final int jour, final int mois, final int annee){
        assert(jour > 0 && mois > 0 && annee > 0);
        assert(jour <= 31 && mois <= 12);
        
        this.jour = jour;
        this.mois = mois;
        this.annee = annee;
    }
    
    public String before_yesterday(){
        String res = jsp;
       
        java.time.LocalDateTime maintenant = java.time.LocalDateTime.now();
        
        int jour_sys = maintenant.getDayOfMonth();
        int mois_sys = maintenant.getMonthValue();
        int annee_sys = maintenant.getYear();
        
        res = jsp;
        if(annee == annee_sys){
            if(mois == mois_sys){
                if(jour == jour_sys - 2){ res = avant_hier; }
                if(jour == jour_sys - 1){ res = hier; }
                if(jour == jour_sys){ res = aujourd_hui; }
                if(jour == jour_sys + 1){ res = demain; }
                if(jour == jour_sys + 2){ res = apres_demain; }
            }
        }
        
        return res;
    }
}
