

let message = '';

let i;
for (i=0; i<9; i=i+1) {
    message = message + i + ', ';
}
message = message + i;

// for(let i = 0; i < 10; i=i+1){
//   message = message + i;
//   if(i != 9){
//     message = message + ', '
//   }
// }

alert('Les dix chiffres : ' + message);

// affiche : Les dix chiffres : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
