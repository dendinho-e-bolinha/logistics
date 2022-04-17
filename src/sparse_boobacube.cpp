#include "scenarios/sparse_boobacube.h"

using namespace std;

SparseBoobacube::Entry::Entry(int a, int b, int c, int d) : a(a), b(b), c(c), d(d) {}

bool SparseBoobacube::Entry::operator==(const Entry &other) const {
    return other.a == this->a 
        && other.b == this->b
        && other.c == this->c 
        && other.d == this->d;
}

int SparseBoobacube::Entry::get_a() const {
    return a;
}

int SparseBoobacube::Entry::get_b() const {
    return b;
}

int SparseBoobacube::Entry::get_c() const {
    return c;
}

int SparseBoobacube::Entry::get_d() const {
    return d;
}

size_t SparseBoobacube::EntryHash::operator()(const Entry &entry) const {
    size_t seed = 0;

    hash<int> hasher;
    seed ^= hasher(entry.get_a()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    seed ^= hasher(entry.get_b()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    seed ^= hasher(entry.get_c()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    seed ^= hasher(entry.get_d()) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    
    return seed;
}

SparseBoobacube::SparseBoobacube(int defaultValue) : defaultValue(defaultValue) {}

void SparseBoobacube::insert(Entry entry, int value) {
    if (value == defaultValue) {
        return;
    }

    boobacube.insert_or_assign(entry, value);
}

int SparseBoobacube::at(Entry entry) const {
    auto it = boobacube.find(entry);
    if (it == boobacube.end()) {
        return defaultValue;
    }

    return it->second;
}

size_t SparseBoobacube::size() const {
    return boobacube.size();
}

void SparseBoobacube::erase(Entry entry) {
    boobacube.erase(entry);
}

void SparseBoobacube::clear() {
    boobacube.clear();
}