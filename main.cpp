#include <iostream>
#include <vector>
using namespace std;

#include "HashTable.hpp"

void operatorWithDelHashtable(HashTable<string>& ht) {
    ht.ht_print();
    ht.ht_del("11");
    ht.ht_del("22");
    ht.ht_del("ab");
    ht.ht_del("bc");
    ht.ht_print();
    ht.ht_del("c9");
    ht.ht_print();
    ht.ht_del("c8");
    ht.ht_print();
    ht.ht_del("c7");
    ht.ht_print();
    ht.ht_del("c6");
    ht.ht_print();
    ht.ht_del("c5");
    ht.ht_print();
    ht.ht_del("c4");
    ht.ht_print();
    ht.ht_del("c3");
    ht.ht_print();
    ht.ht_del("c2");
    ht.ht_print();
}

void operatorWithHashtable(HashTable<string>& ht) {
    cout << "++++++++++++++++++++++" << endl;
    ht.ht_insert("11", "11");
    cout << "++++++++++++++++++++++" << endl;
    ht.ht_insert("22", "22");
    cout << "++++++++++++++++++++++" << endl;
    ht.ht_insert("11", "11a");
    ht.ht_print();
    cout << "++++++++++++++++++++++" << endl;
    ht.ht_insert("ab", "ab");
    ht.ht_print();
    cout << "++++++++++++++++++++++" << endl;
    ht.ht_insert("bc", "bc");
    ht.ht_print();
    ht.ht_insert("mybrujmaonutk", "11");
    cout << "++++++++++++++++++++++" << endl;
    ht.ht_insert("c9", "c9");
    ht.ht_print();
    cout << "++++++++++++++++++++++" << endl;
    ht.ht_insert("c8", "c8");
    ht.ht_print();
    cout << "++++++++++++++++++++++" << endl;
    ht.ht_insert("c7", "c7");
    ht.ht_print();
    cout << "++++++++++++++++++++++" << endl;
    ht.ht_insert("c6", "c6");
    ht.ht_print();
    cout << "++++++++++++++++++++++" << endl;
    ht.ht_insert("c5", "c5");
    cout << "++++++++++++++++++++++" << endl;
    ht.ht_insert("c4", "c4");
    cout << "++++++++++++++++++++++" << endl;
    ht.ht_insert("c3", "c3");
    cout << "++++++++++++++++++++++" << endl;
    ht.ht_insert("c2", "c2");
    cout << "++++++++++++++++++++++" << endl;
    ht.ht_insert("c1", "c1");
    cout << "++++++++++++++++++++++" << endl;
    ht.ht_print();

    cout << "======end insert" << endl;

    string* value = ht.ht_search("11");
    cout << "value11: " << value << endl;
    value = ht.ht_search("22");
    cout << "value22: " << value << endl;
    cout << "------going to delete" << endl;
    operatorWithDelHashtable(ht);
    cout << "------end delete" << endl;
}

void test_string() {
    cout << "start." << endl;
    HashTable<string>& ht = HashTable<string>::ht_new();

    operatorWithHashtable(ht);

    ht.ht_destroy();

    cout << "end" << endl;
}
class ObjectA {
public:
    ObjectA(uint32_t age, uint32_t height, string name): age_(age), height_(height), name_(name) {

    }
    friend ostream& operator<<(ostream& out, ObjectA& o);
private:
    uint32_t age_;
    uint32_t height_;
    string name_;
};
ostream& operator<<(ostream& out, ObjectA& o) {
    out << "age: " << o.age_ << ", height: " << o.height_ << ", name: " << o.name_;
    return out;
}
void test_model() {
    cout << "start." << endl;
    HashTable<ObjectA>& ht = HashTable<ObjectA>::ht_new();
    ht.ht_insert("aker", ObjectA{32, 180, "aker"});
    ht.ht_print();
    ht.ht_destroy();
    cout << "end" << endl;
}

void test_charx() {
    cout << "start." << endl;
    HashTable<char*>& ht = HashTable<char*>::ht_new();
    ht.ht_insert("aker", "akerdi");
    ht.ht_print();
    ht.ht_destroy();
    cout << "end" << endl;
}

int main(int argc, char** argv) {
    cout.setf(ios::unitbuf);
    test_string();
    test_model();
    test_charx();
    return 0;
}
