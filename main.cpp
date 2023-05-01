#include <iostream>

#include "HashTable.h"

int main(int argc, char** argv) {
    HashTable& ht = HashTable::ht_new();
    ht.ht_insert("11", "22");
    ht.ht_insert("22", "33");
    char* value = ht.ht_search("11");
    std::cout << "value11: " << value << std::endl;
    value = ht.ht_search("22");
    std::cout << "value22: " << value << std::endl;
    ht.ht_destroy();
    std::cout << "end" << std::endl;
    return 0;
}
