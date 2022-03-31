#include "company.h"
using namespace std; // for string
/**
* A company.
*/
class company_t
{
    vector<envelope_t> envelopes; /**< The envelopes. */
    string name; /**< The name (example: "UPS"). */
    string web; /**< The web address (example: "https://www.ups.com/"). */
    public:
        /**
        * Constructs a new company.
        * Initializes its name and web address to "undefined".
        */
        company_t():
        name(NULL),
        web(NULL)
        {}
        /**
        * Gets the name for this company.
        * \return The name for this company.
        */
        string get_name() const {
            return this->name;
        }
        /**
        * Gets the web address for this company.
        * \return The web address for this company.
        */
        string get_web() const {
            return this->web;
        }
        /**
        * Handles the e command for this company.
        * Iterates on envelopes to call the handle_m method on its elements.
        */
        void handle_e() const;
        /**
        * Handles the i command for this company.
        * Calls the << overloaded operator on this company.
        */
        void handle_i() const;
        /**
        * Handles the n command for this company.
        */
        void handle_n() const;
        /**
        * Handles the ec command for this company.
        * Iterates on envelopes to call the handle_ec method on its elements.
        * \param postal_code The ec command parameter.
        */
        void handle_ec(int postal_code) const;
        /**
        * Handles the ecge command for this company.
        * Iterates on envelopes to call the handle_ecge method on its elements.
        * \param postal_code The ecge command parameter.
        */
        void handle_ecge(int postal_code) const;
        /**
        * Handles the ecgt command for this company.
        * Iterates on envelopes to call the handle_ecgt method on its elements.
        * \param postal_code The ecgt command parameter.
        */
        void handle_ecgt(int postal_code) const;
        /**
        * Handles the ecle command for this company.
        * Iterates on envelopes to call the handle_ecle method on its elements.
        * \param postal_code The ecle command parameter.
        */
        void handle_ecle(int postal_code) const;
        /**
        * Handles the eclt command for this company.
        * Iterates on envelopes to call the handle_eclt method on its elements.
        * \param postal_code The eclt command parameter.
        */
        void handle_eclt(int postal_code) const;
        /**
        * Handles the en command for this company.
        * Iterates on envelopes to call the handle_en method on its elements.
        * \param name The en command parameter.
        */
        void handle_en(string name) const;
        /**
        * Handles the w command for this company.
        */
        void handle_w() const;
        /**
        * Accesses to the element of envelopes at the specified index for this company.
        * Calls the at method on envelopes.
        * \param index The index.
        * \return The element of envelopes at the specified index for this company.
        */
        envelope_t envelopes_at(int index) const;
        /**
        * Adds an element at the end of envelopes for this company.
        * Calls the push_back method on envelopes.
        * \param envelope The element.
        */
        void envelopes_push_back(envelope_t envelope) {
            this->envelopes.push_back(envelope);
        }
        /**
        * Gets the size of envelopes for this company.
        * Calls the size method on envelopes 
        * \return The size of envelopes for this company.
        */
        int envelopes_size() const {
            return envelopes.size(); // size returns the number of elements in vector envelopes
        }
        /**
        * Sets the name for this company.
        * \param name The name for this company.
        */
        void set_name(string name) {
            this->name = name;
        }
        /**
        * Sets the web address for this company.
        * \param web The web address for this company.
        */
        void set_web(string web) {
            this->web = web;
        }
};
/**
* Inserts a company into an output stream.
* The inserted string is "(name, web, (envelopes1, envelopes2, ...))".
* Calls the << overloaded operator on the envelopes.
* \param os The output stream.
* \param company The company.
* \return The output stream.
*/
ostream &operator<<(ostream &os, const company_t &company);
