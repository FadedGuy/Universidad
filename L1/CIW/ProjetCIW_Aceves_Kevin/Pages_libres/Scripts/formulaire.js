function memeAdresse(){
    var checkBox = document.getElementById("meme_fact");
    var adresseLivr = document.getElementById("livr_adresse");
    var codePostalLivr = document.getElementById("livr_code_postal");
    var villeLivr = document.getElementById("livr_ville");

    if(checkBox.checked){
        console.log("Checked");
        var adresseFact = document.getElementById("fact_adresse");
        var codePostalFact = document.getElementById("fact_code_postal");
        var villeFact = document.getElementById("fact_ville");
        

        adresseLivr.value = adresseFact.value;
        codePostalLivr.value = codePostalFact.value;
        villeLivr.value = villeFact.value;

        adresseLivr.readOnly = true;
        codePostalLivr.readOnly = true;
        villeLivr.readOnly = true;
    }
    else{
        console.log("Not Checked");

        adresseLivr.value = "";
        codePostalLivr.value = "";
        villeLivr.value = "";

        adresseLivr.readOnly = false;
        codePostalLivr.readOnly = false;
        villeLivr.readOnly = false;
    }
}