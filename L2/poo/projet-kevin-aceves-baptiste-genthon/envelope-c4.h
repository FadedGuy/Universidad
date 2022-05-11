/**
* \file envelope-c4.h
*/
#ifndef ENVELOPE_C4_H
#define ENVELOPE_C4_H
#include "envelope.h" // for envelope_t
/**
* An envelope in the C4 format.
*/
class envelope_c4_t: public envelope_t
{
    public:
    /**
    * Constructs a new envelope in the C4 format.
    * Initializes its height to "324" and width to "229".
    */
    envelope_c4_t();
};
#endif
