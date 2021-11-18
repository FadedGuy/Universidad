#ifndef BASE_H
#define BASE_H
#include "facility.h" /* for facility_t */

typedef struct
{
    char *country;
    int day;
    facility_t **facilities;
    int month;
    char *name;
    int nfacilities;
    int year;
} base_t;

/**
 * @brief Adds a facility to a base.
 * @param base the base
 * @param facility the facility
 * @return -1 on error (i.e., if th ememory allocation is a failure), else 0
 */
int base_add_facility(base_t *base, facility_t *facility);

/**
 * @brief Creates a base
 * @return NULL on error (i.e., if the memory allocation is a failure), else a base.
 */
base_t *base_create();

/**
 * @brief Frees a base.
 * @param base the base.
 */
void base_free(base_t *base);

/**
 * @brief Handles the b command for a base.
 * @param base the base
 */
void base_handle_b(base_t base);

/**
 * @brief Handles the c command for a base.
 * @param base the base
 */
void base_handle_c(base_t base);

/**
 * @brief Handles the d command for a base.
 * @param base the base
 */
void base_handle_d(base_t base);

/**
 * @brief Handles the f command for a base.
 * @param base the base
 */
void base_handle_f(base_t base);

/**
 * @brief Handles the fc command for all the facilities of a base
 * @param base the base
 * @param cost the facility cost
 */
void base_handle_fc(base_t base, double cost);

/**
 * @brief Handles the fcge command for all the facilities of a base.
 * @param base the base
 * @param cost the facility cost
 */
void base_handle_fcge(base_t base, double cost);

/**
 * @brief Handles the fcgt command for all the facilities of a base.
 * @param base the base
 * @param cost the facility cost
 */
void base_handle_fcgt(base_t base, double cost);

/**
 * @brief Handles the fcle command for all the facilities of a base.
 * @param base the base
 * @param cost the facility cost
 */
void base_handle_fcle(base_t base, double cost);

/**
 * @brief Handles the fclt command for all the facilities of a base.
 * @param base the base
 * @param cost the facility cost
 */
void base_handle_fclt(base_t base, double cost);

/**
 * @brief Handles the fn command for all the facilities of a base.
 * @param base the base
 * @param name the facility name
 */
void base_handle_fn(base_t base, const char *name);

/**
 * @brief Handles the n command for a base.
 * @param base the base
 */
void base_handle_n(base_t base);

/**
 * @brief Handles the t command for a base.
 * @param base the base
 */
void base_handle_t(base_t base);




/* Effacer */
void yes();

#endif