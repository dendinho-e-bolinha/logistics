#pragma once

#include <unordered_map>

class SparseBoobacube {
    public:

        class Entry {
            int a, b, c, d;

            public:
                Entry(int a, int b, int c, int d);

                int get_a() const;
                int get_b() const;
                int get_c() const;
                int get_d() const;

                bool operator==(const Entry &other) const;

        };

        struct EntryHash {
            std::size_t operator()(const Entry &entry) const;
        };

    private:
    
        std::unordered_map<Entry, int, EntryHash> boobacube;
        int defaultValue;

    public:

        SparseBoobacube(int defaultValue = -1);

        void insert(Entry entry, int value);
        int at(Entry entry) const;

        std::size_t size() const;

        void erase(Entry entry);
        void clear();
};
