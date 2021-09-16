#include <cstdlib>
#include <iostream>
#include <vector>
#include <math.h>

//pour compiler sous linux:
// g++ -o convfrac convfrac.cc
int main(int argc, char** argv)
{


  if (argc!=3)
  {
    std::cerr<<"Usage:"<<'\n';
    std::cerr<<"\t convfrac p/q base"<<'\n';
    return 1;
  }
  std::string frac=argv[1];
  std::string::size_type pos   = frac.find_first_of('/', 0);
  std::string num_string=  frac.substr(0, pos);
  std::string den_string=  frac.substr(pos+1,frac.size()-1 );
  int num=atoi(num_string.c_str());
  int den=atoi(den_string.c_str());
  int xint=num/den;
  int b=atoi(argv[2]);


// conversion de la partie entière
  int q=xint;
  std::vector<int> vint;
  int s;
  while (q!=0)
  {
    s=q%b;
    vint.push_back(s);
    q=q/b;
  }
  if (vint.size()==0) vint.push_back(0);

/* conversion de la partie fractionnaire
 * par multiplications successives.
 * Dès que la partie fractionnaire s'annule
 * où qu'une période est détectée, la boucle while s'arrête.
*/
  //vecteur des parties fractionnaires
  std::vector<int> vfrac;
  //vecteur des chiffres
  std::vector<int> vs;
  bool c=true;
  bool period_found=false;
  int periodbegin;
  num=num%den;
  while(c && num>0)
  {
    num=b*num;
    vfrac.push_back(num);
    s=num/den;
    for (int i=0; i<vfrac.size()-1;i++)
    {
      if (vfrac[i]==num)
      {
        period_found=true;
        periodbegin=i;
        c=false;
      }
    }
    num=num%den;
    if (!period_found) vs.push_back(s);
  }


// écriture des résultats
  std::cout<<"\n("<<frac<<")_10=(";
  for (int i=vint.size()-1; i>=0;i-- )
  {
    std::cout<<vint[i];
  }
  if (vs.size()>0)
  {
    std::cout<<".";
    if (period_found)
    {
      for (int i=0; i<periodbegin;i++)
      {
        std::cout<<vs[i];
      }
      std::cout<<"[";
      for (int i=periodbegin; i<vs.size();i++)
      {
        std::cout<<vs[i];
      }
      std::cout<<"]...";
    }
    else
    {
      for (int i=0; i<vs.size();i++)
      {
        std::cout<<vs[i];
      }
    }
  }

  std::cout<<")_"<<b<<'\n';
  if (period_found)
  {
    std::cout<<"periode de longueur :"<<vs.size()-periodbegin<<'\n';
  }
  std::cout<<'\n';

    return 0;
}
