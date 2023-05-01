//
// Created by shaohong.jiang on 4/24/2023.
//

#include <stdio.h>

#include "HashTable.h"

#define HT_BASE_SIZE 7

Hash_item::Hash_item(char* key, char* value) {
    this->key = strdup(key);
    this->value = strdup(value);
}
void Hash_item::hash_item_delete() {
    free(this->key);
    free(this->value);
    free(this);
}

#pragma mark - HashTable

HashTable& HashTable::ht_new_base_size(int base_size) {
    HashTable* ht = new HashTable(base_size);
    return *ht;
}

HashTable& HashTable::ht_new() {
    return ht_new_base_size(HT_BASE_SIZE);
}

void HashTable::ht_del() {
    for (int i = 0; i < size; i++) {
        items[i]->hash_item_delete();
    }
    free(items);
    free(this);
}
