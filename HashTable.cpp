//
// Created by shaohong.jiang on 4/24/2023.
//

#include <stdio.h>
#include <math.h>

#include "HashTable.h"
#include "Prime.h"

#define HT_BASE_SIZE 7
#define HT_PRIME_CONST_1 101
#define HT_PRIME_CONST_2 103

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
char* Hash_item::get_key() {
    return key;
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
int HashTable::ht_hash(const char *key, const int bucket_size, int attempt_i) {
    int aIndex = hashing(key, HT_PRIME_CONST_1, bucket_size);
    int bIndex = hashing(key, HT_PRIME_CONST_2, bucket_size);
    return (aIndex + attempt_i * (bIndex+size_sqrt)) % bucket_size;
}

void HashTable::ht_resize(int new_base_size) {
    if (new_base_size < HT_BASE_SIZE) return;

    HashTable& new_ht = ht_new_base_size(new_base_size);
    for (int i = 0; i < size; i++) {
        Hash_item* hi = items[i];
        if (hi) {
            new_ht.ht_insert_ht_item(hi);
        }
    }

    base_size = new_ht.base_size;
    count = new_ht.count;

    int temp_size = size;
    size = new_ht.size;
    new_ht.size = temp_size;

    Hash_item** temp_items = items;
    items = new_ht.items;
    new_ht.count = 0;
    new_ht.items = temp_items;

    new_ht.ht_destroy();
}
void HashTable::ht_resize_up() {
    ht_resize(base_size * 2);
}
void HashTable::ht_resize_down() {
    ht_resize(base_size / 2);
}

void HashTable::ht_insert_ht_item(Hash_item* hi) {
    int index = ht_hash(hi->get_key(), size, 0);
    Hash_item* temp_hi = items[index];
    int i = 1;
    while (temp_hi) {
        if (strcmp(temp_hi->get_key(), hi->get_key()) == 0) {
            // replace value
            ht_del_with_index(index);
            break;
        }
        index = ht_hash(hi->get_key(), size, i);
        temp_hi = items[index];
        i++;
    }
    items[index] = hi;
    count++;
}

void HashTable::ht_insert(const char *key, const char *value) {
    int rate = count * 100 / size;
    if (rate > 70) {
        ht_resize_up();
    }
    Hash_item* hi = new Hash_item(key, value);

    ht_insert_ht_item(hi);
}
char* HashTable::ht_search(const char *key) {
    int index = ht_hash(key, size, 0);
    Hash_item* temp_hi = items[index];
    int i = 1;
    while (temp_hi) {
        if (strcmp(temp_hi->get_key(), key) == 0) {
            return items[index]->get_value();
        }
        index = ht_hash(key, size, i);
        temp_hi = items[index];
        i++;
    }
    return NULL;
}

void HashTable::ht_del(const char *key) {
    int rate = count * 100 / size;
    if (rate < 20) {
        ht_resize_down();
    }
    int index = ht_hash(key, size, 0);
    Hash_item* temp_hi = items[index];
    int i = 1;
    while (temp_hi) {
        if (strcmp(temp_hi->get_key(), key) == 0) {
            ht_del_with_index(index);
            return;
        }
        index = ht_hash(key, size, i);
        temp_hi = items[index];
        i++;
    }
    return;
}

void HashTable::ht_del_with_index(int index) {
    items[index]->hash_item_delete();
    items[index] = NULL;
    count--;
}
void HashTable::ht_print() {
    printf("- base_size: %d, size: %d, count: %d \nitems:\n", base_size, size, count);
    for (int i = 0; i < size; i++) {
        Hash_item *hi = items[i];
        if (hi) {
            printf("key: %s, value: %s.\n", hi->get_key(), hi->get_value());
        } else {
            printf("<empty>\n");
        }
    }
}

void HashTable::ht_destroy() {
    for (int i = 0; i < size; i++) {
        if (items[i]) {
            items[i]->hash_item_delete();
        }
    }
    free(items);
    free(this);
}
