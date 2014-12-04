#include "hash_table.h"
template <typename T>
hash_table<T>::hash_table(int size) {
    try {
        hash_table::table = new hash_entry[size];
    } catch(...) {
        //TODO
    }
    hash_table::size = size;
}
template <typename T>
hash_table<T>::~hash_table() {
    delete[] table;
}

template <typename T>
int hash_table<T>::key_in_table(int fd) {
    return fd % size;
}

template <typename T>
T* hash_table<T>::get(int fd) {
    int hv = key_in_table(fd);
    hash_entry he = table[hv];
    while (he) {
        if (he->fd == fd) {
            return he->h;
        }
        he = he->next;
    }
    return NULL;
}

template <typename T>
int hash_table<T>::set(int fd, T* h) {
    int hv = key_in_table(fd);
    hash_entry* he = &table[hv];
    hash_entry n;

    while (*he) {
        if ((*he)->fd == fd) {
            (*he)->h = h;
            return 1;
        }
        he = &((*he)->next);
    }

    *he = malloc(sizeof(hash_entry_t));
    memset(*he, 0, sizeof(hash_entry_t));
    (*he)->h = h;
    (*he)->fd = fd;
    return 1;
}

template <typename T>
int hash_table<T>::remove(int fd) {
    int hv = key_in_table(fd);
    hash_entry *he = &table[hv];
    hash_entry n;

    while(*he) {
        if((*he)->fd == fd) {
            *he = (*he)->next;
            return 1;
        }
        he = &((*he)->next);
    }
    return 0;
}
