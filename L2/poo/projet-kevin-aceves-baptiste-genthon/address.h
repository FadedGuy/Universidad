/**
* \file address.h
*/
#ifndef ADDRESS_H
#define ADDRESS_H
#include <string> // for string
using namespace std; // for string
/**
* An address.
*/
class address_t
{
    string city; /**< The city (example: "Bizanos"). */
    string country; /**< The country (example: "France"). */
    string name; /**< The name (example: "Alain Verse"). */
    int postal_code; /**< The postal code (example: "64320"). */
    string street; /**< The street (example: "1 rue de la programmation"). */
    public:
        /**
        * Constructs a new address.
        * Initializes its city, country, name and street to "undefined".
        * Initializes its postal code to 0.
        */
        address_t();
        /**
        * Gets the city for this address.
        * \return The city for this address.
        */
        string get_city() const;
        /**
        * Gets the country for this address.
        * \return The country for this address.
        */
        string get_country() const;
        /**
        * Gets the name for this address.
        * \return The name for this address.
        */
        string get_name() const;
        /**
        * Gets the postal code for this address.
        * \return The postal code for this address.
        */
        int get_postal_code() const;
        /**
        * Gets the street for this address.
        * \return The street for this address.
        */
        string get_street() const;
        /**
        * Sets the city for this address.
        * \param city The city for this address.
        */
        void set_city(string city);
        /**
        * Sets the country for this address.
        * \param country The country for this address.
        */
        void set_country(string country);
        /**
        * Sets the name for this address.
        * \param name The name for this address.
        */
        void set_name(string name);
        /**
        * Sets the postal code for this address.
        * \param postal_code The postal code for this address.
        */
        void set_postal_code(int postal_code);
        /**
        * Sets the street for this address.
        * \param street The street for this address.
        */
        void set_street(string street);
};
/**
* Inserts an address into an output stream.
* The inserted string is "(name, street, postal_code, city, country)".
* \param os The output stream.
* \param address The address.
* \return The output stream.
*/
ostream &operator<<(ostream &os, const address_t &address);
#endif