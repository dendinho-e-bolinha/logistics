#pragma once

#include <unordered_map>

/**
 * @brief Sparse Boobacube Algorithm
 */
class SparseBoobacube {
    public:

        /**
         * @brief Manages a Entry
         */
        class Entry {
            int a, b, c, d;

            public:
                /**
                 * @brief Creates a new Entry instance
                 */
                Entry(int a, int b, int c, int d);

                /** Getters */
                int get_a() const;
                int get_b() const;
                int get_c() const;
                int get_d() const;

                /**
                 * @overload Equality operator overload 
                 */
                bool operator==(const Entry &other) const;

        };

        /**
         * @brief Manages the Hash for an Entry
         */
        struct EntryHash {
            /**
             * @brief Hash function for each Entry
             */
            std::size_t operator()(const Entry &entry) const;
        };

    private:

        /**
         * @brief Map with an Entry and its hash
         */
        std::unordered_map<Entry, int, EntryHash> boobacube;

        /**
         * @brief Default value
         */
        int defaultValue;

    public:
        /**
        /* @brief Constructs a new SparseBoobacube object
        /*
        /* @param defaultValue The boobacube's default value
        */
        SparseBoobacube(int defaultValue = -1);

        /**
        /* @brief Inserts or assigns a new Entry object into the sparse boobacube
        /*
        /* @param entry The entry to be added
        /* @param value The correspondent value
        */
        void insert(Entry entry, int value);

        /** 
        /* @brief Locates position of Entry object
        /*
        /* @param entry The Entry object to be located
        */
        int at(Entry entry) const;

        /** @brief Returns the boobacube's size */
        std::size_t size() const;

        /** 
        /* @brief Erases an Entry object from the boobacube
        /*
        /* @param entry The Entry object to be erased
        */
        void erase(Entry entry);

        /** @brief Clears all data in boobacube */
        void clear();
};
