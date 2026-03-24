#include <iostream>
#include <vector>
#include "AgentGroup.h"
#include "SocialNetwork.h" 

using namespace std;

int main() {
    AgentGroup g11(3, -100, 50, 0.5,1);
    AgentGroup g21(1, 100, 80, 0.2,2);
    AgentGroup g31(1, -10, 0, 0.5,3);

    AgentGroup g12(3, -100, 100, 0.8,1);
    AgentGroup g22(40, -2, 1, 0.01,2);
    AgentGroup g32(4000, -2, 1, 0.01,3);

    vector<AgentGroup> RSA1 = {g11,g21,g31};
    vector<AgentGroup> RSA2 = {g12,g22,g32};

    SocialNetwork RSprueba(RSA1,80);
    SocialNetwork RS(RSA2,400);

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