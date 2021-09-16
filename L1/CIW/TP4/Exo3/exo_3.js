console.log("je suis exo_3.js");


function dataIMC(){
    let poids = window.prompt("Donne votre poid en kg: ");
    let taille = window.prompt("Donne votre taille en cm: ");

    window.alert("Votre IMC est: " + imc(poids, taille) + ".");
}

function imc(poids, taille){
    return (poids / carre(taille/100));
}