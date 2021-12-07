#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string.h>

#define MAX 1000

static bool isMerged[MAX + 1][MAX + 1];

std::stringstream toBuff(std::string);    // read file into buffer
void merge(const std::string &, const std::string &, const std::string &);
std::string highlight(const std::string &, const std::string &, std::string);

int main(void)
{
    std::string input = "", output = ""; 
    std::string A = "", B = "", C = "";

    std::cerr << "Name of input file: ";
    std::cin >> input;
    std::cerr << "Name of output file: ";
    std::cin >> output;
    auto ss_buff = toBuff(input);

    std::ofstream outfile(output);
    std::clock_t start = std::clock();
    while (getline(ss_buff, A) && getline(ss_buff, B) && getline(ss_buff, C)){
        merge(A, B, C);
        outfile << highlight(A, B, C) << "\n";
    }
    std::clock_t end = std::clock();
    auto time = (end - start) / ((float) CLOCKS_PER_SEC);
    
    std::cerr << "Time to validate merges: " << time << "\n";
    return 0;
}

std::stringstream toBuff(std::string filename)
{
    std::stringstream buff;
    std::ifstream file(filename);
    buff << file.rdbuf();
    file.close();

    return buff;
}

void merge(const std::string &A, const std::string &B, const std::string &C)
{
    long unsigned int M = A.size(), N = B.size();

    /* Iniitialize to all false */
    memset(isMerged, 0, sizeof(isMerged));

    /* Fail cases */
    if ((M + N) != C.size())  
        return;
    else if (!(A.back() == C.back() || B.back() == C.back()))
        return;
    
    /* Check if merge valid */
    for (long unsigned int i = 0; i <= M; ++i){
        for (long unsigned int j = 0; j <= N; ++j){
            char a = A[i - 1], b = B[j - 1], c = C[i + j -1];
            bool a_c = a == c, b_c = b == c;

            if (!i && !j)   
                isMerged[i][j] = true;
            else if (!i && b == C[j - 1]){
                isMerged[i][j] = isMerged[i][j - 1];
            }
            else if (!j && a == C[i - 1]){
                isMerged[i][j] = isMerged[i - 1][j];
            }
            else if (a_c && !b_c)
                isMerged[i][j] = isMerged[i - 1][j];

            else if (!a_c && b_c)
                isMerged[i][j] = isMerged[i][j - 1];

            else if (a_c && b_c)
                isMerged[i][j] = (isMerged[i - 1][j] || isMerged[i][j - 1]);
        }
    }
}

std::string highlight(const std::string &A, const std::string &B, std::string C)
{
    int i = A.size(), j = B.size();
    if (!isMerged[i][j])
        return "*** NOT A MERGE ***";

    while(i > 0){
        if(isMerged[i][j] && (j == 0 || !isMerged[i][j-1])){
            C[i + j - 1] = toupper(C[i + j - 1]);
            --i;
        }
        else    --j;
    }
    return C;
}
