#include "EuclideanVector.h"
#include <stdexcept> // here or in header?

namespace evec {

    // takes the number of dimensions (as an unsigned int) but no
    // magnitudes, sets the magnitude in each dimension as 0.0.
    // This is the default constructor, with the default value being 1. 
    EuclideanVector::EuclideanVector(unsigned int dims = 1): EuclideanVector(dims, 0) {}

    EuclideanVector::EuclideanVector(unsigned int dims, double mag): vals(dims, mag) {}

    // A constructor (or constructors) that takes the start and end of an
    // iterator and works out the required dimensions, and sets the
    // magnitude in each dimension according to the iterated values.
    // The iterators will be from std::vector or std::list.
    // Hint: a function template may help. 
    template<class iterator_type>
    EuclideanVector::EuclideanVector(iterator_type begin, iterator_type end): vals(begin, end) {}

    // initializer list constructor e.g. `EuclideanVector a {1,2,3,4};`
    EuclideanVector::EuclideanVector(std::initializer_list<double> mags): vals{mags} {}

    // copy constructor
    EuclideanVector::EuclideanVector(const EuclideanVector &original) {
        for (const double val : original.vals) {
            vals.push_back(val);
        }
    }

    // move constructor
    // EuclideanVector::EuclideanVector(EuclideanVector &original): vals(std::move(original.vals)), norm(std::move(original.norm)) {}

    unsigned int EuclideanVector::getNumDimensions() {
        // size_t is unsigned
        // any problem if just `return vals.size()`?
        std::size_t n = vals.size();
        return static_cast<unsigned int>(n);
    }

    double EuclideanVector::get(unsigned int i) {
        return vals[i];
    }

    double EuclideanVector::getEuclideanNorm() {
        if (norm < 0) {
            // calculate norm
            norm = 0;
            for (double val : vals) {
                norm += val * val;
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

    // copy assignment
    EuclideanVector EuclideanVector::operator=(const EuclideanVector &e) {
        // copy and swap
        EuclideanVector tmp = e;
        std::swap(tmp, *this);
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
        // would copying then dividing be better?
        std::vector<double> v;
        for (const double val : e.vals) {
            v.push_back(val * n);
        }
        evec::EuclideanVector result(v.begin(), v.end());
        return result;
    }

    EuclideanVector operator*(double n, EuclideanVector e) {
        return e * n;
    }

    EuclideanVector operator/(EuclideanVector e, const double n) {
        return e * (1/n);
    }

    std::ostream& operator<<(std::ostream& stream, const EuclideanVector& e) {
        stream << "[";
        for (auto i = e.vals.begin(); i != e.vals.end(); i++) {
            stream << *i;
            if (i != e.vals.end() - 1) {
                stream << " ";
            }
        }
        stream << "]";
        return stream;
    }
}


// for testing, move to own file

void test(evec::EuclideanVector e) {
    using std::cout;
    using std::endl;
    cout << "---" << endl;
    cout << e << endl;
    cout << "Norm: " << e.getEuclideanNorm() << endl;
    cout << "Dims: " << e.getNumDimensions() << endl;
    cout << "Div 2: " << (e / 2) << endl;
    cout << "Unit Vector: " << e.createUnitVector() << endl;
}


int main(int argc, char* argv[]) {
    evec::EuclideanVector v0;
    test(v0);

    evec::EuclideanVector v1(4);
    test(v1);

    evec::EuclideanVector v2(4, 1.5);
    test(v2);

    const evec::EuclideanVector a = {1, 1};
    test(a);

    std::vector<double> v = {2, 2, 3};
    evec::EuclideanVector e(v.begin(), v.end());
    test(e);
    e[0] = 1;
    test(e);
    std::cout << e.get(0) << ' ' << e.get(2) << std::endl;
    e /= 2;
    test(e);

    // correctly throws since cant convert from string to double
    // std::vector<std::string> v1 = {"moo", "moo"};
    // evec::EuclideanVector e1(v1.begin(), v1.end());
    // std::cout << e1.getEuclideanNorm() << std::endl;
}
