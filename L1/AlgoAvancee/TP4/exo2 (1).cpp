#include <iostream>
#include <cstring>
#include <stdio.h>

#define MAX 10
using namespace std;

struct article{
  int code;
  float prix;
  char nom[20];
  int nbEle;
}articles[MAX];

int chercherCode(struct article art[], int nbMax, int code){
  for(int i = 0; i < nbMax; i++){
    if(art[i].code == code){
      return i;
    }
  }
  return -1;
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

  struct article facture[MAX]; 
  int nbFacturer, code, articlesExistant;
  float somTotal;
  articlesExistant = 3;
  somTotal = 0;

  cout<<"Combien d'article a facturer ? "; cin>>nbFacturer;

  for(int i = 0; i < nbFacturer; i++){
    int iCode;
    cout<<"Code article ? "; cin>>code;
    if(chercherCode(articles, articlesExistant, code) == -1){
      do{
        cout<<"** Article inexistant - Redonnez le code : "; cin>>code;
      }while(chercherCode(articles, articlesExistant, code) == -1);
    }

    iCode = chercherCode(articles, articlesExistant, code);
    
    cout<<"Quantite de "<<articles[iCode].nom<<" au prix unitaire de "<<articles[iCode].prix<<" euros? ";
    cin>>facture[i].nbEle;

    strcpy(facture[i].nom, articles[iCode].nom);
    facture[i].prix = articles[iCode].prix;
    somTotal += facture[i].prix * facture[i].nbEle;
    //Chercher code
  }

  cout<<"\t\tFacture\n\n";
  cout<<"ARTICLE\t\tNBRE\tP-UNIT\tMONTANT\n";
  for(int i = 0; i < nbFacturer; i++){
    printf("%s \t %d \t %.2f \t %.2f \n", facture[i].nom, facture[i].nbEle, facture[i].prix, facture[i].prix*facture[i].nbEle);
  }
  printf("\t TOTAL\t\t %.2f \n", somTotal);
}

int main()
{
    ios::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<ll> a(n);
    for (auto& i : a)cin >> i;
    vector<int> cmp(n+3); cmp[1] = 0; 
    for (int i = 2; i <= n; i++) {
        if (a[i - 1] < a[i - 2])cmp[i] = 2;
        else if (a[i - 1] > a[i - 2])cmp[i] = 1;
        else cmp[i] = 0; // (equal)
    }
    vector<ll>pref(n + 3); pref[0] = 0;
    pref[1] = 0;
    int lastOne = 0;
    for (int i = 2; i <= n; i++) {
        pref[i] = pref[i - 1];
        if ((lastOne == 0&&cmp[i]!=0) || (cmp[i] != 0 && cmp[i] != lastOne))++pref[i];
        lastOne = (cmp[i] ? cmp[i] : lastOne);
    }
    //for (int i = 1; i <= n; i++)cout << cmp[i] << ' '; cout << '\n';
    //for (int i = 1; i <= n; i++)cout << pref[i] << ' '; cout << '\n';
    vector<int>uniquePos;
    for (int i = 1; i <= n; i++) {
        if (cmp[i])uniquePos.push_back(i);
    }
    while (m--) {
        int l, r;
        cin >> l >> r;
        if (r - l <= 1) { 
            cout << "Yes\n";
            continue;
        }
        auto it = lower_bound(uniquePos.begin(), uniquePos.end(), l + 1);
        if (pref[r] - pref[*it] <= 1) {
            if (pref[r] - pref[*it] <= 0) {
                cout << "Yes\n";
                continue;
            }
            if (it == uniquePos.end() || (*it) >= r || cmp[(*it)] == 1) {
                cout << "Yes\n";
                continue;
            }
        }
        cout << "No\n";
    }
    return 0;
}