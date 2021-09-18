let message = '';

let i = 9;
while (i>=0) {
  message = message + i;
  if(i != 0){
    message = message +  ', ';
  }
  i = i-1;
}

alert(message);