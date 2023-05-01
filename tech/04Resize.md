# Resize

目前输入的容器数目只有7个(HT_BASE_SIZE), 我们只要在`void(*HashTable::ht_insert)(const char*, const char*)` 和`void (*HashTable::ht_del)(const char*)`判断放大或者缩小容器的数目，并且将原有的数据计算对应位置迁入新的容器

## 容器调整

```c++
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
```

原理是创建一个新的HashTable，并调整好容器的大小，然后将原有的数据全数挪入新的容器中。之后就是将新的数据，替换回原有对象，删除新的对象。

提供增大缩小便捷函数:

```c++
void HashTable::ht_resize_up() {
    ht_resize(base_size * 2);
}
void HashTable::ht_resize_down() {
    ht_resize(base_size / 2);
}
```

之后只需要设计插入比例、删除比例时执行对应的逻辑:

```c++
void HashTable::ht_insert(const char *key, const char *value) {
    int rate = count * 100 / size;
    if (rate > 70) {
        ht_resize_up();
    }
    ...
```

```c++
void HashTable::ht_del(const char *key) {
    int rate = count * 100 / size;
    if (rate < 20) {
        ht_resize_down();
    }
    ...
```

以上完成 `HashTable` .