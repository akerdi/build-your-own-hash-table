//
// Created by shaohong.jiang on 4/24/2023.
//

#include <stdio.h>

#include "HashTable.h"
#include "Prime.h"

#define HT_BASE_SIZE 7
#define HT_PRIME_CONST_1 101
#define HT_PRIME_CONST_2 103
#define HASH_POW_MAX_LEN 5

static int min(int x, int y) {
    return x < y ? x : y;
}

static uint32_t hashing(const char* key, int prime, int bucket_size) {
    int hash = 0;
    int key_len = min(strlen(key), HASH_POW_MAX_LEN);
    for (int i = 0; i < key_len; i++) {
        hash += (pow(prime, key_len-(i+1)) * int(key[i]));
    }
    return hash % bucket_size;
}
static int floor_mod(const int mod_num, const int check_num) {
    return check_num % mod_num == 0 ? check_num - 1 : check_num;
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
    const uint32_t aIndex = hashing(key, HT_PRIME_CONST_1, bucket_size);
    const uint32_t bIndex = hashing(key, HT_PRIME_CONST_2, bucket_size);
    const int mod_index = floor_mod(bucket_size, (bIndex + 1));
    return (aIndex + attempt_i * mod_index) % bucket_size;
}

void HashTable::ht_resize(int new_base_size) {
    if (new_base_size < HT_BASE_SIZE) return;

    HashTable& new_ht = ht_new_base_size(new_base_size);
    for (int i = 0; i < size; i++) {
        Hash_item* hi = items[i];
        if (hi) {
            new_ht.ht_insert_ht_item(hi);
            items[i] = NULL;
        }
    }

    base_size = new_ht.base_size;
    count = new_ht.count;

    int temp_size = size;
    this->size = new_ht.size;
    new_ht.size = temp_size;

    Hash_item** temp_items = items;
    this->items = new_ht.items;
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
