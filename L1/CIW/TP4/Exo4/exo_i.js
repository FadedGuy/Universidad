console.log("je suis exo_4.js");

function rebourse(a, b){
    let max = a > b ? a : b;
    let min = a < b ? a : b;

    for(max; max >= min; max--){
        console.log(max);
    }
}