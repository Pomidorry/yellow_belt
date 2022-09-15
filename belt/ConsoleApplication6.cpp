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

bool IsPalindrom(const string& str) {
    if (str.size() == 0||str.size()==1) {
        return 1;
    }
    for (int i = 0; i < str.size() / 2; i++) {
        if (str[i] != str[str.size() - 1]) {
            return 0;
        }
        else {
            return 1;
        }
    }
}
void isPalindrom1()
{
    Assert(IsPalindrom(""), "empty string ->> palindrome");
    Assert(IsPalindrom("tacocat"), "tacocat ->> palindrome");
    Assert(IsPalindrom("taccat"), "taccat ->> palindrome");
    Assert(IsPalindrom("a"), "a ->> palindrome");
    Assert(IsPalindrom(" ajja ajja "), " ajja ajja  ->> palindrome");
    Assert(IsPalindrom("aaaa"), "aaaa ->>not palindrome");
    Assert(!IsPalindrom(" ajja ajja"), " ajja ajja ->>not palindrome");
    Assert(!IsPalindrom("OK"), "OK ->>not palindrome");
}
int main() {
    TestRunner runner;
    runner.RunTest(isPalindrom1, "isPalindrome");
    return 0;
}