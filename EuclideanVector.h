#ifndef EVEC_H
#define EVEC_H

#include <vector>
#include <list>
#include <cmath>
#include <iostream>
#include <iterator>

namespace evec {
    class EuclideanVector {
        public:
            // constructors

            EuclideanVector(unsigned int dims = 1);

            EuclideanVector(unsigned int dims, double mag);

            template<class iterator_type>
            EuclideanVector(iterator_type begin, iterator_type end) {
                dims_ = std::distance(begin, end);
                vals = new double[dims_];
                unsigned int i = 0;
                for (auto it = begin; it != end; ++it, ++i) {
                    vals[i] = *it;
                }
            }

            EuclideanVector(std::initializer_list<double> mags);

            EuclideanVector(const EuclideanVector &original);

            EuclideanVector(EuclideanVector &&original);

            // destructor

            ~EuclideanVector();

            // operations

            // copy assignment
            EuclideanVector& operator=(EuclideanVector &e);

            // move assignment
            EuclideanVector& operator=(EuclideanVector &&e);

            unsigned int getNumDimensions() const;

            double get(unsigned int i) const;

            double getEuclideanNorm();

            EuclideanVector createUnitVector();
            
            double &operator[](unsigned int i);
            const double &operator[](unsigned int i) const;

            EuclideanVector& operator+=(const EuclideanVector &e);

            EuclideanVector& operator-=(const EuclideanVector &e);

            EuclideanVector& operator*=(const double &n);

            EuclideanVector& operator/=(const double &n);

            operator std::vector<double>();
            operator std::list<double>();
        private:
            unsigned int dims_;
            double *vals;
            mutable double norm = -1; // need to cache norm if possible

            friend void swap(EuclideanVector& a, EuclideanVector& b);
    };

    bool operator==(const EuclideanVector &e1, const EuclideanVector &e2);
    bool operator!=(const EuclideanVector &e1, const EuclideanVector &e2);
    EuclideanVector operator+(const EuclideanVector &e1, const EuclideanVector &e2);
    EuclideanVector operator-(const EuclideanVector &e1, const EuclideanVector &e2);
    double operator*(const EuclideanVector &e1, const EuclideanVector &e2);
    EuclideanVector operator*(const EuclideanVector &e, const double &n);
    EuclideanVector operator*(const double &n, const EuclideanVector &e);
    EuclideanVector operator/(const EuclideanVector &e, const double &n);
    std::ostream& operator<<(std::ostream& stream, const EuclideanVector& e);
}

#endif
