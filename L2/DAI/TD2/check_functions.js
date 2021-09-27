//--- Vérification de la nature des caractères

function isNumber(c) {
  return !isNaN(c * 1); // cadeau !  isNaN == is Not a Number (inclus dans Javascrit)
}                       // On tente la conversion de caractère en nombre avec * 1

function isLowerCaseLetter(c) {
  return c === c.toLowerCase() && isLetter(c); // TODO
}

function isUpperCaseLetter(c) {
  return c === c.toUpperCase() && isLetter(c); // TODO
}

function isLetter(c) {
  return c.toUpperCase() !== c.toLowerCase(); // TODO
}

function isLetterOrNumber(c) {
  return ((c.toUpperCase() !== c.toLowerCase()) || (c >= '0' && c <= '9')); // TODO
}

// Vérifie si la longueur de str est dans [lenMin, lenMax]
function checkLength(str, lenMin, lenMax) {
  return str.length >= lenMin && str.length <= lenMax; // TODO
}

//--- Vérification de la conformité des chaînes de caractères

// Vérifie s'il n'y a que des caractères autorisés (lettres et chiffres)
function checkAllowedChars(str) {
  for(let i = 0; i < str.length; i++){
    if(!isLetterOrNumber(str[i])){
      return false;
    }
  }
  return str.length > 0; // TODO
}

// Vérifie si str contient au moins min caractères autorisés par isCharFunc
// exemple d'appel :
//    checkMinChars('ab12+-', 2, isLowerCaseLetter) vérifie si 'ab12+-' contient
//                                                  au moins deux minuscules :
//                                                  Renvoie 'true'.
function checkMinChars(str, min = 1, isCharFunc = isLetterOrNumber) {
  let cnt = 0;
  for(let i = 0; i < str.length; i++){
    console.log(str[i] + " " + isCharFunc(str[i]));
    cnt += isCharFunc(str[i]);
    if(cnt >= min){
      return true;
    }
  }
  return false;
}

//--- Tests ---
// Tous doivent afficher '+ Passed' !
// utilisation : test(résultatAttendu, functionÀTester, arg1, ..., argN)

const faireTests = true;

if (faireTests) {

  let ft = 0;  // failed tests

  console.log('=== Test des fonctions ===');

  console.log('--- est un nombre ---');
  ft += ! test(true,  isNumber, '1');
  ft += ! test(false, isNumber, 'a');

  console.log('--- est une minuscule ---');
  ft += ! test(true,  isLowerCaseLetter, 'a');
  ft += ! test(false, isLowerCaseLetter, 'A');

  console.log('--- est une majuscule ---');
  ft += ! test(true,  isUpperCaseLetter, 'A');
  ft += ! test(false, isUpperCaseLetter, 'a');

  console.log('--- est une lettre ---');
  ft += ! test(true,  isLetter, 'a');
  ft += ! test(false, isLetter, '1');

  console.log('--- Entre 8 et 10 caractères ---');
  ft += ! test(true,  checkLength, '12345678', 8, 10);
  ft += ! test(false, checkLength, '1234567', 8, 10);
  ft += ! test(false, checkLength, '12345678901', 8, 10);

  console.log('--- Seulement composé de lettres et de chiffres ---');
  ft += ! test(true,  checkAllowedChars, 'abcABC123'); //
  ft += ! test(false, checkAllowedChars, 'abcABC12+');

  console.log('--- Au moins 1 majuscule ---');
  ft += ! test(true,  checkMinChars, 'aB12+-', 1, isUpperCaseLetter);
  ft += ! test(false, checkMinChars, 'ab12+-', 1, isUpperCaseLetter);

  console.log('--- Au moins 2 minuscules ---');
  ft += ! test(true,  checkMinChars, 'ab12+-', 2, isLowerCaseLetter);
  ft += ! test(false, checkMinChars, 'aB12+-', 2, isLowerCaseLetter);

  console.log('--- Au moins 2 chiffres ---');
  ft += ! test(true,  checkMinChars, 'aB123+-', 2, isNumber);
  ft += ! test(false, checkMinChars, 'abcd3+-', 2, isNumber);

  console.log(`=== ${ft} test(s) raté(s) ! ===`);
}

// Fonction de test
// (ne pas toucher...)
function test() {
  let [result, func, ...args] = arguments;
  let res = func(...args) === result
  let passedFailed = res ? '+ Passed' : '- Failed';
  let sign         = res ?    '==='   :    '!==';
  let message = `${passedFailed}: ${func.name}(${args.map(v => v.name || v)
                .join(', ')}) ${sign} ${result}`;
  if (res) {console.log(message);} else {console.error(message);}
  return res;
}
