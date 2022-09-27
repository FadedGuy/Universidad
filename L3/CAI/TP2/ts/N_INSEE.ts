enum Result {
    Format = "Invalid format",
    Key = "Invalid key",
    Ok = "Ok",
}

export default class N_INSEE {
    private _result: Result;
    get result(): Result {
        return this._result;
    }

    constructor(private readonly _n_insee: number, private readonly _clef: number) {
        if (this._n_insee.toString().match("[1-2]\\d{12}")) {
            if (this._calcul_clef())
                this._result = Result.Ok;
            else this._result = Result.Key;
        } else
            this._result = Result.Format;
    }

    private _calcul_clef(): boolean {
        if ((97 - (this._n_insee % 97)) === this._clef)
            return true;
        else
            return false;
    }
}
