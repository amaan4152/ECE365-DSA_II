#include "hash.h"
#include <valarray>
#include <iostream>
#include <ctime>
#define LOAD_LIMIT 0.45

hashTable::hashTable(int size) : capacity{(int)getPrime(size)}, filled{0}
{
    this->data.resize(this->capacity);
}

unsigned int hashTable::getPrime(int size)
{
    int next_prime = 0;
    std::vector<int> optimal_primes{53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917};
    for (int prime : optimal_primes)
    {
        if (prime > size)
        {
            next_prime = prime;
            break;
        }
    }
    return next_prime;
}

int hashTable::insert(const std::string &key, void *pv)
{
    double load_factor;
    if (this->contains(key))    return 1; // key exists in hash table
    int index = this->hash(key);

    // linear probe
    while((this->data)[index].isOccupied)
        (++index) %= this->capacity;

    // fill entry 
    this->filled++;
    this->data[index].key = key;
    this->data[index].isOccupied = true;
    this->data[index].isDeleted = false;
    this->data[index].pv = pv;

    // rehash once load factor reached limit or greater
    if ((load_factor = filled / capacity) >= LOAD_LIMIT)
    {
        if (!this->rehash())
        {
            std::cerr << "[FATAL]: Memory allocation for <REHASHING> failed" << std::endl;
            return 2;
        }
    }
    return 1;
}

// http://www.cse.yorku.ca/~oz/hash.html
int hashTable::hash(const std::string &key)
{
    size_t hash = 1315423911;
    for(std::size_t i = 0; i < key.length(); ++i)
        hash ^= ((hash << 5) + key[i] + (hash >>2));
    return (hash % this->capacity);
}

bool hashTable::rehash()
{
    try
    {
        // update the capacity and preserve the old hashtable
        this->capacity = 2 * (this->data.size());
        std::vector<hashItem> old_table = this->data;
        this->data.clear();
        this->data.resize(getPrime(capacity));

        // fill up the new table
        for (hashItem entry : old_table)
        {
            if (entry.isOccupied == false)
                continue;
            this->insert(entry.key);
        }

        // https://stackoverflow.com/questions/10464992/c-delete-vector-objects-free-memory
        std::vector<hashItem>().swap(old_table);
        return true;
    }
    catch(std::bad_alloc)
    {
        return false;
    }
}

bool hashTable::contains(const std::string &key)
{
    if (this->findPos(key) != -1)   return true;
    return false;
}

int hashTable::findPos(const std::string &key)
{
    unsigned int index = this->hash(key);
    while(this->data[index].isOccupied)
    {
        if(this->data[index].key == key)
            return index;
        (++index) %= this->capacity;
    }
    return -1;
}
