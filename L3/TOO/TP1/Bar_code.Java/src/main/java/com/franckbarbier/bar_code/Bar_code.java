package com.franckbarbier.bar_code;

enum Result {
    Correct,
    Incorrect,
    Invalid_format
}

public class Bar_code {

    private final java.util.ArrayList<Integer> _bar_code = new java.util.ArrayList<>();
    public final Result correct;

    Bar_code(final String bar_code) throws NumberFormatException {
        for (String s : bar_code.split("")) { // 'bar_code' est découpé en éléments...
            try {
                int element = Integer.valueOf(s); // Conversion en entier pour les calculs...
                _bar_code.add(element);
            } catch (NumberFormatException nfe) {
                correct = Result.Invalid_format;
                throw nfe;
            }
        }
        correct = _check_sum() ? Result.Correct : Result.Incorrect;
    }

    private boolean _check_sum() { // Méthode de calcul du "check sum" :
        // Example: 5 0 1 0 3 5 6 8 2 3 3 5 7
        // Step 1: ajouter les chiffres de rang impair en partant de la gauche (ne pas compter le dernier chiffre de contrôle, i.e., '7')
        // Step 2: ajouter au résultat trois fois la somme des chiffres de rang pair toujours en partant de la gauche
        // R = (5 + 1 + 3 + 6 + 2 + 3) + 3 * (0 + 0 + 5 + 8 + 3 + 5) = 20 + (3 * 21) = 83
        // Step 3: ajouter le chiffre de contrôle (i.e., '7') à R soit 83 + 7 = 90
        // Step 4: le code barre est correct si le résultat final est un multiple de '10'
        int impair = 0;
        int pair = 0; 
        int ctrl = 0;
        
        for(int i = 0; i < _bar_code.size(); i++){
            if(i != _bar_code.size() - 1){
                if(i % 2 == 0){
                    pair += _bar_code.get(i);
                }
                else{
                    impair += _bar_code.get(i);
                }
            }
        }
        
        ctrl = pair + (3 * impair) + _bar_code.get(_bar_code.size()-1);
        
        return ctrl % 10 == 0; // A remplacer
    }

    private boolean _alternative_check_sum() { // Autre méthode de calcul du "check sum" :
        // (5 + 1 + 3 + 6 + 2 + 3 + 7) + 3 * (0 + 0 + 5 + 8 + 3 + 5) = 90
        // Le code barre est correct si le résultat final est un multiple de '10'
        int pair = 0;
        int impair = 0;
        int ctrl = 0;
        int i = 0;
        
        for(Integer _bar_code1 : _bar_code){
            if(i == 0){
                pair += _bar_code1;
                i = 1;
            }
            else{
                impair += _bar_code1;
                i = 0;
            }
        }
        
        ctrl = pair + (3 * impair);
        
        return ctrl % 10 == 0; // A remplacer
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (Integer _bar_code1 : _bar_code) {
            sb.append(_bar_code1);
        }
        return sb.toString(); // A remplacer
    }
}
