#pragma once
#include <string>
#include <tuple>

using namespace std;

class AgentGroup
{
private:
    tuple<int, int, int, double>group;

public:
    AgentGroup(int, int, int, double);
    AgentGroup() = default;
    void showGroup();
    int getConflict(int) const;
    int getEffort(int) const;
    int getQuantity() const;
};