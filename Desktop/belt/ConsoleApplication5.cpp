#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << x;
    }
    return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& kv : m) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << kv.first << ": " << kv.second;
    }
    return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
    if (t != u) {
        ostringstream os;
        os << "Assertion failed: " << t << " != " << u;
        if (!hint.empty()) {
            os << " hint: " << hint;
        }
        throw runtime_error(os.str());
    }
}

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}

class TestRunner {
public:
    template <class TestFunc>
    void RunTest(TestFunc func, const string& test_name) {
        try {
            func();
            cerr << test_name << " OK" << endl;
        }
        catch (exception& e) {
            ++fail_count;
            cerr << test_name << " fail: " << e.what() << endl;
        }
        catch (...) {
            ++fail_count;
            cerr << "Unknown exception caught" << endl;
        }
    }

    ~TestRunner() {
        if (fail_count > 0) {
            cerr << fail_count << " unit tests failed. Terminate" << endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};

class Rational {
public:
    // Вы можете вставлять сюда различные реализации,
    // чтобы проверить, что ваши тесты пропускают корректный код
    // и ловят некорректный

    Rational() : num(0), denom(1) {

    };
    Rational(int numerator, int denominator):num(0), denom(1) {
        
        if (denominator < 0)
                    {
                           denominator = -denominator;
                           numerator = -numerator;
                    }
            
                    if (numerator == 0) 
                    {
                        denominator = 1;
                    }
            
                    int gcd_value = gcd(numerator, denominator);
                   num = numerator / gcd_value;
                   denom = denominator / gcd_value;
    }

    int Numerator() const {
        return num;
    }

    int Denominator() const {
        return denom;
    }
private:
    int gcd(int a, int b) {
        return (abs(a) == 0) ? abs(b) : gcd(abs(b) % abs(a), abs(a));
    }
    int num;
    int denom;
};
void testDefaultConsturctor()
{
    AssertEqual(Rational().Numerator(), 0, "test Numerator = 0");
    AssertEqual(Rational().Denominator(), 1, "test Denominator = 1");
}
void testIrreducible()
{
    AssertEqual(Rational(1, 1).Numerator(), 1, "test 1/1 -> 1/1");
    AssertEqual(Rational(1, 1).Denominator(), 1, "test 1/1 -> 1/1");
    AssertEqual(Rational(3, 8).Numerator(), 3, "test 3/8 -> 3/8");
    AssertEqual(Rational(3, 8).Denominator(), 8, "test 3/8 -> 3/8");
}
void testZeroNumenator()
{
    AssertEqual(Rational(0, 25).Numerator(), 0, "test 0/25 -> 0/1");
    AssertEqual(Rational(0, 25).Denominator(), 1, "test 0/25 -> 0/1");
}
void testBothNegative()
{
    AssertEqual(Rational(-2, -3).Numerator(), 2, "test -2/-3 -> 2/3");
    AssertEqual(Rational(-2, -3).Denominator(), 3, "test -2/-3 -> 2/3");
    AssertEqual(Rational(-6, -12).Numerator(), 1, "test -6/-12 -> 1/2");
    AssertEqual(Rational(-6, -12).Denominator(), 2, "test -6/-12 -> 1/2");
}
void testNegativeDenominator()
{
    AssertEqual(Rational(6, -12).Numerator(), -1, "test 6/-12 -> -1/2");
    AssertEqual(Rational(6, -12).Denominator(), 2, "test -6/-12 -> -1/2");
}
void testNegativeNumerator()
{
    AssertEqual(Rational(-3, 12).Numerator(), -1, "test -3/12 -> -1/4");
    AssertEqual(Rational(-3, 12).Denominator(), 4, "test -3/12 -> -1/4");
}
void testFractionReduction()
{
    AssertEqual(Rational(24, 64).Numerator(), 3, "test 24/64 -> 3/8");
    AssertEqual(Rational(24, 64).Denominator(), 8, "test 24/64 -> 3/8");
    AssertEqual(Rational(2, 4).Numerator(), 1, "test 2/4 -> 1/2");
    AssertEqual(Rational(2, 4).Denominator(), 2, "test 2/4 -> 1/2");
}
int main() {
    TestRunner runner;
    runner.RunTest(testDefaultConsturctor, "test_rational");
    runner.RunTest(testIrreducible, "test_irreducible_fraction");
    runner.RunTest(testZeroNumenator, "test_zero_numenator");
    runner.RunTest(testBothNegative, "test_both_negative");
    runner.RunTest(testNegativeDenominator, "test_negative_denominator");
    runner.RunTest(testNegativeNumerator, "test_negative_numerator");
    runner.RunTest(testFractionReduction, "test_fraction_reduction");
    return 0;
}