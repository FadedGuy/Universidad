#include "address.h" // for addresses
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
        address_t():
        city(NULL),
        country(NULL),
        name(NULL),
        postal_code(0),
        street(NULL)
        {}
        /**
        * Gets the city for this address.
        * \return The city for this address.
        */
        string get_city() const {
            return this->city;
        }
        /**
        * Gets the country for this address.
        * \return The country for this address.
        */
        string get_country() const {
            return this->country;
        }
        /**
        * Gets the name for this address.
        * \return The name for this address.
        */
        string get_name() const {
            return this->name;
        }
        /**
        * Gets the postal code for this address.
        * \return The postal code for this address.
        */
        int get_postal_code() const {
            return this->postal_code;
        }
        /**
        * Gets the street for this address.
        * \return The street for this address.
        */
        string get_street() const {
            return this->street;
        }
        /**
        * Sets the city for this address.
        * \param city The city for this address.
        */
        void set_city(string city) {
            this->city = city;
        }
        /**
        * Sets the country for this address.
        * \param country The country for this address.
        */
        void set_country(string country) {
            this->country = country;
        }
        /**
        * Sets the name for this address.
        * \param name The name for this address.
        */
        void set_name(string name) {
            this->name = name;
        }
        /**
        * Sets the postal code for this address.
        * \param postal_code The postal code for this address.
        */
        void set_postal_code(int postal_code) {
            this->postal_code = postal_code;
        }
        /**
        * Sets the street for this address.
        * \param street The street for this address.
        */
        void set_street(string street) {
            this->street = street;
        }
};
/**
* Inserts an address into an output stream.
* The inserted string is "(name, street, postal_code, city, country)".
* \param os The output stream.
* \param address The address.
* \return The output stream.
*/
ostream &operator<<(ostream &os, const address_t &address);