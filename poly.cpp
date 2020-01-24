// -------------------------- poly.cpp --------------------------
// Enina Bogdani, CSS 502
// 1/7/2020
// 1/12/2020
// --------------------------------------------------------------
// Purpose: implementation file for the Poly class.
// --------------------------------------------------------------
// Implements the internal representation of a polynomial as an
// array of terms.
// One terms is stored in each array element, containing an
// exponent and a coefficient.
// User input is assumed to be of valid data types.
// Negative exponents are invalid and are not processed as input.
// --------------------------------------------------------------

#include "poly.h"

// ------------------------ initialize -----------------------
// Helper to initialze arrays to zero
// Takes a pointer to an array to be initialized and the size
// of the array as parameters
// -----------------------------------------------------------
void initialize(int* arrayToInit, int size) {
    for (int i = 0; i < size; i++) {
        arrayToInit[i] = 0;
    }
}

// --------------------------- Poly --------------------------
// Default constructor
// Takes no parameters
// Constructs an empty polynomial with a size of 1 and 1st
// coefficient of 0
// -----------------------------------------------------------
Poly::Poly() {
    arrayPtr = new int[1];
    arrayPtr[0] = 0;
    size = 1;
}

// --------------------------- Poly --------------------------
// Constructor
// Takes a coefficient and exponent as parameters
// Constructs a polynomial with an element of the given
// coefficient and exponent
// -----------------------------------------------------------
Poly::Poly(int coeff, int exp) {
    arrayPtr = new int[exp + 1];
    size = exp + 1;
    initialize(arrayPtr, size);
    arrayPtr[exp] = coeff;
}


// --------------------------- Poly --------------------------
// Constructor
// Takes a coefficient as parameter
// Constructs a polynomial with an element of the given
// coefficient and exponent of 0
// -----------------------------------------------------------
Poly::Poly(int coeff) {
    arrayPtr = new int[1];
    arrayPtr[0] = coeff;
    size = 1;
}

// --------------------------- Poly --------------------------
// Copy constructor
// Takes a polynomial as parameter
// Deep copies it into the current polynomial
// -----------------------------------------------------------
Poly::Poly(const Poly& p) {
    arrayPtr = new int[0];
    size = 0;
    *this = p;
}

// --------------------------- ~Poly --------------------------
// Destructor
// Deletes the array containing the polynomial's terms
// -----------------------------------------------------------
Poly::~Poly() {
    delete[] arrayPtr;
    arrayPtr = NULL;
}

// ------------------------- getCoeff ------------------------
// Returns the coefficient of the given exponent
// If the exponent is not present in the polynomial, returns 0
// No type checking, assumes valid input is being passed
// -----------------------------------------------------------
int Poly::getCoeff(int exp) const {
    if (exp >= size || exp < 0) {
        return 0;
    }

    return arrayPtr[exp];
}

// ------------------------- setCoeff ------------------------
// Assigns the given coefficient to the given exponent
// Returns true if assignment was successful
// If the exponent is negative, returns 0
// If the given exponent is greater than the current largest
// exponent, the array size is increased
// No type checking, assumes valid input is being passed
// -----------------------------------------------------------
bool Poly::setCoeff(int coeff, int exp) {
    if (exp < 0) {
        return false;
    }

    if (exp >= size) {
        resize(exp + 1);
    }

    arrayPtr[exp] = coeff;
    return true;
}

// ----------------------- operator<< ----------------------
// Prints an entire polynomial in the format 
// Cn * x^n + Cn-1 * X^n-1 + ... C1 * X + C0
// ---------------------------------------------------------
ostream& operator<<(ostream& output, const Poly& p) {
    bool isFirst = true;
    for (int i = p.size - 1; i >= 0; i--)  {
        int coefficient = p.getCoeff(i);
        if (coefficient != 0) {
            // Print sign of coefficient
            if (coefficient > 0) {
                output << " +";
            } else if (coefficient < 0) {
                output << " -";
            }

            // Print coefficient
            if (coefficient != 1 && coefficient != -1) {
                // Get coefficient's absolute value in order to avoid
                // duplicate - sign
                output << (coefficient < 0 ? -coefficient : coefficient);
            } else if (coefficient == 1 || coefficient == -1) {
                output << "1";
            }

            // Print variable
            if (i > 0) {
                output << "x";
            }

            // Print exponent
            if (i > 1) {
                output << "^" << i;
            }

            isFirst = false;
        }    
    }

    // If still on first by time we exit the loop, know we didn't print anything, so all 0's
    if (isFirst) {
        output << "0";
    }

    return output;
}

// ----------------------- operator>> ------------------------
// Takes user input for all terms of a polynomial in the form
// of coefficient/pairs; -1 -1 pair indicates end of input
// No type checking, assumes the user is entering a valid data
// type and even number of ints
// -----------------------------------------------------------
istream& operator>>(istream& input, Poly& p) {
    int coeff;
    int exp;
    input >> coeff;
    input >> exp;
    p.setCoeff(coeff, exp); 
    while ((coeff != -1) || (exp != -1)) {
        input >> coeff;
        if (exp >= 0) {
            input >> exp;
        }
        
        p.setCoeff(coeff, exp);    
    }

    return input;
}

// ----------------------- operator+ ------------------------
// Adds the given polynomial to the current polynomial
// Returns a new polynomial with this value
// ----------------------------------------------------------
Poly Poly::operator+(const Poly& p) const {
    int maxSize = size > p.size ? size : p.size;
    Poly sum(0, maxSize);
    for (int i = 0; i < maxSize; i++) {
        int thisCoeff = 0;
        int pCoeff = 0;
        if (i < size) {
            thisCoeff = arrayPtr[i];
        }

        if (i < p.size) {
            pCoeff = p.arrayPtr[i];
        }

        sum.arrayPtr[i] = thisCoeff + pCoeff;
    }

    return sum;
}

// ----------------------- operator- ------------------------
// Subtracts the given polynomial from the current polynomial
// Returns a new polynomial with this value
// ----------------------------------------------------------
Poly Poly::operator-(const Poly& p) const {
    int maxSize = size > p.size ? size : p.size;
    Poly difference(0, maxSize);
    for (int i = 0; i < maxSize; i++) {
        int thisCoeff = 0;
        int pCoeff = 0;
        if (i < size) {
            thisCoeff = arrayPtr[i];
        }

        if (i < p.size) {
            pCoeff = p.arrayPtr[i];
        }

        difference.arrayPtr[i] = thisCoeff - pCoeff;
    }
    
    return difference;
}

// ----------------------- operator* -------------------------
// Multiplies the current polynomial with the given polynomial
// Returns a new polynomial with this value
// -----------------------------------------------------------
Poly Poly::operator*(const Poly& p) const {
    Poly product(0, (size + p.size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < p.size; j++) {
            int coeff = arrayPtr[i] * p.arrayPtr[j];
            int exp = i + j;
            if (product.arrayPtr[exp] == 0) {
                product.arrayPtr[exp] = coeff;
            } else {
                product.arrayPtr[exp] += coeff;
            }
        }
    }

    return product;
}

// -------------------------- operator= --------------------------
// If the given polynomial is equal to the current polynomial, 
// immediately returns current object
// Otherwise, sets the current polynomial equal to the given
// polynomial, and returns the current object
// ---------------------------------------------------------------
Poly& Poly::operator=(const Poly& p) {
    if (&p == this) {
        return *this;
    }

    delete[] arrayPtr;
    arrayPtr = new int[p.size];
    size = p.size;
    initialize(arrayPtr, size);
    for (int i = 0; i < p.size; i++) {
        arrayPtr[i] = p.arrayPtr[i];
    }

    return *this;
}

// -------------------------- operator+= -------------------------
// Adds the given polynomial to the current polynomial
// Returns the current polynomial
// ---------------------------------------------------------------
Poly& Poly::operator+=(const Poly& p) {
    Poly sum = *this + p;
    *this = sum;
    return *this;
}

// -------------------------- operator-= -------------------------
// Subtracts the given polynomial from the current polynomial
// Returns the current polynomial
// ---------------------------------------------------------------
Poly& Poly::operator-=(const Poly& p) {
    Poly difference = *this - p;
    *this = difference;
    return *this;
}

// -------------------------- operator*= -------------------------
// Multiplies the current polynomial with the given polynomial
// Returns the current polynomial
// ---------------------------------------------------------------
Poly& Poly::operator*=(const Poly& p) {
   Poly product = *this * p;
   *this = product;
   return *this; 
}

// -------------------------- operator== -------------------------
// Compares the given polynomial with the current polynomial
// Returns true if they are equal, false otherwise
// ---------------------------------------------------------------
bool Poly::operator==(const Poly& p) const {
    for (int i = 0; i < size; i++) {
        // getCoeff accounts for out-of-bounds exponents
        if (getCoeff(i) != p.getCoeff(i)) {
            return false;
        }
    }

    for (int i = 0; i < p.size; i++) {      
        if (getCoeff(i) != p.getCoeff(i)) {
            return false;
        }
    }

    return true;
}

// -------------------------- operator!= -------------------------
// Compares the given polynomial with the current polynomial
// Returns true if they are not equal, false otherwise
// ---------------------------------------------------------------
bool Poly::operator!=(const Poly& p) const {
    return !(*this == p);
}

// ---------------------------- resize ---------------------------
// Increases the size of arrayPtr to the given size in order to 
// accomodate a polynomial term with a greater exponent
// ---------------------------------------------------------------
void Poly::resize(int resizeTo) {
    int* temp = new int[resizeTo];
    for (int i = 0; i < resizeTo; i++) {
        temp[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        temp[i] = arrayPtr[i];
    }

    delete[] arrayPtr;
    arrayPtr = temp;
    size = resizeTo;
}