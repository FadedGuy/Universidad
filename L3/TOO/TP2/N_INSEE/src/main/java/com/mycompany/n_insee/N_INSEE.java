package com.mycompany.n_insee;
/**
 *
 * @author kasiordia
 */
public class N_INSEE {
    private final long _nInsee; 
    
    N_INSEE(final String n_insee){
        verification(n_insee);
        _nInsee = Long.parseLong(n_insee);
    }
    
    public long clef(){
        return 97 - (_nInsee % 97);
    }
    
    private void verification(String val){
        if(!java.util.regex.Pattern.matches("^[1-2]\\d{12}", val)){
            throw new RuntimeException("N INSEE ne respecte pas le format pour un N INSEE");
        }
    }
}
