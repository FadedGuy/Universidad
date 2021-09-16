console.log("je suis exo_7.js");

let maFenetre = null;

function ouvre(){
    if(maFenetre === null){
        maFenetre = window.open("https://www.youtube.com/watch?v=mP3fGkpmVM0&t=156s");
    } else{
        window.alert("Attention, une fenetre est deja ouverte");
    }
}

function ferme(){
    if(maFenetre !== null){
        maFenetre = window.close();
        maFenetre = null;
    } else{
        window.alert("Aucun fenetre n'est ouverte");
    }
}