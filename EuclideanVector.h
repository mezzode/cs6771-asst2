#ifndef EVEC_H
#define EVEC_H

#include <vector>
#include <list>
#include <cmath>
#include <iostream>

namespace evec {
    class EuclideanVector {
        public:
            EuclideanVector(unsigned int dims);
            EuclideanVector(unsigned int dims, double mag);
            EuclideanVector(std::initializer_list<double> mags);
            EuclideanVector(const EuclideanVector &original);
            // EuclideanVector(EuclideanVector &original);

            template<class iterator_type>
            EuclideanVector(iterator_type begin, iterator_type end);

            ~EuclideanVector();

            unsigned int getNumDimensions();
            double get(unsigned int i);
            double getEuclideanNorm();
            EuclideanVector createUnitVector();

            operator std::vector<double>(); 
            operator std::list<double>();

            EuclideanVector operator=(const EuclideanVector &e);
            double &operator[](unsigned int i);
            const double &operator[](unsigned int i) const;
            EuclideanVector operator+=(EuclideanVector e);
            EuclideanVector operator-=(EuclideanVector e);
            EuclideanVector operator*=(double n);
            EuclideanVector operator/=(double n);

            // dont friend things which dont access private vars
            // should these also be declared separately in the header file?
            friend bool operator==(EuclideanVector e1, EuclideanVector e2);
            friend bool operator!=(EuclideanVector e1, EuclideanVector e2);
            friend EuclideanVector operator+(EuclideanVector e1, EuclideanVector e2);
            friend EuclideanVector operator-(EuclideanVector e1, EuclideanVector e2);
            friend double operator*(EuclideanVector e1, EuclideanVector e2);
            friend EuclideanVector operator*(EuclideanVector e, double n);
            friend EuclideanVector operator*(double n, EuclideanVector e);
            friend EuclideanVector operator/(EuclideanVector e, const double n);
            friend std::ostream& operator<<(std::ostream& stream, const EuclideanVector& e);
        private:
            // std::vector<double> vals; // must use dynamically allocated memory, cant just be automatic...
            unsigned int dims_;
            double *vals;
            mutable double norm = -1; // need to cache norm if possible
    };
}

#endif
