#include "EuclideanVector.h"
#include <vector>

// print vector
std::ostream& operator<<(std::ostream& stream, const std::vector<double>& v) {
    stream << '<';
    for (auto it = v.begin(); it < v.end(); ++it) {
        stream << *it;
        if (it < v.end() - 1) {
            stream << ' ';
        }
    }
    stream << '>';
    return stream;
}

void test(evec::EuclideanVector e) {
    using std::cout;
    using std::endl;
    cout << "---" << endl;
    cout << e << endl;
    cout << "Norm: " << e.getEuclideanNorm() << endl;
    cout << "Dims: " << e.getNumDimensions() << endl;
    cout << "Div 2: " << (e / 2) << endl;
    cout << "Unit Vector: " << e.createUnitVector() << endl;
    std::vector<double> v;
    v = e;
    cout << "Vector: " << v << endl;
    cout << "---" << endl;
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
    std::cout << v << std::endl;
    evec::EuclideanVector e(v.begin(), v.end());
    test(e);
    e[0] = 1;
    test(e);
    std::cout << e.get(0) << ' ' << e.get(2) << std::endl;
    test(e + e);
    e = e + e;
    test(e);
    e /= 4;
    test(e);

    // correctly throws since cant convert from string to double
    // std::vector<std::string> v1 = {"moo", "moo"};
    // evec::EuclideanVector e1(v1.begin(), v1.end());
    // std::cout << e1.getEuclideanNorm() << std::endl;
}
