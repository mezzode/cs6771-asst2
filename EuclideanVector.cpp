#include <vector>
#include "EuclideanVector.h"

namespace evec {
    class EuclideanVector {
        public:
            // A constructor that takes the number of dimensions (as an unsigned int) but no magnitudes,
            // sets the magnitude in each dimension as 0.0.
            // Hint: you may want to make this a delegating constructor to the next constructor below. 
            // This is the default constructor, with the default value being 1. 
            EuclideanVector(unsigned int dims) {

            }

            EuclideanVector(unsigned int dims, double mag): vals(dims, mag) {
                
            }


            unsigned int getNumDimensions() {
                return vals.size(); // what type is this? any concerns about type casting?
            }

            double get(unsigned int i) {
                return vals[i];
            }

            double getEuclideanNorm() {
                if (norm < 0) {
                    // calculate norm
                    norm = 1;
                }
                return norm; // TODO:
            }

            EuclideanVector createUnitVector() {
                const double norm = getEuclideanNorm();
                return this / norm; // TODO
            }
        private:
            std::vector<double> vals;
            double norm; // need to cache norm if possible
    };
}
