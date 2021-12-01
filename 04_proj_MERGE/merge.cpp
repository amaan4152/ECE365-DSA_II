#include <iostream>
#include <stdio.h>
#include <string.h>

#define MAX 1000
static bool isMerged[MAX + 1][MAX + 1];

void merge(const std::string &A, const std::string &B, const std::string &C)
{
    /* Fail cases */
    if ((A.size() + B.size()) != C.size())  
        return;
    else if (!(A.back() == C.back() && B.back() == C.back()))
        return;

    /* Iniitialize to all false */
    memset(isMerged, 0, sizeof(isMerged));

    /* Check if merge valid */
    for (int i = 0; i <= MAX; ++i){
        for (int j = 0; j <= MAX; ++j){
            if (i == 0 && j == 0)   
                isMerged[i][j] = true;

            else if (i == 0){
                if (B[j - 1] == C[j - 1])
                    isMerged[i][j] = isMerged[i][j - 1];
            }
            else if (j == 0){
                if (A[i - 1] == C[j - 1])
                    isMerged[i][j] = isMerged[i - 1][j];
            }
            else if (A[i - 1] == C[i + j - 1] && B[j - 1] != C[i + j -1])
                isMerged[i][j] = isMerged[i - 1][j];

            else if (A[i - 1] != C[i + j - 1] && B[j - 1] != C[i + j -1])
                isMerged[i][j] = isMerged[i][j - 1];

            else if (A[i - 1] == C[i + j - 1] && B[j - 1] == C[i + j -1])
                isMerged[i][j] = (isMerged[i - 1][j] || isMerged[i][j - 1]);
        }
    }
}

std::string highlight(std::string &C)
{
    int i = MAX, j = MAX;
    if (!isMerged[MAX][MAX])
        return "*** NOT A MERGE ***";
    else{
        if(isMerged[i][j] && (j == 0 || !isMerged[i][j-1])){
            C[i + j - 1] = toupper(C[i + j - 1]);
            --i;
        }
        --j;
    }
}
