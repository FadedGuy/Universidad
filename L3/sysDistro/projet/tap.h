#ifndef TAP
#define TAP

#define KEG_CAPACITY 5.0
#define SERVE_HALF_PINT 2
#define SERVE_PINT 4

typedef enum {
    AMBER = 1,
    LAGER,
} beer_type_t;

typedef struct{
    beer_type_t type;
    char* name;
    float quantity;
    float capacity;
} tap_t;


#endif