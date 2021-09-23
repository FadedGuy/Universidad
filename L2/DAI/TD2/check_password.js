

function checkPassword() {
  const pw     = document.getElementById('passwd').value;
  const resElt = document.getElementById('result');

  const c1 = checkLength(pw,8,10);
  const c2 = false; // TODO: Modifier...
  const c3 = false; // TODO: Modifier...
  const c4 = false; // TODO: Modifier...
  const c5 = false; // TODO: Modifier...
  const isValid = c1 && c2 && c3 && c4 && c5;
  const validText = isValid ? 'valide !' : 'invalide...';

  const cvalid   = 'class="valid"'
  const cinvalid = 'class="invalid"'
  const ch1 = c1 ? cvalid : cinvalid;
  // TODO: pareil pour c2 à c5...

  const html = `
  <style>
    .valid   { color:green; }
    .invalid { color:red;   }
  </style>
  <p>Votre mot de passe doit contenir :</p>
  <ul>
    <li ${ch1}>entre 8 et 10 caractères</li>
    <li       >que des lettres et des chiffres</li>
    <li       >au moins 2 minuscules</li>
    <li       >au moins 1 majuscules</li>
    <li       >au moins 2 chiffres</li>
  </ul>
  <p>Le mot de passe est ${validText}</p>
  `;

  resElt.innerHTML = html;
}
