#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "entities/delivery.h"
#include "entities/driver.h"

using FileEntry = std::vector<std::string>;

class File {
    std::vector<std::string> columns;
    std::vector<FileEntry> entries;

    bool read_header(std::ifstream &file, char delim);
    bool read_body(std::ifstream &file, char delim);

public:
    File(std::string path, char delim = ' ');

    std::vector<std::string> get_columns() const;
    std::vector<FileEntry> get_entries() const;

    std::vector<Delivery> read_deliveries() const;
    std::vector<Driver> read_drivers() const;
};
