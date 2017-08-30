#ifndef EVEC_H
#define EVEC_H

#include <vector>
#include <cmath>
#include <iostream>

namespace evec {
    class EuclideanVector {
        public:
            EuclideanVector(unsigned int dims);
            EuclideanVector(unsigned int dims, double mag);
            EuclideanVector(std::initializer_list<double> mags);

            template<class iterator_type>
            EuclideanVector(iterator_type begin, iterator_type end);

            unsigned int getNumDimensions();
            double get(unsigned int i);
            double getEuclideanNorm();
            EuclideanVector createUnitVector();

            double &operator[](unsigned int i) {
                return vals[i];
            }

            const double &operator[](unsigned int i) const {
                return vals[i];
            }

            EuclideanVector operator+=(EuclideanVector e);
            EuclideanVector operator-=(EuclideanVector e);
            EuclideanVector operator*=(const double n);
            EuclideanVector operator/=(const double n);

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
            std::vector<double> vals; // must use dynamically allocated memory, cant just be automatic...
            mutable double norm = -1; // need to cache norm if possible
    };
}

#endif
