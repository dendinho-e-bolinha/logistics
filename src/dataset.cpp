#include <iostream>
#include <string>
#include <sstream>

#include "dataset.h"

using namespace std;

File::File(string path, char delim){
    ifstream file(path);

    if (!file.is_open())  {
        throw invalid_argument("Couldn't open given file");
    }

    if (!read_header(file, delim) || !read_body(file, delim)) {
        throw invalid_argument("Invalid format");
    }
}

bool File::read_header(ifstream &file, char delim) {
    string line;

    if (!getline(file, line)) {
        return false;
    }

    istringstream header(line);
    while(getline(header, line, delim))  {
        columns.push_back(line);
    }

    return true;
}

bool File::read_body(ifstream &file, char delim) {
    string line;
    
    while(getline(file, line))  {
        string data;
        vector<string> entry;
        
        istringstream body(line);
        while(getline(body, data, delim))  {
            entry.push_back(data);
        }

        entries.push_back(entry);
    }

    return true;
}

vector<string> File::get_columns() const {
    return columns;
}

vector<FileEntry> File::get_entries() const {
    return entries;    
}