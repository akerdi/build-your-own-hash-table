//
// Created by shaohong.jiang on 4/24/2023.
//

#include <stdio.h>
#include <math.h>

#include "HashTable.h"
#include "Prime.h"

#define HT_BASE_SIZE 7

int hashing(const char* key, int prime, int bucket_size) {
    int hash = 0;
    int key_len = strlen(key);
    for (int i = 0; i < key_len; i++) {
        hash = (pow(prime, key_len-(i+1)) * int(key[i]));
    }
    return hash % bucket_size;
}

#pragma mark - Hash_item

Hash_item::Hash_item(const char* key, const char* value) {
    this->key = strdup(key);
    this->value = strdup(value);
}
void Hash_item::hash_item_delete() {
    free(this->key);
    free(this->value);
    free(this);
}
char* Hash_item::get_value() {
    return value;
}

#pragma mark - HashTable

HashTable& HashTable::ht_new_base_size(int base_size) {
    int next_prime = Prime::next_Prime(base_size);
    HashTable* ht = new HashTable(base_size, next_prime);

    return *ht;
}

HashTable& HashTable::ht_new() {
    return ht_new_base_size(HT_BASE_SIZE);
}
int HashTable::ht_hash(const char *key, const int bucket_size) {
    int aIndex = hashing(key, 101, bucket_size);
    return aIndex;
}
void HashTable::ht_insert(const char *key, const char *value) {
    int index = ht_hash(key, size);
    Hash_item* hi = new Hash_item(key, value);
    items[index] = hi;
    count++;
}
char* HashTable::ht_search(const char *key) {
    int index = ht_hash(key, size);
    Hash_item* hi = items[index];
    return hi->get_value();
}
void HashTable::ht_del(const char *key) {
    int index = ht_hash(key, size);
    items[index]->hash_item_delete();
    items[index] = NULL;
    count--;
}

void HashTable::ht_destroy() {
    for (int i = 0; i < size; i++) {
        items[i]->hash_item_delete();
    }
    free(items);
    free(this);
}
