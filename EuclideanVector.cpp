#include "EuclideanVector.h"
#include <stdexcept>
#include <cmath>

namespace evec {

    // constructors

    EuclideanVector::EuclideanVector(unsigned int dims): EuclideanVector(dims, 0) {}

    EuclideanVector::EuclideanVector(unsigned int dims, double mag) {
        dims_ = dims;
        vals = new double[dims_];
        for (unsigned int i = 0; i < dims_; ++i) {
            vals[i] = mag;
        }
    }

    EuclideanVector::EuclideanVector(std::initializer_list<double> mags): EuclideanVector(mags.begin(), mags.end()) {}

    // copy constructor
    EuclideanVector::EuclideanVector(const EuclideanVector &original) {
        dims_ = original.dims_;
        vals = new double[dims_];
        for (unsigned int i = 0; i < dims_; ++i) {
            vals[i] = original[i];
        }
    }

    // move constructor
    EuclideanVector::EuclideanVector(EuclideanVector &&original): EuclideanVector(0) {
        swap(*this, original);
    }

    // destructor

    EuclideanVector::~EuclideanVector() {
        delete[] vals;
    }

    // operations

    // copy assignment
    EuclideanVector& EuclideanVector::operator=(EuclideanVector& e) {
        // copy and swap
        EuclideanVector tmp = e;
        swap(tmp, *this);
        return *this;
    }

    // move assignment
    EuclideanVector& EuclideanVector::operator=(EuclideanVector &&e) {
        if (e == *this) {
            return *this;
        }
        EuclideanVector tmp(0);
        swap(e, *this);
        swap(e, tmp);
        return *this;
    }

    unsigned int EuclideanVector::getNumDimensions() const {
        return dims_;
    }

    double EuclideanVector::get(unsigned int i) const {
        return vals[i];
    }

    double EuclideanVector::getEuclideanNorm() {
        if (norm < 0) {
            // calculate norm
            norm = 0;
            for (unsigned int i = 0; i < dims_; ++i) {
                norm += vals[i] * vals[i];
            }
            norm = std::sqrt(norm);
        }
        return norm;
    }

    EuclideanVector EuclideanVector::createUnitVector() {
        const double norm = getEuclideanNorm();
        return *this / norm;
    }

    double &EuclideanVector::operator[](unsigned int i) {
        return vals[i];
    }

    const double &EuclideanVector::operator[](unsigned int i) const {
        return vals[i];
    }

    EuclideanVector& EuclideanVector::operator+=(const EuclideanVector &e) {
        if (dims_ != e.dims_) {
            throw std::invalid_argument("Dimensions do not match.");
        }
        for (unsigned int i = 0; i < dims_; ++i) {
            vals[i] += e[i];
        }
        return *this;
    }

    EuclideanVector& EuclideanVector::operator-=(const EuclideanVector &e) {
        *this += (e*-1);
        return *this;
    }

    EuclideanVector& EuclideanVector::operator*=(const double &n) {
        for (unsigned int i = 0; i < dims_; ++i) {
            vals[i] *= n;
        }
        return *this;
    }

    EuclideanVector& EuclideanVector::operator/=(const double &n) {
        *this *= (1/n);
        return *this;
    }

    EuclideanVector::operator std::vector<double>() {
        std::vector<double> result(vals, vals+dims_);
        return result;
    }

    EuclideanVector::operator std::list<double>() {
        std::list<double> result(vals, vals+dims_);
        return result;
    }

    // operators

    bool operator==(const EuclideanVector &e1, const EuclideanVector &e2) {
        if (e1.getNumDimensions() != e2.getNumDimensions()) {
            return false;
        }
        for (unsigned int i = 0; i < e1.getNumDimensions(); i++) {
            if (e1[i] != e2[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const EuclideanVector &e1, const EuclideanVector &e2) {
        return !(e1 == e2);
    }

    EuclideanVector operator+(const EuclideanVector &e1, const EuclideanVector &e2) {
        EuclideanVector result = e1;
        result += e2;
        return result;
    }

    EuclideanVector operator-(const EuclideanVector &e1, const EuclideanVector &e2) {
        return e1 + (-1*e2);
    }

    double operator*(const EuclideanVector &e1, const EuclideanVector &e2) {
        // dot product
        if (e1.getNumDimensions() != e2.getNumDimensions()) {
            throw std::invalid_argument("Dimensions do not match.");
        }
        const unsigned int ndims = e1.getNumDimensions();
        double result(0);
        for (unsigned int i = 0; i < ndims; i++) {
            result += e1[i] * e2[i];
        }
        return result;
    }

    EuclideanVector operator*(const EuclideanVector &e, const double &n) {
        EuclideanVector result = e;
        result *= n;
        return result;
    }

    EuclideanVector operator*(const double &n, const EuclideanVector &e) {
        return e * n;
    }

    EuclideanVector operator/(const EuclideanVector &e, const double &n) {
        return e * (1/n);
    }

    std::ostream& operator<<(std::ostream& stream, const EuclideanVector& e) {
        stream << '[';
        for (unsigned int i = 0; i < e.getNumDimensions(); ++i) {
            stream << e[i];
            if (i < (e.getNumDimensions() - 1)) {
                stream << ' ';
            }
        }
        stream << ']';
        return stream;
    }

    void swap(EuclideanVector& a, EuclideanVector& b) {
        using std::swap;
        swap(a.dims_, b.dims_);
        swap(a.vals, b.vals);
        swap(a.norm, b.norm);
    }
}
