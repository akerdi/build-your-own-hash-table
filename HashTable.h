//
// Created by shaohong.jiang on 4/24/2023.
//

#ifndef HASH_TABLE_HASHTABLE_H
#define HASH_TABLE_HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
class Hash_item {
public:
    Hash_item(char* key, char* value);
    void hash_item_delete();
private:
    char* key;
    char* value;
};

class HashTable {
public:
    static HashTable& ht_new();
    void ht_del();
private:
    static HashTable& ht_new_base_size(int base_size);
    HashTable(int bs): base_size(bs), size(0) {
        count = 0;
        items = (Hash_item**)calloc(bs, sizeof(Hash_item*));
    }
private:
    int base_size;
    int size;
    Hash_item** items;
    int count;

};


#endif //HASH_TABLE_HASHTABLE_H
