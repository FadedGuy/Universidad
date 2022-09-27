var Result;
(function (Result) {
    Result["Format"] = "Invalid format";
    Result["Key"] = "Invalid key";
    Result["Ok"] = "Ok";
})(Result || (Result = {}));
export default class N_INSEE {
    constructor(_n_insee, _clef) {
        this._n_insee = _n_insee;
        this._clef = _clef;
        if (this._n_insee.toString().match("[1-2]\\d{12}")) {
            if (this._calcul_clef())
                this._result = Result.Ok;
            else
                this._result = Result.Key;
        }
        else
            this._result = Result.Format;
    }
    get result() {
        return this._result;
    }
    _calcul_clef() {
        if ((97 - (this._n_insee % 97)) === this._clef)
            return true;
        else
            return false;
    }
}
