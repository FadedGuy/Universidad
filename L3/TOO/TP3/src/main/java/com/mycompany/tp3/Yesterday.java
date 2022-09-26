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
    
    Yesterday(final int jour, final int mois, final int annee, String resultat){
        assert(jour > 0 && mois > 0 && annee > 0);
        assert(jour <= 31 && mois <= 12);
        
        java.time.LocalDateTime maintenant = java.time.LocalDateTime.now();
        
        int jour_sys = maintenant.getDayOfMonth();
        int mois_sys = maintenant.getMonthValue();
        int annee_sys = maintenant.getYear();
        
//        System.out.println(jour_sys + "-" + mois_sys + "-" + annee_sys);
        
        
    }
    
}
