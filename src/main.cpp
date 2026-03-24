#include <iostream>
#include <vector>
#include "AgentGroup.h"
#include "SocialNetwork.h" 

using namespace std;

int main() {
    AgentGroup g1(3, -100, 50, 0.5,1);
    AgentGroup g2(1, 100, 80, 0.1,2);
    AgentGroup g3(1, -10, 0, 0.5,3);

    vector<AgentGroup> RSA = {g1,g2,g3};

    SocialNetwork RS(RSA,80);

    cout<< "Solución Ingenua" << endl;

    vector<int> solutionBruteForce = RS.micBruteForce(true);

    for (int i = 0; i < solutionBruteForce.size(); i++) {
        cout << solutionBruteForce[i] << "\t" << endl;
    }

    cout<< "\nSolución Voraz" << endl;

    vector<int> solutionGreddy = RS.micGreedy(true);

     for (int i = 0; i < solutionGreddy.size(); i++) {
        cout << solutionGreddy[i] << "\t" << endl;
    } 

    return 0;
}