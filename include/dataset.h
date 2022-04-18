#pragma once

#include <vector>
#include <string>
#include <fstream>

using FileEntry = std::vector<std::string>;

/** @brief Manages file operations */
class File {

    /** @brief Vector containing all column data*/
    std::vector<std::string> columns;

    /** @brief Vector containing all entry data */
    std::vector<FileEntry> entries;

    /**
     * @brief Reads file header
     * 
     * @param file The file to be read from
     * @param delim The character that delimits entries
     * @return true if data could be retrieved
     * @return false if data could not be retrieved
     */
    bool read_header(std::ifstream &file, char delim);
    
    /**
     * @brief Reads file body
     * 
     * @param file The file to be read from
     * @param delim The character that delimits entries
     * @return true if data could be retrieved
     * @return false if data could not be retrieved
     */
    bool read_body(std::ifstream &file, char delim);

public:
    /**
     * @brief Construct a new File object
     * 
     * @param path The file's absolute path
     * @param delim The character that delimits the data 
     */
    File(std::string path, char delim = ' ');

    /**
     * @brief Get the columns object
     * 
     * @return std::vector<std::string> 
     */
    std::vector<std::string> get_columns() const;

    /**
     * @brief Get the entries object
     * 
     * @return std::vector<FileEntry> 
     */
    std::vector<FileEntry> get_entries() const;
};