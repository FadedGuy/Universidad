function changeCouleur(){ 
    console.log("Changing color");
    let r, g, b;

    r = Math.floor(Math.random() * 255);
    g = Math.floor(Math.random() * 255);
    b = Math.floor(Math.random() * 255);
    document.body.style.backgroundColor = "rgb("+r+","+g+","+b+")";

    return false;
}

function changeImageM1(url, nom) {
    console.log("DEBUG : changeImageM1 : url = "+url+", nom = "+nom);
    var bodyTag = document.body;
    var p1Tag = bodyTag.childNodes[3].childNodes[3];
    var bTag = p1Tag.lastChild;
    var p2Tag = bodyTag.childNodes[3].childNodes[5];
    var imgTag = p2Tag.firstChild;

    bTag.innerHTML = nom;
    imgTag.src = url;
}
  
function changeImageM2(id_url, id_nom, url, nom) {
    console.log("DEBUG : changeImageM2 : id_url = " + id_url + ", id_nom = " + id_nom
                +", url = " + url + ", nom = " + nom);
    var bTag = document.getElementById(id_nom);
    var imgTag = document.getElementById(id_url);

    bTag.innerHTML = nom;
    imgTag.src = url;
}

function changeImageM3(url, nom){
    console.log("DEBUG : changeImageM3 : url = " + url + ", nom = " + nom);
    var bTag = document.querySelector('b');
    var imgTag = document.querySelector('img');

    bTag.innerHTML = nom;
    imgTag.src = url;
}
  