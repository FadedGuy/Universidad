#include <iostream>
using namespace std;

bool anneBissextile(int anne){
    return (((anne%4 == 0) && (anne%100 != 0)) || (anne%400 == 0));
}

int nombreJours(int mois, int anne){
    int jourMax;

    if(mois == 1 || mois == 3 || mois == 5 || mois == 7 || mois == 8 || mois == 10 || mois == 12){
        return 31;
    }
    else{
        if(mois == 4 || mois == 6 || mois == 9 || mois == 11){
            return 30;
        }
        else{
            if(anneBissextile(anne)){
                return 29;
            }
            else{
                return 28;
            }
        }
    }
}

int main(){
    int jour, mois, anne, joursMax, jourL, moisL, anneL;

    cout<<"Donne le jour: ";
    cin>>jour;
    cout<<"Donne le mois (1-12): ";
    cin>>mois;
    cout<<"Donne le anne: ";
    cin>>anne;

    joursMax = nombreJours(mois, anne);
    if(jour < joursMax){
        //Jour prochain
        jourL = jour+1;
        moisL = mois;
        anneL = anne;
    }
    else{
        if(jour == joursMax && mois != 12){
            //Mois prochain
            jourL = 1;
            moisL = mois+1;
            anneL = anne;
        }
        else{
            if(jour == joursMax && mois == 12){
                //Anne prochain
                jourL = 1;
                moisL = 1;
                anneL = anne+1;
            }
            else{
                cout<<"Jour ou mois non valide\n";
            }
        }
    }
    cout<<"Aujord'hui est le: "<<jour<<"/"<<mois<<"/"<<anne<<"\n";
    cout<<"Lendemain sera le: "<<jourL<<"/"<<moisL<<"/"<<anneL<<"\n";
}