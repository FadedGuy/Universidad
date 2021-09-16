//8-9-10
console.log("je suis exo_8.js");

let valide = true;

function infoNav(){
    alert("Informations sur votre navigateur :\nNom : " + navigator.appName + "\nVersion : " + navigator.appVersion + "\nLangue : " + navigator.language);
}

function clicDroitInterdit(){
    alert("Clic droit interdit ! :D");
    return false;
}

function donneMotPasse(){
    if(valide){
        let a = window.prompt("Donne la mot de passe :");
        if(a == "h565s" && valide == true){
            return true;
            } else{
                valide = false;
                return false;
            }  
    } else{
        return false;
    }
    
    
}