#include <iostream>
#include "EuclideanVector.h"

int main(int argc, char* argv[]) {
    evec::EuclideanVector a = {1, 1};
    std::cout << a.getEuclideanNorm();
}