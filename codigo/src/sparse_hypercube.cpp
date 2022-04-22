#include "sparse_hypercube.h"

using namespace std;

SparseHypercube::Entry::Entry(int a, int b, int c, int d) : a(a), b(b), c(c), d(d) {}

bool SparseHypercube::Entry::operator==(const Entry &other) const {
    return other.a == this->a 
        && other.b == this->b
        && other.c == this->c 
        && other.d == this->d;
}

int SparseHypercube::Entry::get_a() const {
    return a;
}

int SparseHypercube::Entry::get_b() const {
    return b;
}

int SparseHypercube::Entry::get_c() const {
    return c;
}

int SparseHypercube::Entry::get_d() const {
    return d;
}

size_t SparseHypercube::EntryHash::operator()(const Entry &entry) const {
    size_t seed = 0;

    hash<int> hasher;
    seed ^= hasher(entry.get_a()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    seed ^= hasher(entry.get_b()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    seed ^= hasher(entry.get_c()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    seed ^= hasher(entry.get_d()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    
    return seed;
}

SparseHypercube::SparseHypercube(int defaultValue) : defaultValue(defaultValue) {}

void SparseHypercube::insert(Entry entry, int value) {
    if (value == defaultValue) {
        return;
    }

    hypercube.insert_or_assign(entry, value);
}

int SparseHypercube::at(Entry entry) const {
    auto it = hypercube.find(entry);
    if (it == hypercube.end()) {
        return defaultValue;
    }

    return it->second;
}

size_t SparseHypercube::size() const {
    return hypercube.size();
}

void SparseHypercube::erase(Entry entry) {
    hypercube.erase(entry);
}

void SparseHypercube::clear() {
    hypercube.clear();
}