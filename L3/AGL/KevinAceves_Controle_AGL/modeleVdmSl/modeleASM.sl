MACHINE TraitementMessages

TYPES
	MESSAGE; PRIORITE; ROBOT
	
VARIABLES
	message: set of MESSAGE
	priorites: set of PRIORITE
	messagesEdites: set of MESSAGE
	ordrePriorite: set of PRIORITE
	listeRobots: set of ROBOT
	boiteMessage: inmap MESSAGE to PRIORITE
	messageEnCours: inmap MESSAGE to ROBOT
	robotOcupees: set of ROBOT
	
	INVARIANT
		messagesEdites subset messages
		and ordrePriorite subset priorites
		and dom boiteMessages subset messageEdites
		and rng boiteMessages subset ordrePriorite
		and robotOcupees subset listeRobots
		and dom messageEnCours subset message
		and rng messageEnCours subset listeRobots
		
INITIALISATION
	initialiser --> ETAT
	post initialiser == 
	messagesEdites = messageEdites0,
	and ordrePriorite = ordrePriorite0,
	and listeRobots = listeRobots0,
	and boiteMessages = boiteMessages0,
	and messageEnCours = messageEnCours0,
	and robotOcupees = robotOcupees0;
	
OPERATIONS
	editer: MESSAGE ==> ETAT
	pre message not in messagesEdites
	post messagesEdites = messagesEdites~union{message};
	
	ranger: MESSAGE * PRIORITE ==> ETAT
	pre
		message not in messagesEdites
		and priorite in ordrePriorite
		and message not in set dom boiteMessages
	post boiteMessages = boiteMessages~munion{message|->priorite};
	
	preempter: MESSAGE * ROBOT ==> ETAT
	pre
		message in dom boiteMessages
		and robot not in robotOcupees
		and message not in dom messageEnCours
	post messageEnCours = messageEnCours~munion{message|->robot};
	
	retirerMessage: MESSAGE ==> ETAT
	pre message in dom messageEnCours
	post boiteMessages = {message} <--:boiteMessages~;
	
	
	/ operations d'observation
	edites: () ==> set of MESSAGE
	enAttente: () ==> inmap MESSAGE to PRIORITE
	plusPrioritaire: () ==> MESSAGE
	enCours: () ==> inmap MESSAGE to ROBOT
	quel_message: ROBOT --/-> MESSAGE
	quel_robot: MESSAGE --/-> ROBOT
	
FIN TraitementMessages
	
	
	
	
	
	
	
	