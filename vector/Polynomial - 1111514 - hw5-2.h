#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <cmath>
using std::sqrt;

#include "vector - 1111514 - hw5.h"

// Represents a term of a polynomial
template< typename T >
struct Term
{
   bool operator!=( const Term &right ) const
   {
      return coef != right.coef || expon != right.expon;
   }

   T coef;
   T expon;
};

// Polynomial class template definition
template< typename T1, typename T2 >
class Polynomial
{
   // Overloaded stream insertion operator
   template< typename T1, typename T2 >
   friend ostream &operator<<( ostream &output, Polynomial< T1, T2 > a );
public:

   // Constructs an empty polynomial, with no terms.
   Polynomial( size_t n = 0 )
      : polynomial( n )
   {
   }

   // Constructs a polynomial with a copy of each of the terms in polynomialToCopy.
   Polynomial( const Polynomial &right )
      : polynomial( right.polynomial )
   {
   }

   // Destructor with empty body
   ~Polynomial()
   {
   }

   // Copies all the terms from "right" into the polynomial
   const Polynomial operator=( const Polynomial &right )
   {
      if( &right != this ) // avoid self-assignment
         polynomial = right.polynomial;

      return *this; // enables x = y = z, for example
   }

   bool operator==( const Polynomial &right )
   {
      return polynomial == right.polynomial;
   }

   void setPolynomial( T2 coefficient[], T2 exponent[], int numTerms )
   {
      for( int i = 0; i < numTerms; i++ )
      {
         polynomial[ i ].coef = coefficient[ i ];
         polynomial[ i ].expon = exponent[ i ];
      }
   }

   // addition assignment operator; Polynomial += Polynomial
   void operator+=( Polynomial &op2 )
   {
       // addend+=adder
       int addendsize = polynomial.size();
       int addersize = op2.polynomial.size();
       Polynomial x = *this;
       // if( adder == 0 )
       if (op2.zero())
           return;

       // if( addend == 0 )
       if (x.zero())
       {
           // addend = adder
           *this = op2;
           return;
       }

       // buffer = 0
       Polynomial buffer;

       // buffer = -adder
       buffer = -op2;

       // if( addend == -adder )
       if (buffer == *this)
       {
           polynomial.clear();     // addend = 0;
           return;
       }
       Polynomial sum;
       Polynomial store(1);
       int i = 0;
       int j = 0;
       int k = 0;
       //cout << addendsize << endl << "," << addersize << endl;
       while (i < addendsize && j < addersize)
       {
           if (polynomial[i].expon == op2.polynomial[j].expon) {
               if (polynomial[i].coef + op2.polynomial[j].coef == 0) {
                   i++;
                   j++;
               }
               else {
                   store.polynomial[0].coef = polynomial[i].coef + op2.polynomial[j].coef;
                   store.polynomial[0].expon = polynomial[i].expon;
                   sum.polynomial.insert(sum.polynomial.end(), store.polynomial[0]);
                   i++;
                   j++;
                   k++;
               }
           }
           else if (polynomial[i].expon < op2.polynomial[j].expon) {
               store.polynomial[0].coef = op2.polynomial[j].coef;
               store.polynomial[0].expon = op2.polynomial[j].expon;
               sum.polynomial.insert(sum.polynomial.end(), store.polynomial[0]);
               j++;
               k++;
           }
           else if (polynomial[i].expon > op2.polynomial[j].expon) {
               store.polynomial[0].coef = polynomial[i].coef;
               store.polynomial[0].expon = polynomial[i].expon;
               sum.polynomial.insert(sum.polynomial.end(), store.polynomial[0]);
               i++;
               k++;
           }
       }

       while (i < addendsize)
       {
           store.polynomial[0].coef = polynomial[i].coef;
           store.polynomial[0].expon = polynomial[i].expon;
           sum.polynomial.insert(sum.polynomial.end(), store.polynomial[0]);
           k++;
           i++;
       }

       while (j < addersize)
       {
           store.polynomial[0].coef = op2.polynomial[j].coef;
           store.polynomial[0].expon = op2.polynomial[j].expon;
           sum.polynomial.insert(sum.polynomial.end(), store.polynomial[0]);
           k++;
           j++;
       }
       *this = sum;
   }

   // subtraction assignment operator; Polynomial -= Polynomial
   void operator-=( Polynomial &op2 )
   {
      Polynomial minus = -op2;
      *this += minus;
   }

   // multiplication operator; Polynomial * Polynomial
   Polynomial operator*( Polynomial &op2 )
   {
       // product = 0;
       Polynomial product;
       Polynomial store(1);
       Polynomial buffer;
       Polynomial x = *this;
       if (!x.zero() && !op2.zero()) {
           for (int i = 0; i < polynomial.size(); i++) {
               for (int j = 0; j < op2.polynomial.size(); j++) {
                   store.polynomial[0].coef = polynomial[i].coef * op2.polynomial[j].coef;
                   store.polynomial[0].expon = polynomial[i].expon + op2.polynomial[j].expon;
                   buffer.polynomial.insert(buffer.polynomial.end(), store.polynomial[0]);
               }
               product += buffer;
               buffer.polynomial.clear();
           }
       }
       while (product.polynomial[0].coef == 0) {
           product.polynomial.erase(product.polynomial.begin());
       }

       return product;

   }

   // computes the square root of the current polynomial
   Polynomial compSquareRoot()
   {
       Polynomial remainder;
       remainder = *this;
       Polynomial monomial(1);
       Polynomial divisor;
       Polynomial buffer;
       Polynomial squareroot;
       monomial.polynomial[0].coef = sqrt(remainder.polynomial[0].coef);
       monomial.polynomial[0].expon = remainder.polynomial[0].expon / 2;
       squareroot += monomial;
       divisor += monomial;
       buffer = monomial * divisor;
       remainder -= buffer;

       while (!remainder.zero()) {
           divisor.polynomial[divisor.polynomial.size() - 1].coef *= 2;
           monomial.polynomial[0].coef = remainder.polynomial[0].coef / divisor.polynomial[0].coef;
           monomial.polynomial[0].expon = remainder.polynomial[0].expon - divisor.polynomial[0].expon;
           squareroot += monomial;
           divisor += monomial;
           buffer = monomial * divisor;
           remainder -= buffer;
       }
       return squareroot;
   }

private:
   T1 polynomial; // a polynomial

   // Attaches a new term to the polynomial
   void attach( T2 coefficient, T2 exponent )
   {
      Term< T2 > tempTerm;
      tempTerm.coef = coefficient;
      tempTerm.expon = exponent;
      polynomial.insert( polynomial.end(), tempTerm );
   }

   // Returns the minus of the current polynomial
   Polynomial operator-()
   {
      Polynomial minus( polynomial.size() );
      typename T1::iterator it2 = minus.polynomial.begin();
      typename T1::iterator it1 = polynomial.begin();
      for( ; it1 != polynomial.end(); ++it1, ++it2 )
      {
         it2->coef = -it1->coef;
         it2->expon = it1->expon;
      }

      return minus;
   }

   // Returns true if and only if polynomial is a zero polynomial
   bool zero() const
   {
      return polynomial.empty();
   }

   // Returns the highest of degrees of polynomial's terms
   int degree() const
   {
      if( polynomial.empty() )
         return 0;
      else
         return polynomial.begin()->expon;
   }

}; // end class template Polynomial

// Overloaded stream insertion operator
template< typename T1, typename T2 >
ostream& operator<<( ostream &output, Polynomial< T1, T2 > a )
{
   if( a.zero() )
   {
      output << 0 << endl;
      return output;
   }

   typename T1::iterator it = a.polynomial.begin();

   if( it->coef < 0 )
      cout << "-" << -it->coef;
   else if( it->coef > 0 )
      cout << it->coef;

   if( it->expon > 0 )
   {
      if( it->expon == 1 )
         cout << "x";
      else
         cout << "x^" << it->expon;
   }

   for( ++it; it != a.polynomial.end(); ++it )
   {
      if( it->coef < 0 )
         cout << " - " << -it->coef;
      else if( it->coef > 0 )
         cout << " + " << it->coef;

      if( it->expon > 0 )
      {
         if( it->expon == 1 )
            cout << "x";
         else
            cout << "x^" << it->expon;
      }
   }

   return output; // enables cout << x << y;
} // end function operator<<

#endif