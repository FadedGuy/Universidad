#include <iostream>
#include <cstring>

#define MAX 10
using namespace std;

struct article{
  int code;
  float prix;
  char nom[20];
}articles[MAX];

bool chercherCode(struct article art[], int nbMax, int code){
  for(int i = 0; i < nbMax; i++){
    if(art[i].code == code){
      return true;
    }
  }
  return false;
}

main()
{
  articles[0].code = 25;
  articles[0].prix = 35;
  strcpy(articles[0].nom, "Centrifugeuse");
  articles[1].code = 16;
  articles[1].prix = 29.90;
  strcpy(articles[1].nom, "Grille-pain");
  articles[2].code = 26;
  articles[2].prix = 44.90;
  strcpy(articles[2].nom, "Fout a raclette");

  int nbFacturer, somTotal, code, articlesExistant;
  articlesExistant = 3;

  cout<<"Combien d'article a facturer ? "; cin>>nbFacturer;
  for(int i = 1; i <= nbFacturer; i++){
    cout<<"Code article ? "; cin>>code;
    if(chercherCode(articles, articlesExistant, code)){
      cout<<"code trouve";
    }else{
      do{
        cout<<"Code article ? "; cin>>code;
      }while(!chercherCode(articles, articlesExistant, code))
    }
    //Chercher code
  }

}
