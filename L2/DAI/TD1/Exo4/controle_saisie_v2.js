let nombre, err;
let message = '', eEnt,eImpar, eInf10, eSup20;

document.getElementById('nom').textContent = "...";

do {
  err = '';
  message = message + 'Entrez un entier impair dans [10,20]';
  nombre = prompt(message);
  eEnt = parseInt(nombre) == nombre;
  if(!eEnt){
    err = '1 erreur : ' + nombre + ' n\'est pas entier !';
  }
  
  eImpar = nombre % 2 == 1;
  if(!eImpar){
    if(err == ''){
      err = '1 erreur : ' + nombre + ' n\'est pas impair !';
    }else{
      err = '2 erreurs : ' + nombre + ' n\'est ni entier ni impair !'
    }
  }

  eInf10 = nombre >= 10;
  if(!eInf10){
    if(err == ''){
      err = '1 erreur : ' + nombre + ' n\'est pas supérieur à 10 !';
    }
    else{
      if(eEnt){
        err = '2 erreurs : ' + nombre + ' n\'est ni impair ni supérieur à 10 !'
      }else if(eImpar){
        err = '2 erreurs : ' + nombre + ' n\'est ni entier ni supérieur à 10 !'        
      }else{
        err = '3 erreurs : ' + nombre + ' n\'est ni entier ni impair ni supérieur à 10 !'
      }
    }
  }
  
  eSup20 = nombre <= 20;
  if(!eSup20){
    if(err == ''){
      err = '1 erreur : ' + nombre + ' n\'est pas inferieur a 20 !';
    }else if(err.search('entier') && !err.search('impair')){
      err = '2 erreurs : ' + nombre + ' n\'est ni entier ni inferieur a 20 !'
    }else if(err.search('impair') && !err.search('entier')){
      err = '2 erreurs : ' + nombre + ' n\'est ni impair ni inferieur a 20 !'
    }else {
      err = '3 erreurs : ' + nombre + ' n\'est ni entier ni impair ni inferieur a 20 !'
    }
  }

  if(!eSup20){
    if(err == ''){
      err = '1 erreur : ' + nombre + ' n\'est pas inférieur à 20 !';
    }
    else{
      if(eEnt){
        err = '2 erreurs : ' + nombre + ' n\'est ni impair ni inférieur à 20 !'
      }else if(eImpar){
        err = '2 erreurs : ' + nombre + ' n\'est ni entier ni inférieur à 20 !'        
      }else if(eEnt && eImpar){
        err = '3 erreurs : ' + nombre + ' n\'est ni entier ni impair ni inférieur à 20 !'
      }else{
        err = '4 erreurs : ' + nombre + ' n\'est ni entier ni impair ni supérieur à 10 inférieur à 20 !'
      }
    }
  }
  

  message = err +'\n';
} while (!(eInf10 && eSup20 && eEnt && eImpar));

alert(nombre + ' est bien un entier impair dans [10,20] !');
document.getElementById('nom').textContent = nombre;
