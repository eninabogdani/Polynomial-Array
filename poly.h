// ------------------------------ poly.h -------------------------------
// Enina Bogdani, CSS 502
// 1/7/2020
// 1/12/2020
// --------------------------------------------------------------------
// Purpose: header file for the Poly class.
// --------------------------------------------------------------------
// A polynomial is an expression of more than two algebraic terms,
// containg different powers of the same variable.
// Represents a polynomial as an array of terms.
// Functionality includes overloaded arithmetic, assignment, comparison
// and input/output operators.
// Includes a mutator method to change/add a given coefficient, and an
// accessor method to obtain the coefficient of a power.
// Also includes a method to increase the size of the array containing
// the polynomial.
// --------------------------------------------------------------------

#ifndef POLYNOMIAL_H
#define POLY_H
#include <iostream> // Provides input and output formatting functions
using namespace std;

class Poly {
    // Overloaded << : prints a polynomial
    friend ostream& operator<<(ostream& output, const Poly& p);
    // Overloaded >> : takes user input to create a polynomial
    friend istream& operator>>(istream& input, Poly& p);

    public:
        // Member functions
        Poly(); // Default constructor
        Poly(int coeff, int exp); // Constructor
        Poly(int coeff); // Constructor
        Poly(const Poly& p); // Copy constructor, copies given Poly p
        ~Poly(); // Destructor

        // Arithmetic operators
        Poly operator+(const Poly& p) const; // Adds two Poly objects
        Poly operator-(const Poly& p) const; // Subtracts two Poly objects
        Poly operator*(const Poly& p) const; // Multiplies two Poly objects

        // Assignment operators
        Poly& operator=(const Poly& p);  // Sets current object equal 
                                         // to parameter
        Poly& operator+=(const Poly& p); // Current object += parameter
        Poly& operator-=(const Poly& p); // Current object -= parameter
        Poly& operator*=(const Poly& p); // Current object *= parameter

        // Comparison operators
        bool operator==(const Poly& p) const; // Is object == parameter?
        bool operator!=(const Poly& p) const; // Is object != parameter?

        // Accessors
        int getCoeff(int exp) const;

        // Mutator
        bool setCoeff(int coeff, int exp);

    private:
        int* arrayPtr; // The array containing the polynomial terms
        int size;      // The size of the array
        void resize(int resizeTo); // Resizes the array if its current size
                                   // becomes insufficient
};

#endif