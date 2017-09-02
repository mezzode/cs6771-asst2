#include "EuclideanVector.h"
#include <stdexcept> // here or in header?
#include <algorithm>
#include <iterator>

namespace evec {

    // takes the number of dimensions (as an unsigned int) but no
    // magnitudes, sets the magnitude in each dimension as 0.0.
    // This is the default constructor, with the default value being 1. 
    EuclideanVector::EuclideanVector(unsigned int dims): EuclideanVector(dims, 0) {}

    EuclideanVector::EuclideanVector(unsigned int dims, double mag) {
        dims_ = dims;
        vals = new double[dims_];
        for (unsigned int i = 0; i < dims_; ++i) {
            vals[i] = mag;
        }
    }

    // initializer list constructor e.g. `EuclideanVector a {1,2,3,4};`
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
    EuclideanVector::EuclideanVector(EuclideanVector &&original): dims_{std::move(original.dims_)}, norm{std::move(original.norm)} {
        vals = original.vals;
        original.vals = nullptr;
    }

    EuclideanVector::~EuclideanVector() {
        // delete dims_;
        delete[] vals;
        // delete norm;
    }

    unsigned int EuclideanVector::getNumDimensions() {
        return dims_;
    }

    double EuclideanVector::get(unsigned int i) {
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
        // TODO: returns nan if norm is 0; norm is zero if zero vector; allowed?
        const double norm = getEuclideanNorm();
        return *this / norm;
    }

    EuclideanVector::operator std::vector<double>() {

        // for (unsigned int i = 0; i < dims_; ++i) {

        // }
        std::vector<double> result(vals, vals+dims_);
        return result;
    }

    EuclideanVector::operator std::list<double>() {
        std::list<double> result(vals, vals+dims_);
        return result;
    }

    // copy assignment
    EuclideanVector EuclideanVector::operator=(EuclideanVector e) {
        // copy and swap
        swap(e, *this);
        return *this;
    }

    double &EuclideanVector::operator[](unsigned int i) {
        return vals[i];
    }

    const double &EuclideanVector::operator[](unsigned int i) const {
        return vals[i];
    }

    EuclideanVector EuclideanVector::operator/=(const double n) {
        return *this / n; // needs to assign to itself tho
    }

    bool operator==(EuclideanVector e1, EuclideanVector e2) {
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

    bool operator!=(EuclideanVector e1, EuclideanVector e2) {
        return !(e1 == e2);
    }

    EuclideanVector operator+(EuclideanVector e1, EuclideanVector e2) {
        if (e1.getNumDimensions() != e2.getNumDimensions()) {
            throw std::invalid_argument("Dimensions do not match.");
        }
        const int ndims = e1.getNumDimensions();
        EuclideanVector result(ndims);
        for (int i = 0; i < ndims; i++) {
            result[i] = e1[i] + e2[i];
        }
        return result;
    }

    EuclideanVector operator-(EuclideanVector e1, EuclideanVector e2) {
        return e1 + (-1*e2);
    }

    double operator*(EuclideanVector e1, EuclideanVector e2) {
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

    EuclideanVector operator*(EuclideanVector e, double n) {
        evec::EuclideanVector result(e.dims_);
        for (unsigned int i = 0; i < e.dims_; ++i) {
            result[i] = e[i] * n;
        }
        return result;
    }

    EuclideanVector operator*(double n, EuclideanVector e) {
        return e * n;
    }

    EuclideanVector operator/(EuclideanVector e, const double n) {
        return e * (1/n);
    }

    std::ostream& operator<<(std::ostream& stream, const EuclideanVector& e) {
        stream << '[';
        for (unsigned int i = 0; i < e.dims_; ++i) {
            stream << e[i];
            if (i < (e.dims_ - 1)) {
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
