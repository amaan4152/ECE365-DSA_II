#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include "hash.h"

enum TYPE
{
    DICT,
    DOC
};

std::vector<std::string> getStrings(std::string); // convert file into list of strings delimited by '\n'
void spellcheck(std::ofstream &, hashTable *, std::string word, int);
void input_process(std::vector<std::string>, std::string, hashTable *);
bool isValid(std::string);

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
        if (!isValid(dict_word) || dict_word.size() > 20)
            continue;
        if (h_table->insert(dict_word) == 2)
            exit(EXIT_FAILURE);
    }
    std::clock_t end = std::clock();
    std::cout << "Total time (in seconds) to load dictionary: " << (float)((end - start) / (float)CLOCKS_PER_SEC) << std::endl;

    std::cout << "Enter name of input file: ";
    std::cin >> in_file;
    std::cout << "Enter name of output file: ";
    std::cin >> out_file;

    std::vector<std::string> input = getStrings(in_file);

    std::clock_t time_start = std::clock();
    input_process(input, out_file, h_table);
    std::clock_t time_end = std::clock();
    std::cout << "Total time (in seconds) to check document: " << (float)((time_end - time_start) / (float)CLOCKS_PER_SEC) << std::endl;

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

void input_process(std::vector<std::string> in_data, std::string out_f, hashTable *table)
{
    int line_num = 1;
    std::string word = "";
    std::ofstream o_file(out_f, std::ios::binary);
    for (std::string line : in_data)
    {
        if (line == "" && (++line_num))
            continue;
        if (isValid(line))
            spellcheck(o_file, table, line, line_num);
        else
        {
            for (int i = 0; i < line.size(); ++i)
            {
                char c = line[i];
                if (!(isalnum(c) || c == '-' || c == '\''))
                {
                    spellcheck(o_file, table, word, line_num);
                    word.clear();
                    continue;
                }
                word += c;
                if (i == (line.size() - 1))
                {
                    spellcheck(o_file, table, word, line_num);
                    word.clear();
                }
            }
        }
        ++line_num;
    }
    o_file.close();
}

void spellcheck(std::ofstream &out_f, hashTable *table, std::string word, int line_num)
{
    if (word.size() > 20)
        out_f << "Long word at line " << line_num << ", starts: " << word.substr(0, 20) << std::endl;
    else if (!table->contains(word))
        out_f << "Unknown word at line " << line_num << ": " << word << std::endl;
}

bool isValid(std::string word)
{
    for (char c : word)
    {
        if (isalnum(c) || c == '-' || c == '\'')
            continue;
        return false;
    }
    return true;
}