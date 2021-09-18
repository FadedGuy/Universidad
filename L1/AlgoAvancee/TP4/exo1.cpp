#include <iostream>
#include <cstring>

using namespace std;

main()
{
  int jour;
  char mois[10];
  cout<<"Donne votre date de naissance (j/m): ";
  cin>>jour;
  cin>>mois;

  if((strcmp(mois, "decembre") == 0 && jour >= 23) || (strcmp(mois, "janvier") == 0 && jour <= 19)){
    cout<<"Capricorn";
  }else if((strcmp(mois, "janvier") == 0 && jour >= 20) || (strcmp(mois, "fevrier") == 0 && jour <= 19)){
    cout<<"Verseau";
  }else if((strcmp(mois, "fevrier") == 0 && jour >= 20) || (strcmp(mois, "mars") == 0 && jour <= 20)){
    cout<<"Poisson";
  }else if((strcmp(mois, "mars") == 0 && jour >= 21) || (strcmp(mois, "avril") == 0 && jour <= 19)){
    cout<<"Belier";
  }else if((strcmp(mois, "avril") == 0 && jour >= 20) || (strcmp(mois, "mai") == 0 && jour <= 20)){
    cout<<"Taureau";
  }else if((strcmp(mois, "mai") == 0 && jour >= 21) || (strcmp(mois, "juin") == 0 && jour <= 20)){
    cout<<"Gemeau";
  }else if((strcmp(mois, "juin") == 0 && jour >= 21) || (strcmp(mois, "juillet") == 0 && jour <= 21)){
    cout<<"Cancer";
  }else if((strcmp(mois, "juillet") == 0 && jour >= 22) || (strcmp(mois, "aout") == 0 && jour <= 22)){
    cout<<"Lion";
  }else if((strcmp(mois, "aout") == 0 && jour >= 23) || (strcmp(mois, "septembre") == 0 && jour <= 22)){
    cout<<"Vierge";
  }else if((strcmp(mois, "septembre") == 0 && jour >= 23) || (strcmp(mois, "octobre") == 0 && jour <= 22)){
    cout<<"Balance";
  }else if((strcmp(mois, "octobre") == 0 && jour >= 23) || (strcmp(mois, "novembre") == 0 && jour <= 21)){
    cout<<"Scorpion";
  }else if((strcmp(mois, "novembre") == 0 && jour >= 22) || (strcmp(mois, "decembre") == 0 && jour <= 22)){
    cout<<"Verseau";
  }else{
    cout<<"Date non valide";
  }

  cout<<endl;
}
