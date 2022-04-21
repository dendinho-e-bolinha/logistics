#pragma once

#include <unordered_map>

/**
 * @brief A data structure for storing sparse 4-dimensional data
 */
class SparseHypercube {
    public:

        /**
         * @brief A 4-dimensional entry for the data structure
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
        std::unordered_map<Entry, int, EntryHash> hypercube;

        /**
         * @brief Default value
         */
        int defaultValue;

    public:
        /**
        /* @brief Constructs a new SparseHypercube object
        /*
        /* @param defaultValue The hypercube's default value
        */
        SparseHypercube(int defaultValue = -1);

        /**
        /* @brief Inserts or assigns a new Entry object into the sparse hypercube
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

        /** @brief Returns the hypercube's size */
        std::size_t size() const;

        /** 
        /* @brief Erases an Entry object from the hypercube
        /*
        /* @param entry The Entry object to be erased
        */
        void erase(Entry entry);

        /** @brief Clears all data in the hypercube */
        void clear();
};
