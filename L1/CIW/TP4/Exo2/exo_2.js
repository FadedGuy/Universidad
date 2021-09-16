console.log("je suis exo_2.js");

function calculeAge(){
    let anneeNaissance = window.prompt("Quelle est votre annee de naissance ?");
    let anneeCourant = new Date();
    anneeCourant = anneeCourant.getFullYear();

    window.alert("Vous avez " + (anneeCourant - anneeNaissance -1) + " ou " + (anneeCourant - anneeNaissance) + " ans.");
}