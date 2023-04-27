#ifndef TAP
#define TAP

/*
    Pint sizes differ from the US, UK and rest
        US: 0.473176 L
        UK: 0.568 L
        Metric world: 0.5 L

    Using 0.5 for simplicity
*/

#define KEG_CAPACITY 5.0
#define SERVE_HALF_PINT_TIME 2
#define SERVE_PINT_TIME 4
#define HALF_PINT_QTY 0.25
#define PINT_QTY 0.5

#define SHM_KEY 99
#define N_TAPS 2
#define SEM_KEY "tap_semaphore"
#define MAX_LENGTH_NAME 20

typedef enum {
    AMBER = 1,
    LAGER,
} beer_type_t;

typedef struct{
    beer_type_t type;
    char        name[MAX_LENGTH_NAME];
    float       quantity;
    float       capacity;
} tap_t;

/**
 * Creates an SHM for tap_t with the key and size given
 * @param key Key of the SHM
 * @param nTaps Number of taps
 * @return 0 on sucess, -1 for errors
*/
int createTapSHM(int key, int nTaps);

/**
 * Retrieves an SHM for tap_t from the key with size given
 * @param key Key of the SHM
 * @param nTaps Number of taps
 * @return 0 on sucess, -1 for errors
*/
int retrieveTapSHM(int key, int nTaps);

/**
 * Attach to a SHM with the SHM Id
 * @param shmid SHM ID
 * @return NULL for errors, pointer to SHM otherwise
*/
tap_t* attachTapSHM(const int shmid);

/**
 * Detach a pointer from the SHM
 * @param taps Pointer to attached variable
 * @return 0 on sucess, -1 for errors
*/
int detachTapSHM(tap_t* taps);

/**
 * Removes the SHM with shmId from the system
 * @param shmid shmId to remove
 * @return 0 on sucess, -1 for errors
*/
int removeTapSHM(const int shmid);

/**
 * Retrieves a semaphore with key, creates it if non existent
 * @param semaphore Pointer to the array of semaphores
 * @param semSize Size of the array
 * @param key Key of the semaphore
 * @return 0 on sucess, -1 for errors
*/
int openTapSemaphore(sem_t* semaphore[], const int semSize, const char* key);

/**
 * Closes a semaphore
 * @param semaphore Pointer to the array of semaphores
 * @param semSize Size of the array
 * @return 0 on sucess, -1 for errors
*/
int closeTapSemaphore(sem_t* semaphore[], const int semSize);

/**
 * Initializes the values of a tap with it's given type
 * @param sem Semaphore that controls the tap
 * @param tap Tap to initialize 
 * @param type Type of tap to initialize
 * @return 0 on sucess, -1 for errors
*/
int initializeTap(sem_t* sem, tap_t* tap, beer_type_t type);

/**
 * Serves qty of beer from tap
 * @param sem Semaphore that controls the tap
 * @param tap Tap that is being used to serve
 * @param qty Quantity of beer to serve
 * @return Remaining beer quantity on sucess, -1 for errors
*/
int serveBeer(sem_t* sem, tap_t* tap, const float qty);

/**
 * Gets the quantity of beer remaining in a keg
 * @param sem Semaphore that controls the tap
 * @param tap Tap to check
 * @return Quantity >= 0, -1 for errors
*/
float getQuantity(sem_t* sem, tap_t* tap);

/**
 * Verifies a given keg
 * @param sem Semaphore controlling tap
 * @param tap Tap to check levels
 * @param id Id of the keg being checked
 * @return 0 on sucess, -1 for errors
*/
int checkKeg(sem_t* sem, tap_t* tap, int id);

/**
 * Initializes an SHM and attaches to it
 * @param key SHM key
 * @param nTaps Number of taps
 * @param taps Taps associated with shm
 * @return shmId on sucess, -1 for errors
*/
int initSHM(const int key, const int nTaps, tap_t** taps);

/**
 * Getter for the beer name of a tap
 * @param sem Semaphore controlling tap
 * @param tap Tap to use
 * @return Pointer to name on sucess, null otherwise
*/
char* getBeerName(sem_t* sem, tap_t* tap);

/**
 * Getter for beer type
 * @param sem Semaphore controlling tap
 * @param tap Tap to use
 * @return Beer type on sucess, -1 for errors
*/
int getBeerType(sem_t* sem, tap_t* tap);

/**
 * Refills a given tap
 * @param sem Semaphore controlling tap
 * @param tap Tap to fill back up to capacity
 * @return New quantity on sucess, -1 for errors
*/
int refillTap(sem_t* sem, tap_t* tap);

/**
 * Setter for tap name
 * @param sem Semaphore controlling tap
 * @param tap Tap to change name
 * @param name Name to set
 * @return 0 on sucess, -1 for errors
*/
int setTapName(sem_t* sem, tap_t* tap, const char* name);

/**
 * Setter for tap type
 * @param sem Semaphore controlling tap
 * @param tap Tap to change type
 * @param type New type
 * @return 0 on sucess, -1 for errors
*/
int setTapType(sem_t* sem, tap_t* tap, const beer_type_t type);

/**
 * Setter for tap name via string
 * @param sem Semaphore controlling tap
 * @param Tap Tap to change name
 * @param type Type as string
 * @return 0 on sucess, -1 for errors
*/
int setTapTypeFromString(sem_t* sem, tap_t* tap, const char* type);

#endif