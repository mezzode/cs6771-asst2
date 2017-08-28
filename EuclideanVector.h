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

            // EuclideanVector operator/=(const double n) {
            //     // asdf
            // }

            double &operator[](unsigned int i) {
                return vals[i];
            }

            const double &operator[](unsigned int i) const {
                return vals[i];
            }

            friend EuclideanVector operator/(EuclideanVector e, const double n);
            friend std::ostream& operator<<(std::ostream& stream, const EuclideanVector& e);
        private:
            std::vector<double> vals; // must use dynamically allocated memory, cant just be automatic...
            mutable double norm = -1; // need to cache norm if possible
    };
}

#endif
