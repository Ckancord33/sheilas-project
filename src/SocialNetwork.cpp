#include "SocialNetwork.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

SocialNetwork::SocialNetwork(const std::vector<AgentGroup>& v, int R_max) 
{
    SAG = v;
    this->R_max = R_max;
}


vector<vector<int>> getAgentsSet(const std::vector<AgentGroup>& v){
    vector<vector<int>> agentSet(v.size());
    AgentGroup actualGroup;

    for (int i = 0; i < v.size(); i++){
        actualGroup = v[i];
        agentSet[i] = vector<int>(actualGroup.getQuantity() + 1);
        iota(agentSet[i].begin(), agentSet[i].end(), 0);
    };

    return agentSet;
}

void productoRecursivo(const vector<vector<int>>& conjuntos, 
                       vector<vector<int>>& resultado, 
                       vector<int>& combinacionActual, 
                       int indiceConjunto) {
    
    // Caso base: Si el índice llegó al final, guardamos la combinación completa
    if (indiceConjunto == conjuntos.size()) {
        resultado.push_back(combinacionActual);
        return;
    }

    // Caso recursivo: Iteramos sobre el conjunto actual
    for (int elemento : conjuntos[indiceConjunto]) {
        // 1. Añadimos el elemento a la ruta actual
        combinacionActual.push_back(elemento);
        
        // 2. Llamada recursiva para el siguiente nivel (siguiente conjunto)
        productoRecursivo(conjuntos, resultado, combinacionActual, indiceConjunto + 1);
        
        // 3. Quitamos el elemento para probar con el siguiente del mismo conjunto
        combinacionActual.pop_back();
    }
}

vector<vector<int>> calcularProductoCartesiano(const vector<vector<int>>& conjuntos) {
    vector<vector<int>> resultado;
    vector<int> combinacionActual;
    
    if (conjuntos.empty()) return resultado;

    productoRecursivo(conjuntos, resultado, combinacionActual, 0);
    return resultado;
}


vector<int> getEffort (const std::vector<AgentGroup>& v, vector<vector<int>> strategies){

    vector<int> effortVec(strategies.size());
    
    int sumEffortAct = 0;

    for (int i = 0; i < strategies.size();i++){
        sumEffortAct = 0;
        for (int j = 0; j < strategies[i].size() && j < v.size(); j++) {
            sumEffortAct += v[j].getEffort(strategies[i][j]);
        }
        effortVec[i] = sumEffortAct;
    }

    return effortVec;
}

tuple<int,double> ciMinimum(const std::vector<AgentGroup>& v, const vector<int>& effortVec, int Rmax, const vector<vector<int>>& strategies,bool debug) {
    
    int indexBestStrategy = -1; 
    double minConflict = 0;
    bool primeroEncontrado = false;

    for (int i = 0; i < strategies.size(); i++) {
        
        if (effortVec[i] <= Rmax) {
        
            double conflictAct = 0;
            for (int j = 0; j < v.size(); j++) {
                conflictAct += v[j].getConflict(v[j].getQuantity() - strategies[i][j]);
            }
            conflictAct /= v.size();

            if (debug){
                cout << "Conflicto de la iteracion: " << i << " " << conflictAct << endl;
            }
            

            if (!primeroEncontrado || conflictAct < minConflict) {
                minConflict = conflictAct;
                indexBestStrategy = i;
                primeroEncontrado = true;
            }
        }
    }

    return {indexBestStrategy,minConflict};
}


vector<int> SocialNetwork::micBruteForce(bool debug = false){
    vector<vector<int>> agentsSet = getAgentsSet(SAG);
    vector<vector<int>> strategies = calcularProductoCartesiano(agentsSet);
    vector<int> effortVec = getEffort(SAG,strategies);

    tuple<int,double> indexMaxEffort = ciMinimum(SAG,effortVec,R_max,strategies,false);

    if (debug){
        cout << "Esfuerzo de la estrategia: " << effortVec[get<0>(indexMaxEffort)] << endl;
        cout << "Conflicto interno de la estrategia: " << get<1>(indexMaxEffort) << endl;
    }

    return strategies[get<0>(indexMaxEffort)];
}



vector<AgentGroup> sortRS (const std::vector<AgentGroup>& v){
    vector<AgentGroup> sortedV = v;

    sort(sortedV.begin(), sortedV.end(), [](const AgentGroup& a, const AgentGroup& b) {

        double ciA = a.getConflict(a.getQuantity()) / a.getObstinacy();
        double ciB = b.getConflict(b.getQuantity()) / b.getObstinacy();

        return ciA > ciB; 
    });

    return sortedV;
    
}

int getAmountpMaximumEffort (const AgentGroup& v, int Rmax){
    int maxQuantity = 0;
    for (int i = 0 ; i <= v.getQuantity(); i++){
        if (v.getEffort(i) <= Rmax){
            maxQuantity = i;
        }
    }
    return maxQuantity;
}

void showCIandE (const std::vector<AgentGroup>& v , vector<int> strategie){
    int newCI = 0;
    double conflictAct = 0;
    int efforAct = 0; 

    for (int j = 0; j < v.size(); j++) {
        conflictAct += v[j].getConflict(v[j].getQuantity() - strategie[j]);
        efforAct += v[j].getEffort(strategie[j]);
    }
    conflictAct /= v.size();

    cout << "Esfuerzo de la estrategia: " << efforAct << endl;
    cout << "Conflicto interno de la estrategia voraz: " << conflictAct << endl;
}

int getIndex(const std::vector<AgentGroup>& v, const AgentGroup& valor) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i].getIndex() == valor.getIndex()) {
            return i;
        }
    }
    return -1;
}

vector<int> SocialNetwork::micGreedy(bool debug){
    vector<AgentGroup> sortVectRS = sortRS(SAG);
    vector<int> strategie(sortVectRS.size());
    int newEffort = 0;
    int maximumEffort;
    int indexAgentGroup;

    for (int i = 0 ; i < sortVectRS.size(); i++){
        maximumEffort = getAmountpMaximumEffort(sortVectRS[i],R_max - newEffort);
        indexAgentGroup = getIndex(SAG,sortVectRS[i]);
        strategie[indexAgentGroup] = maximumEffort;
        newEffort += sortVectRS[i].getEffort(maximumEffort);
    }

    if(debug){
        showCIandE(sortVectRS,strategie);
    }

    return strategie;
}