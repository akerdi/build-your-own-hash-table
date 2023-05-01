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
    Hash_item(const char* key, const char* value);
    void hash_item_delete();
    char* get_key();
    char* get_value();
private:
    char* key;
    char* value;
};

class HashTable {
public:
    static HashTable& ht_new();
    void ht_insert(const char* key, const char* value);
    char* ht_search(const char* key);
    void ht_del(const char* key);
    void ht_print();
    void ht_destroy();
private:
    static HashTable& ht_new_base_size(int base_size);
    int ht_hash(const char* key, const int bucket_size, int attempt_i);
    void ht_del_with_index(int index);
    void ht_resize(int new_base_size);
    void ht_resize_up();
    void ht_resize_down();
    void ht_insert_ht_item(Hash_item* hi);
    HashTable(int bs, int s = 0): base_size(bs), size(s) {
        count = 0;
        size_sqrt = sqrt(size);
        items = (Hash_item**)calloc(s, sizeof(Hash_item*));
    }
private:
    int base_size;
    int size;
    int size_sqrt;
    Hash_item** items;
    int count;

};


#endif //HASH_TABLE_HASHTABLE_H
