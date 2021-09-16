
function changeImageM1(url, nom) {
  console.log("DEBUG : changeImageM1 : url = "+url+", nom = "+nom);
  let element = document.getElementById("id_quoi");
  element.textContent = nom;
  document.getElementById("id_image").src = url;
}

function changeImageM2(id_url, id_nom, url, nom) {
  console.log("DEBUG : changeImageM2 : id_url = " + id_url + ", id_nom = " + id_nom
              +", url = " + url + ", nom = " + nom);
  document.getElementById(id_nom).textContent = nom;
  document.getElementById(id_url).src = url;
}

function changeImageM3(url, nom){
  console.log("DEBUG : changeImageM3 : url = "+url+", nom = "+nom);
  var el = document.querySelector("#id_quoi");
  var img = document.querySelector("p img");
  el.textContent = nom;
  img.src = url;
}

function changeInitial(id_url,id_nom, url, nom){
  console.log("DEBUG : changeInitial : id_url = " + id_url + ", id_nom = " + id_nom
              +", url = " + url + ", nom = " + nom);
  document.getElementById(id_nom).textContent = nom;
  document.getElementById(id_url).src = url;
}
