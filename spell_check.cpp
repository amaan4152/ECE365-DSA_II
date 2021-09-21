#include <iostream>
#include <fstream>
#include "hash.h"

// https://www.cplusplus.com/reference/istream/istream/read/
std::vector<std::string> getStrings(std::string filename)
{
    std::vector<std::string> str_list;
    std::string line;
    std::ifstream file(filename, std::ios::binary);
    while (std::getline(file, line))
        str_list.push_back(line);

    file.close();
    return str_list;
}

int main()
{
    std::string dict_file, in_file, out_file;
    std::cout << "Enter name of dictionary: ";
    std::cin >> dict_file;
    std::cout << "Enter name of input file: ";
    std::cin >> in_file;
    std::cout << "Enter name of output file: ";
    std::cin >> out_file;

    std::vector<std::string> dict = getStrings(dict_file);
    std::vector<std::string> input = getStrings(in_file);
    hashTable *h_table = new hashTable(dict.size());
    for (std::string dict_word : dict)
    {
        if (h_table->insert(dict_word) == 2)
            exit(EXIT_FAILURE);

        std::cout << "processing..." << std::endl;
    }
    delete h_table;
}