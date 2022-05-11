/**
* \file envelope.h
*/
#ifndef ENVELOPE_H
#define ENVELOPE_H
#include <string> // for string
#include "address.h" // for address_t
using namespace std; // for string
/**
* A format.
*/
enum priority_t
{
    undefined,
    high,
    low,
    medium
};
/**
* An envelope.
*/
class envelope_t
{
    private:
        priority_t priority; /**< The priority (example: "low"). */
        address_t recipient; /**< The recipient address. */
        address_t sender; /**< The sender address. */
    protected:
        int height; /**< The height (in mm, example: "324"). */
        int width; /**< The width (in mm, example: "229"). */
    public:
        /**
        * Constructs a new envelope.
        * Initializes its height and width to "0".
        */
        envelope_t();
        /**
        * Gets the height for this envelope.
        * \return The height for this envelope.
        */
        int get_height() const;
        /**
        * Gets the priority for this envelope.
        * \return The priority for this envelope.
        */
        priority_t get_priority() const;
        /**
        * Gets the recipient address for this envelope.
        * \return The recipient address for this envelope.
        */
        address_t get_recipient() const;
        /**
        * Gets the sender address for this envelope.
        * \return The sender address for this envelope.
        */
        address_t get_sender() const;
        /**
        * Gets the width for this envelope.
        * \return The width for this envelope.
        */
        int get_width() const;
        /**
        * Handles the e command for this envelope.
        * Calls the << overloaded operator on this envelope.
        */
        void handle_e() const;
        /**
        * Handles the ec command for this envelope.
        * Calls the handle_e method on this envelope if the condition is satisfied.
        * \param postal_code The ec command parameter.
        */
        void handle_ec(int postal_code) const;
        /**
        * Handles the ecge command for this envelope.
        * Calls the handle_e method on this envelope if the condition is satisfied.
        * \param postal_code The ecge command parameter.
        */
        void handle_ecge(int postal_code) const;
        /**
        * Handles the ecgt command for this envelope.
        * Calls the handle_e method on this envelope if the condition is satisfied.
        * \The ecgt command parameter.
        */
        void handle_ecgt(int postal_code) const;
        /**
        * Handles the ecle command for this envelope.
        * Calls the handle_e method on this envelope if the condition is satisfied.
        * \param postal_code The ecle command parameter.
        */
        void handle_ecle(int postal_code) const;
        /**
        * Handles the eclt command for this envelope.
        * Calls the handle_e method on this envelope if the condition is satisfied.
        * \param postal_code The eclt command parameter.
        */
        void handle_eclt(int postal_code) const;
        /**
        * Handles the en command for this envelope.
        * Calls the handle_e method on this envelope if the condition is satisfied.
        * \param name The en command parameter.
        */
        void handle_en(string name) const;
        /**
        * Sets the priority for this envelope.
        * \param priority The priority for this envelope.
        */
        void set_priority(priority_t priority);
        /**
        * Sets the recipient address for this envelope.
        * \param recipient The recipient address for this envelope.
        */
        void set_recipient(address_t recipient);
        /**
        * Sets the sender address for this envelope.
        * \param sender The sender address for this envelope.
        */
        void set_sender(address_t sender);
};
/**
* Inserts an envelope into an output stream.
* The inserted string is "(sender -> recipient [priority] widthxheight)".
* \param os The output stream.
* \param envelope The envelope.
* \return The output stream.
*/
ostream &operator<<(ostream &os, const envelope_t &envelope);
#endif