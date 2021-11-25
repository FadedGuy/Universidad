#ifndef FACILITY_H
#define FACILITY_H

typedef struct
{
    int area;
    double cost;
    char *name;
} facility_t;

/**
 * @brief Creates a facility
 * @return NULL on error (i.e., if the memory allocation is a failure), else a facility
 */
facility_t *facility_create();

/**
 * @brief Frees a facility
 * @param facility the facility
 */
void facility_free(facility_t *facility);

/**
 * @brief Handles the f command for a facility
 * @param facility the facility
 */
void facility_handle_f(facility_t facility);

/**
 * @brief Handles the fc command for a facility
 * @param facility the facility
 * @param cost the facility cost
 */
void facility_handle_fc(facility_t facility, double cost);

/**
 * @brief Handles the fcge command for a facility
 * @param facility the facility
 * @param cost the facility cost
 */
void facility_handle_fcge(facility_t facility, double cost);

/**
 * @brief Handles the fcgt command for a facility
 * @param facility the facility
 * @param cost the facility cost
 */
void facility_handle_fcgt(facility_t facility, double cost);

/**
 * @brief Handles the fcle command for a facility
 * @param facility the facility
 * @param cost the facility cost
 */
void facility_handle_fcle(facility_t facility, double cost);

/**
 * @brief Handles the fclt command for a facility
 * @param facility the facility
 * @param cost the facility cost
 */
void facility_handle_fclt(facility_t facility, double cost);

/**
 * @brief Handles the fn command for a facility
 * @param facility the facility
 * @param name the facility name
 */
void facility_handle_fn(facility_t facility, const char *name);

#endif