let nombre;

do {
  nombre = parseInt(prompt('Entrez un nombre entre 10 et 20'));
} while (!((nombre >= 10 && nombre <= 20) && (nombre % 2 != 0)));

alert(nombre + ' est bien un entier impair dans [10,20]');