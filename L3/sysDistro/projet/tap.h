#ifndef TAP
#define TAP

#define KEG_CAPACITY 5.0
#define SERVE_HALF_PINT 2
#define SERVE_PINT 4

#define SHM_KEY 99
#define N_TAPS 2
#define SEM_KEY "tap_semaphore"

typedef enum {
    AMBER = 1,
    LAGER,
} beer_type_t;

typedef struct{
    beer_type_t type;
    char name[15];
    float quantity;
    float capacity;
} tap_t;


#endif