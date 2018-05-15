#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

class Thing {
private:
    int* arr;
    int  size;

public:
    Thing(int size) {
        this->arr  = new int[size]();
        this->size = size;
    }

    // copy contructor
    Thing(const Thing& other) {
        this->size = other.size;
        arr = new int[this->size]();

        for (int i = 0; i < this->size; ++i) {
            this->arr[i] = other.arr[i];
        }
    }

    // operator= with copy swap
    Thing& operator=(Thing other) {
        std::swap(arr, other.arr);
        std::swap(size, other.size);

        return *this;
    }

    ~Thing() {
        delete[] arr;
        arr = nullptr;
    }

    const int& getSize() const { return size; }
    const int* getArr()  const { return arr;  }

    friend std::ostream& operator<<(std::ostream& out, const Thing& rhs) {
        out << rhs.size << ": ";
        for (int i = 0; i < rhs.size; ++i) {
            out << rhs.arr[i] << " ";
        }

        return out;
    }
};


void openAndReadFile(string filename) {
    std::ifstream infile(filename);

    if (infile.fail()) {
        throw std::invalid_argument("Error opening file: " + filename);
    }

    // using eof() function
    int d = 0;
    while (!infile.eof()) {
        infile >> d;
        cout << d << endl;
    }

    // using getline
    string line = "";
    while (getline(infile, line)) {
        // line is entire line now (up untill excl. \n)
        cout << line << " - ";
    }

    // using >>
    string word;
    while (infile >> word) {
        cout << word << " ";
    }
    cout << endl;

    // using stringstream
    string line2;
    while (getline(infile, line2)) {
        stringstream ss(line2);
        string firstWord, secondWord;
        ss >> firstWord >> secondWord;

        cout << secondWord << firstWord;
    }


    infile.close();  // not needed anymore, but nice to have.
}


void vectorDeleteWithIterators(vector<int> vec) {
    auto it = vec.begin();
    while (it != vec.end()) {
        if (*it == 42) {
            it = vec.erase(it);  // .erase returns iterator to next element
        }
        else {
            ++it;
        }
    }
}


void initVectorAndArray() {
    const int size = 6;
    vector<int> vec(size);  // all elems are 0
    vector<int> vec2 {1, 2, 3};  // size 3 with elems 1, 2, 3
    vec2 = {3, 2, 1};
    vector<int> vec3;  // size 0

    int arr[size] {0};  // init all elem to 0    
    int* dynArr = new int[size] {};  // all elems are 0
    int arr2[] {1, 2, 3};  // size 3, elems are 1, 3, 3

    delete[] dynArr;
}

void useUniquePtr(unique_ptr<int> argptr) {
    cout << *argptr;
}

void useUniquePtrRef(unique_ptr<int>& argptr) {
    cout << *argptr  << endl;
}

int* theifPtr;
void useOldPtrStyleThing(int* argptr) {
    *argptr = 6;
    theifPtr = argptr;
    cout << *argptr << endl;
}

void maliciousFunc() {
    *theifPtr = 1;
}

void uniquePointerTest() {
    unique_ptr<int> aptr = make_unique<int>(4);

    cout << *aptr << endl;

    useUniquePtrRef(aptr);
    //useUniquePtr(move(aptr));  // aptr is now nullptr, cannot be used after this line
    //useUniquePtr(aptr);  // doesn't even work, lol.

    useOldPtrStyleThing(aptr.get());
    // .get returns raw pointer and surrenders ownership

    maliciousFunc();  // changes value at memory loc of aptr
    cout << *aptr << endl;

    unique_ptr<int> cpyPtr = make_unique<int>(*aptr);

    unique_ptr<int> bptr = move(aptr);
    cout << *bptr << endl;
    // cout << *aptr << endl;  // crashes

    unique_ptr<vector<int>> vecPtr = make_unique<vector<int>>(16);
    *vecPtr = { 1, 2, 4 };

    int n;
    cin >> n;
    unique_ptr<int> nPtr = make_unique<int>(n);  // <=> int* nPtr = new int(n);

    //throw n;

    // delete nPtr;
    // something...
}

unique_ptr<int> returnUniquePtr(int a) {
    unique_ptr<int> aPtr = make_unique<int>(a);

    return move(aPtr);
    //return aPtr;
}

void enumTest() {
    enum DAYS { MONDAY=5, TUESDAY, ETC=5 };
    enum class MONTH {JAN=2, FEB=2, ETC};
    enum class alalal { JAN, FEB };

    DAYS m = MONDAY;
    if (ETC == MONDAY) {
        cout << ":(\n";
    }

    cout << TUESDAY;

    MONTH j = MONTH::JAN;
    string JAN = "jan";
    alalal asdf = alalal::JAN;

    if (MONTH::JAN == MONTH::FEB) {
        cout << "They're the same!";
    }

    enum COLOR { BLUE, RED, YELLOW };

    if (BLUE == MONDAY) {
        cout << "ja";
    }


}

void cString() {
    char t2[10] = "tekst";
    const char* t3 = "tekst";

    strcpy_s(t2, "abcde");
}

double myRound(double x, int precision) {  // x = 1.234567, p = 3
    bool neg = x < 0;

    double y = abs(x) * pow(10, precision);     // y = 1234.567
    int integerPart = (int)y;
    double decimal = y - integerPart;
    if (decimal >= 0.5) integerPart++;
    double returnVal = (double)integerPart / pow(10, precision);
    
    if (neg) returnVal *= -1;

    return returnVal;
}

double krisRound(double x, int precision) {
    int mantissa = x * pow(10, precision + 1);
    mantissa += 5 * (mantissa / abs(mantissa)); // Legger til +-5 avhengig av fortegn
    mantissa /= 10;
    return static_cast<double>(mantissa) / pow(10, precision);
}

void floorCeilTruncIOManip() {
    /* value   round   floor   ceil    trunc
        ---- - ---- - ---- - ----    ---- -
        2.3     2.0     2.0     3.0     2.0
        3.8     4.0     3.0     4.0     3.0
        5.5     6.0     5.0     6.0     5.0
      - 2.3   - 2.0   - 3.0   - 2.0   - 2.0
      - 3.8   - 4.0   - 4.0   - 3.0   - 3.0
      - 5.5   - 6.0   - 6.0   - 5.0   - 5.0
        */

    cout << myRound(2.3456, 3) << " " << myRound(3.8764, 3) << " " << myRound(-2.3456, 3) << " " << myRound(-3.8765, 3) << endl;
    cout << krisRound(2.3456, 3) << " " << krisRound(3.8764, 3) << " " << krisRound(-2.3456, 3) << " " << krisRound(-3.8765, 3) << endl;

    cout << setprecision(2) << setw(4);
}


class Test1
{
protected:
    int pa = 5;
public:
    int a = 1;
    int b = 2;

    int getB() { return b; }
};

class Test2 : protected Test1
{
public:
    int getA() { return a; }
};

class Test3 : public Test2
{

};

class Human {
protected:
    string name;
public:
    Human(string name) : name(name) {};

    string getName() { return name; }
    virtual void printName() = 0;  // pure virutal, making `Human` an abstract class
};

class Man : public Human
{
public:
    Man(string name) : Human(name) {};

    virtual void printName() override { cout << getName() << " the man\n"; }
};

class Woman : public Human
{
public:
    Woman(string name) : Human(name) {};

    virtual void printName() override { cout << getName() << " the woman\n"; }
};

class Person
{
private:
    string name;
public:
    Person(string name) : name(name) { };
    virtual string getName() { return "Person: " + name; }
};

class Student : public Person
{
private:
    int id;
public:
    Student(string name, int id) : Person(name), id(id) { };
    string getName() override { return "Student: " + Person::getName(); }
};

class Foo {
private:
	int* a;
public:
	Foo() : Foo(0) { cout << "Default constructor" << endl; }
	Foo(int a) : a(new int(a)) { cout << "Initializing list" << endl; }
	
	Foo(const Foo& other) {
		cout << "Copy constructor" << endl;
		this->a = new int(*(other.a));
	}
	
	//Foo& operator=(Foo rhs) {
	//	cout << "Assignment operator" << endl;
	//	swap(a, rhs.a); // copy and swap
	//	return *this;
	//}

	Foo& operator=(const Foo& rhs) {
		cout << "Assignment operator" << endl;
		this->a = new int(rhs.getA()); // Ikke copy-swap 
		return *this;
	}
	
	~Foo() {
		cout << "Destructor" << endl;
		delete a;
	}
	
	void setA(int n) { *a = n; }
	int getA() const { return *a; }	
};

ostream& operator<<(ostream& os, const Foo& f) {
	os << f.getA();
	return os;
}

void constructors() {
	cout << "Foo f1;" << endl;
	Foo f1; // Def
	cout << "Foo f2 = f1;" << endl;
	Foo f2 = f1; // Kaller kopi-konstruktør?
	cout << endl;

	cout << "f1: " << f1 << endl;
	cout << "f2: " << f2 << endl;
	cout << "f2.setA(5)" << endl;
	f2.setA(5);
	cout << "f1: " << f1 << endl;
	cout << "f2: " << f2 << endl;
	cout << "f1 = f2" << endl;
	f1 = f2;
	cout << "f1: " << f1 << endl;
	cout << "f2: " << f2 << endl;
}


int main() {
    //uniquePointerTest();

    /*auto aPtr = returnUniquePtr(4);
    cout << *aPtr << endl;*/
    //floorCeilTruncIOManip();
   /* Test1 t1;
    cout << t1.a << t1.b << endl;

    Test2 t2;
    cout << t2.getA() << endl;

    Test3 t3;
    cout << t3.getA() << endl;*/

    /*Person* pep = new Person("hei");
    Student* stud = new Student("ja", 123);

    vector<Person*> peps = { pep, stud };

    cout << pep->getName() << " " << stud->getName()  << endl;

    for (int i = 0; i < 2; ++i) {
        cout << peps[i]->getName() << endl;
    }*/

    Man m("ahah");
    m.printName();

    Woman w("asdf");
    w.printName();

    vector<Human*> humanPtrVec = { &m, &w };
    for (auto i : humanPtrVec) {
        i->printName();
    }

    vector<Human> humanVec = { m, w };
    for (auto i : humanVec) {
        i.printName();
    }
}