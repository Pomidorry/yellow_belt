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

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        firstName[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        lastName[year] = last_name;
    }
    string GetFullName(int year) {
        string first_name = GetFirstName(year);
        string last_name = GetLastName(year);
        string full_name = first_name + " " + last_name;
        if (first_name.size() == 0 && last_name.size() == 0) {
            full_name = "Incognito";
            return full_name;
        }
        else if (first_name.size() != 0 && last_name.size() == 0) {
            full_name = first_name+" with unknown last name";
            return full_name;
        }
        else if (first_name.size() == 0 && last_name.size() != 0) {
            full_name = last_name + " with unknown first name";
            return full_name;
        }
        else {
            return full_name;
        }
    }
private:
    map<int, string> firstName;
    map<int, string> lastName;
    string GetFirstName(int year) {
        string first_name = "";
        while (firstName.count(year) == 0 && year > 0) {
            --year;
        }
        first_name = firstName[year];
        return first_name;
    }
    string GetLastName(int year) {
        string last_name = "";
        while (lastName.count(year) == 0 && year > 0) {
            --year;
        }
        last_name = lastName[year];
        return last_name;
    }
};
void test_incognito()
{
    Person person_test;
    person_test.ChangeFirstName(1965, "test_first_name1");
    person_test.ChangeLastName(1967, "test_last_name1");
    AssertEqual(person_test.GetFullName(1900), "Incognito", "test_1_incog");
}
void test_unknown_first_name()
{
    Person person_test;
    person_test.ChangeLastName(1900, "test_last_name1");
    person_test.ChangeFirstName(1905, "test_first_name1");
    AssertEqual(person_test.GetFullName(1903), "test_last_name1 with unknown first name", "test_1_unknown_fn");
}
void test_last_name_unknown() {
    Person person_test;
    person_test.ChangeLastName(1905, "test_last_name3");
    person_test.ChangeFirstName(1900, "test_first_name3");
    AssertEqual(person_test.GetFullName(1903), "test_first_name3 with unknown last name", "test_1_unknown_ln");
}
void test_is_changed_first_name()
{
    Person person_test;
    person_test.ChangeFirstName(2900, "test_first_name1");
    person_test.ChangeFirstName(2902, "test_first_name2");
    AssertEqual(person_test.GetFullName(2899), "Incognito", "test_1");
    AssertEqual(person_test.GetFullName(2900), "test_first_name1 with unknown last name", "test_1_first_name");
    AssertEqual(person_test.GetFullName(2901), "test_first_name1 with unknown last name", "test_1_first_name");
    AssertEqual(person_test.GetFullName(2902), "test_first_name2 with unknown last name", "test_1_first_name");
}
void test_is_changed_lst_name()
{
    Person person_test;
    person_test.ChangeLastName(2900, "test_last_name1");
    person_test.ChangeLastName(2902, "test_last_name2");
    AssertEqual(person_test.GetFullName(2899), "Incognito", "test_1");
    AssertEqual(person_test.GetFullName(2900), "test_last_name1 with unknown first name", "test_1_last_name");
    AssertEqual(person_test.GetFullName(2901), "test_last_name1 with unknown first name", "test_1_last_name");
    AssertEqual(person_test.GetFullName(2902), "test_last_name2 with unknown first name", "test_1_last_name");
}
void test_both_name()
{
    Person person_test;
    person_test.ChangeFirstName(1900, "test_first_name1");
    person_test.ChangeLastName(1902, "test_last_name1");
    AssertEqual(person_test.GetFullName(1903), "test_first_name1 test_last_name1", "test_1_both");
}
void test_change_both_name()
{
    Person person_test;
    person_test.ChangeFirstName(1900, "test_first_name1");
    person_test.ChangeLastName(1902, "test_last_name1");
    person_test.ChangeFirstName(1904, "test_first_name2");
    person_test.ChangeLastName(1905, "test_last_name2");
    AssertEqual(person_test.GetFullName(1906), "test_first_name2 test_last_name2", "test_1_both");
}
void is_saved_first_name()
{
    Person person_test;
    person_test.ChangeFirstName(1900, "test_first_name1");
    person_test.ChangeLastName(1902, "test_last_name1");
    person_test.ChangeFirstName(1905, "test_first_name2");
    AssertEqual(person_test.GetFullName(1903), "test_first_name1 test_last_name1", "test_1_save");
}
void is_saved_last_name()
{
    Person person_test;
    person_test.ChangeLastName(1900, "test_last_name1");
    person_test.ChangeFirstName(1902, "test_first_name1");
    person_test.ChangeLastName(1905, "test_last_name2");
    AssertEqual(person_test.GetFullName(1903), "test_first_name1 test_last_name1", "test_1_save");
}
int main() {
    TestRunner runner;
    runner.RunTest(test_incognito, "test_incognito");
    runner.RunTest(test_unknown_first_name, "test_unknown_first_name");
    runner.RunTest(test_is_changed_first_name, "test_change_first_name");
    runner.RunTest(test_last_name_unknown, "test_unknown_last_name");
    runner.RunTest(test_is_changed_lst_name, "test_change_last_name");
    runner.RunTest(test_both_name, "test_both_name");
    runner.RunTest(test_change_both_name, "test_change_both_name");
    runner.RunTest(is_saved_first_name, "save_first_name");
    runner.RunTest(is_saved_last_name, "save_last_name");
    return 0;
}
