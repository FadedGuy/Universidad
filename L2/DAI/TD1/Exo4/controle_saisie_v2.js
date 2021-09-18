let nombre, err;
let message = '', eEnt,eImpar, eInf10, eSup20;
do {
  err = '';
  message = message + 'Entrez un entier impair dans [10,20]';
  nombre = prompt(message);
  eEnt = parseInt(nombre) == nombre;
  if(!eEnt){
    err = '1 erreur: ' + nombre + ' nest pas entier !';
  }
  eImpar = nombre % 2 == 1;
  if(!eImpar){
    if(err == ''){
      err = '1 erreur: ' + nombre + ' nest pas impair !';
    }else{
      err = '2 erreurs: ' + nombre + ' nest ni entier ni impair !'
    }
  }
  eInf10 = nombre >= 10;
  if(!eInf10){
    if(err == ''){
      err = '1 erreur: ' + nombre + ' nest pas superieur a 10 !';
    }else{
      err = '2 erreurs: ' + nombre + ' nest ni entier ni impair !'
    }
  }

  eSup20 = nombre <= 20;

  message = err +'\n';
} while (!(eInf10 && eSup20 && eEnt && eImpar));

alert(nombre + ' est bien un entier impair dans [10,20]');