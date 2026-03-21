#pragma once
#include <string>
#include <tuple>

class AgentGroup{
    private:
        std::tuple<int, int, int, int> group;

    public:
        AgentGroup(int, int, int, int);
        void showGroup();

};