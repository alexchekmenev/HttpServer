#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include "headers.h"
template <typename T>
struct hash_table {
public:
    struct hash_entry_t {
        int fd;
        T* h;
        hash_entry_t* next;
    };
    typedef hash_entry_t* hash_entry;

    hash_table<T>(int size); //static hash_table* hash_table_init(int size);
    ~hash_table<T>();
    int key_in_table(int fd); //static int hash_value(hash_table* ht, int fd);
    T* get(int fd); //static handler* hash_get(hash_table* ht, int fd);
    int set(int fd, T* h); //static int hash_set(hash_table* ht, int fd, handler *h);
    int remove(int fd); //static int hash_remove(hash_table* ht, int fd);

private:
    hash_entry* table;
    int size;
};

#endif // HASH_TABLE_H

