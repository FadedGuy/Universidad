MACHINE pilotageMarche

TYPES
	OP; GARANTIE

VARIABLES
	
	enregistres:	SET[OP]
	validees: 		SET[GARANTIE]
	visees:				SET[OP]
	fini:					SET[OP]
	validePar:		INMAP[OP]/GARANTIE

INVARIANT

	dom validePar subset enregistres
	and 
	rng validePar subset validees
	and
	visees subset dom validePar
	and
	fini subset dom validePar

INITIALISATION

	initialiser -> ETAT
	post initialiser ==
		enregistres = enregistres(),
		validees = validees(),
		visees = {},
		fini = fini(),
		validePar = validePar()

OPERATIONS

	enregistrer: OP ==> ETAT
	pre operation not in set enregistres
	post enregistres = enregistres~union{operation};
	
	souscrire: GARANTIE ==> ETAT
	pre garantie not in validees
	post validees = validees~union{garantie};

	valider: OP * GARANTIE ==> ETAT
	pre operation in enregistres
			and garantie in validees
			and operation not in set dom validePar
			and garantie not in set rng validePar
	post validePar = validePar~munion{operation |-> garantie};
	
	viser: OP ==> ETAT
	pre operation in set dom validePar
	post visees = visees~union{operation};
	
	denouer: OP ==> ETAT
	pre operation in set viseees
	post operation not in set dom validePar;
	
	confirmer: OP ==> ETAT
	pre operation in set dom validePar
	post fini = fini~union{operation}
			 and validePar = {operation} <-: validePar~;
			 -- Ajouter operation a fini et effacer de validePar
			 
	enCours: () ==> set of OP
	
	validees: () ==> set of OP
	
	visees: () ==> set of OP
	
	denouees: () ==> set of OP
		post RESULT = visees \ visees inter dom validePar

	confirmees: () ==> set of OP

FIN pilotageMarche

Enregistres op -> Valider op avec depot -> Appel a la marge?
Oui -> Marge suivi ?
										Oui -> Confirmer bonne execution d'une operation
										Non -> Denouer
Non -> Confirmer bonne execution d'une operation