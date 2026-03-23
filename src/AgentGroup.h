#pragma once
#include <string>
#include <tuple>

using namespace std;

class AgentGroup
{
private:
    tuple<int, int, int, int> group;

public:
    AgentGroup(int, int, int, int);
    void showGroup();
    int getConflict();
    int getEffort(int);
};