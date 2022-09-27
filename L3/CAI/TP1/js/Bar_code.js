var Result;
(function (Result) {
    Result["Correct"] = "Correct";
    Result["Incorrect"] = "Incorrect";
    Result["Invalid_format"] = "Invalid format";
})(Result || (Result = {}));
export default class Bar_code {
    constructor(bar_code) {
        this._bar_code = new Array;
        this._correct = Result.Invalid_format; // Default value...
        bar_code.split("").forEach((s) => {
            const element = parseInt(s); // Conversion en entier pour les calculs...
            if (isNaN(element))
                throw new Error(Result.Invalid_format);
            else
                this._bar_code.push(element);
        });
        this._correct = this._check_sum() ? Result.Correct : Result.Incorrect;
    }
    get correct() {
        return this._correct;
    }
    _check_sum() {
        // https://barcode-coder.com/fr/specification-ean-13-102.html
        // Example: 2 1 0 9 8 7 6 5 4 3 2 1 0
        // Step 1: ajouter les chiffres de rang impair en partant de la droite (ne pas compter le dernier chiffre de contrôle, i.e., '0')
        // Step 2: ajouter au résultat trois fois la somme des chiffres de rang pair toujours en partant de la droite
        // Check sum: (10 - [ (3 * "impairs" + "pairs") modulo 10 ]) modulo 10
        return true; // A remplacer
    }
    _alternative_check_sum_() {
        // Autre méthode : https://fr.wikipedia.org/wiki/EAN_13
        return true; // A remplacer
    }
    toString() {
        return ""; // A remplacer
    }
}
//# sourceMappingURL=Bar_code.js.map