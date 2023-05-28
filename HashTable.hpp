//
// Created by shaohong.jiang on 4/24/2023.
//

#ifndef HASH_TABLE_HASHTABLE_HPP
#define HASH_TABLE_HASHTABLE_HPP

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
template<class V>
class Hash_item {
public:
    Hash_item(const char* key, const V& value) {
        this->key = strdup(key);
        V* newValue = new V(value);
        this->value = newValue;
    }
    void hash_item_delete() {
        free(this->key);
        if (this->value)
            free(this->value);
        this->value = NULL;
        free(this);
    }
    char* get_key() {
        return key;
    }
    V* get_value() {
        return value;
    }
private:
    char* key;
    V* value;
};
template<> void Hash_item<string>::hash_item_delete() {
    free(this->key);
    if (this->value)
        free(this->value);
    this->value = NULL;
    free(this);
}
template<> void Hash_item<char*>::hash_item_delete() {
    free(this->key);
    if (this->value)
        free(this->value);
    this->value = NULL;
    free(this);
}

#pragma mark - HashTable

template<class V>
class HashTable {
public:
    HashTable(int bs, int s = 0): base_size(bs), size(s) {
        count = 0;
        items = (Hash_item<V>**)calloc(s, sizeof(Hash_item<V>*));
    }
    void ht_insert(const char* key, const V& value) {
        int rate = count * 100 / size;
        if (rate > 70) {
            ht_resize_up();
        }
        Hash_item<V>* hi = new Hash_item<V>(key, value);
        ht_insert_ht_item(hi);
    }
    V* ht_search(const char* key) {
        int index = ht_hash(key, size, 0);
        Hash_item<V>* temp_hi = items[index];
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
    void ht_del(const char* key) {
        int rate = count * 100 / size;
        if (rate < 20) {
            ht_resize_down();
        }
        int index = ht_hash(key, size, 0);
        Hash_item<V>* temp_hi = items[index];
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
    void ht_print() {
        printf("- base_size: %d, size: %d, count: %d \nitems:\n", base_size, size, count);
        for (int i = 0; i < size; i++) {
            Hash_item<V>* hi = items[i];
            if (hi) {
                cout << "key: " << hi->get_key() << ", value: " << *hi->get_value() << "." << endl;
            } else {
                printf("<empty>\n");
            }
        }
    }
    void ht_destroy() {
        for (int i = 0; i < size; i++) {
            if (items[i]) {
                items[i]->hash_item_delete();
            }
        }
        free(items);
        free(this);
    }

    static HashTable& ht_new() { return ht_new_base_size(HT_BASE_SIZE); }
private:
    int ht_hash(const char* key, const int bucket_size, int attempt_i) {
        const uint32_t aIndex = hashing(key, HT_PRIME_CONST_1, bucket_size);
        const uint32_t bIndex = hashing(key, HT_PRIME_CONST_2, bucket_size);
        const int mod_index = floor_mod(bucket_size, (bIndex + 1));
        return (aIndex + attempt_i * mod_index) % bucket_size;
    }
    void ht_del_with_index(int index) {
        items[index]->hash_item_delete();
        items[index] = NULL;
        count--;
    }
    void ht_resize(int new_base_size) {
        if (new_base_size < HT_BASE_SIZE) return;

        HashTable& new_ht = ht_new_base_size(new_base_size);
        for (int i = 0; i < size; i++) {
            Hash_item<V>* hi = items[i];
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

        Hash_item<V>** temp_items = items;
        this->items = new_ht.items;
        new_ht.count = 0;
        new_ht.items = temp_items;

        new_ht.ht_destroy();
    }
    void ht_resize_up() { ht_resize(base_size * 2); }
    void ht_resize_down() { ht_resize(base_size / 2); }
    void ht_insert_ht_item(Hash_item<V>* hi) {
        int index = ht_hash(hi->get_key(), size, 0);
        Hash_item<V>* temp_hi = items[index];
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

    static HashTable& ht_new_base_size(int base_size) {
        int next_prime = Prime::next_Prime(base_size);
        HashTable* ht = new HashTable(base_size, next_prime);

        return *ht;
    }
private:
    int base_size;
    int size;
    Hash_item<V>** items;
    int count;
};

#endif //HASH_TABLE_HASHTABLE_HPP
