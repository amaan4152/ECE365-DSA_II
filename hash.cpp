#include "hash.h"
#include <valarray>
#include <iostream>
#define LOAD_LIMIT 0.75

hashTable::hashTable(int size) : capacity{(int)getPrime(size)}, filled{0}
{
    this->data.resize(this->capacity);
}

unsigned int hashTable::getPrime(int size)
{
    std::valarray<int> optimal_primes{53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469, 12582917};
    optimal_primes[optimal_primes < size] = 0;
    std::valarray<int> shifted_primes = optimal_primes.shift(std::count(std::begin(optimal_primes), std::end(optimal_primes), 0));
    return shifted_primes[0];
}

int hashTable::insert(const std::string &key, void *pv)
{
    double load_factor;
    int index = this->hash(key);
    if (this->contains(key))
        return 1; // key exists in hash table
    for (index %= this->capacity; (this->data)[index].isOccupied; index++)
    {
    }
    this->filled++;
    this->data[index].key = key;
    this->data[index].isOccupied = true;
    this->data[index].isDeleted = false;
    this->data[index].pv = pv;
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
    unsigned long hash = 5381;
    for (int c : key)
        hash = ((hash << 5) + hash) + c;

    return (hash % this->capacity);
}

bool hashTable::rehash()
{
    this->capacity = 2 * (this->data.size());
    std::vector<hashItem> old_table = this->data;
    this->data.clear();
    this->data.resize(getPrime(capacity));
    for (hashItem entry : old_table)
    {
        if (entry.key == "")
            continue;
        this->insert(entry.key);
    }
    // https://stackoverflow.com/questions/10464992/c-delete-vector-objects-free-memory
    std::vector<hashItem>().swap(old_table);
    return true;
}

bool hashTable::contains(const std::string &key)
{
    if (this->findPos(key) != -1)
        return true;
    return false;
}

int hashTable::findPos(const std::string &key)
{
    auto itr = std::find_if(this->data.cbegin(), this->data.cend(), [&](hashItem i)
                            { return (i.key == key); });
    return (itr != this->data.cend()) ? std::distance(this->data.cbegin(), itr) : -1;
}
