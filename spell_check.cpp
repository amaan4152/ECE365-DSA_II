#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include "hash.h"

enum TYPE {DICT, DOC};

std::vector<std::string> getStrings(std::string); // convert file into list of strings delimited by '\n'
std::pair<int, std::vector<char> *> isValid(const std::string &, int); // given dataset type (dictionary or input document), check if word is valid to not ignore

int main()
{
    std::string dict_file, in_file, out_file;
    std::cout << "Enter name of dictionary: ";
    std::cin >> dict_file;

    std::vector<std::string> dict = getStrings(dict_file);
    hashTable *h_table = new hashTable(dict.size());
    std::clock_t start = std::clock();
    for (std::string dict_word : dict)
    {
        if((isValid(dict_word, DICT)).first == -1)    continue; // skip invalid words
        if (h_table->insert(dict_word) == 2)
            exit(EXIT_FAILURE);
    }
    std::clock_t end = std::clock();
    std::cout << "Total time (in seconds) to load dictionary: " << (start - end) << std::endl;

    std::cout << "Enter name of input file: ";
    std::cin >> in_file;
    std::cout << "Enter name of output file: ";
    std::cin >> out_file;

    std::vector<std::string> input = getStrings(in_file);

    for(std::string line : input)
    {
        std::string segment;
        std::stringstream ss(line);
        std::vector<std::string> tokens;
        while(std::getline(ss, segment, ' '))
        {
            std::string word; 
            std::vector<char> *delims = isValid(segment, DOC).second;
            
        }
    }

    delete h_table;
}

// https://www.cplusplus.com/reference/istream/istream/read/
std::vector<std::string> getStrings(std::string filename)
{
    std::vector<std::string> str_list;
    std::string line;
    std::ifstream file(filename, std::ios::binary);
    while (std::getline(file, line))
    {
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);
        str_list.push_back(line);
    }
    file.close();
    return str_list;
}



std::pair<int, std::vector<char> *> isValid(const std::string &word, int type)
{
    std::pair<int, std::vector<char> *> res0(0, nullptr), res1(-1, nullptr);
    std::vector<char> *delims;
    for(int c = 0; c < word.size(); ++c)
    {
        if(!(std::isdigit(word[c]) || std::isalpha(word[c]) || word[c] == '-' || word[c] == '\''))
        {   
            if(type == DICT)    return res1;
            else    delims->push_back(word[c]);
        }
    }
    if(type == DOC) res0 = std::make_pair(1, delims);
    return res0;
}
