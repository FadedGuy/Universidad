/*
Emploi:
    classe: niveau des salaires pratiques
    type: specialisation <=> nature activite

EC A1 => min 40k an
EC A2 => max 60k an
EC B1 => activite=specialite
EC B2 => activite=pluridsciplinaire

certains emploi sont des stages
    S1 peut doboucher sur un emplo
    S2


Regles placement:
    R1: Offre A1 il est exclu de processus
    R2: 2 offre, offre 1 est annulee et exclu de processus
    R3: 3 tentatives pour une 2 emploi
    R4: B1 ne peut pas viser pour une 2 offre type B1
    R5: S1 elegible pour offres A1
    R6: S2 elegible juste pour A2

*/
#include <iostream>
#include <string>

using namespace std;

char ask_question(string question){
    char ans;

    cout << question << "\nReponse: ";
    cin >> ans;

    return ans;
}

int main(){
    char ans;

    cout << "Repondre les questions suivantes pour etre place avec oui(o) ou non(n)\n";

    if(ask_question("Avez vous obtenu une offre d'emploi de classe A1") == 'o'){
        cout << "Vous etes exclu du processus de placement\n";
    }
    else{
        if(ask_question("Avez vous recu une 2ieme offre d'emploi?") == 'o'){
            cout << "1ere offre annulee\nVous etes exclu du processus de placement\n";
        }
        else{
            if(ask_question("Avez vous refuse 3 offres differentes pour une 2eme emploi?") == 'o'){
                cout << "Maximum d'offres refuse\n";
            }
            else{
                if(ask_question("Avez vous obtenu un emploi de type B1?") == 'o'){
                    cout << "Vous ne peut pas viser que pour une 2eme offre de type B1\n";
                }
                else{
                    if(ask_question("Avez vous obtenu un stage de type S1?") == 'o'){
                        cout << "Vous etes elegible aux offres de classe A1\n";
                    }
                    else{
                        if(ask_question("Avez vous obtenu un stage de type S2?") == 'o'){
                            cout << "Vous eres elegible juste aux offres de classe A2\n";
                        }
                    }
                }
            }
        }
    }

    cout << "Processus de placement termine\n";

    return 0;
}