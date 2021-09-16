console.log("je suis exo_1.js");

function plusGrand2(nom1, nom2){
    return nom1 > nom2 ? nom1 : nom2;
}

function plusGrand3(nom1, nom2, nom3){
    let grand = plusGrand2(nom1, nom2);
    return grand > nom3 ? grand : nom3;
}