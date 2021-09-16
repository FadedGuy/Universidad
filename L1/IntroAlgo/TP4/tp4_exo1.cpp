#include <iostream>
using namespace std;

bool anneBissextile(int anne){
    return ((anne%4 == 0 && anne%100 != 0) || (anne%400 == 0));
}

int main(){
    int jour, mois, anne;
    int jour_mois[] = {30,27,30,29,30,29,30,30,29,30,29,30};

    cout<<"Donne le jour: ";
    cin>>jour;
    cout<<"Donne le mois (1-12): ";
    cin>>mois;
    cout<<"Donne le anne: ";
    cin>>anne;

    if(mois >= 1 && mois <= 12){
        if(jour >= 1 && jour <= jour_mois[mois-1]){
            //Jour prochain
            cout<<"Aujord'hui est le: "<<jour<<"/"<<mois<<"/"<<anne<<"\n";
            cout<<"Lendemain sera le: "<<jour+1<<"/"<<mois<<"/"<<anne<<"\n";
        }
        else{
            if((jour == jour_mois[mois-1]+1) || (mois == 2 && (jour == 28 || jour == 29) && anneBissextile(anne))){
                if(mois != 12){
                    if(mois == 2 && jour == 28 && anneBissextile(anne)){
                        //Jour prochain bissextile
                        cout<<"Aujord'hui est le: "<<jour<<"/"<<mois<<"/"<<anne<<"\n";
                        cout<<"Lendemain sera le: "<<jour+1<<"/"<<mois<<"/"<<anne<<"\n";
                    }
                    else{
                        //Mois prochain
                        cout<<"Aujord'hui est le: "<<jour<<"/"<<mois<<"/"<<anne<<"\n";
                        cout<<"Lendemain sera le: "<<1<<"/"<<mois+1<<"/"<<anne<<"\n";
                    }
                }
                else{
                    //Anne prochain
                    cout<<"Aujord'hui est le: "<<jour<<"/"<<mois<<"/"<<anne<<"\n";
                    cout<<"Lendemain sera le: "<<1<<"/"<<1<<"/"<<anne+1<<"\n";
                }
            }
            else{
                cerr<<"Jour non valide\n";
            }
        }
    }
    else{
        cerr<<"Mois non valide\n";
    }
    return 0;
}