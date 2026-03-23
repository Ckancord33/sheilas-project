#pragma once
#include <string>
#include "AgentGroup.h"
#include <vector>

using namespace std;


class SocialNetwork
{
private:
    vector<AgentGroup> SAG;
    int R_max;
public:
    SocialNetwork(const std::vector<AgentGroup>& v, int R_max);

    vector<int> micBruteForce(bool);
    vector<int> micGreedy();
    vector<int> micDinamycProgramming();
    void showEffortUsed();
};