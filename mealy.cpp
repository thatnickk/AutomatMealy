#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>


//Github: https://github.com/thatnickk/AutomatMealy

using namespace std;

ifstream fin("mealy.in");
ofstream fout("mealy.out");

struct muchie{
    string lit;
    string output;
};

int main(){
    int nodes, sides, noOfTests, tempNode1, tempNode2, initialState, noOfFinalStates, currentNode;
    set<int> finalStates;
    string currentTest;
    fin>>nodes;
    fin>>sides;

    vector<vector<muchie>> matrix(nodes, vector<muchie>(nodes));

    for(int i = 0; i < nodes; i++) {
        for(int j = 0; j < nodes; j++){
            matrix[i][j].lit = '-';
            matrix[i][j].output = '-';
        }
    }

    for(int i = 0; i < sides; i++) {
        fin >> tempNode1;
        fin >> tempNode2;
        if(matrix[tempNode1][tempNode2].lit == "-" && matrix[tempNode1][tempNode2].output == "-"){
            fin >> matrix[tempNode1][tempNode2].lit;
            fin >> matrix[tempNode1][tempNode2].output;
        }
        else{
            char temp1, temp2;
            fin >> temp1;
            matrix[tempNode1][tempNode2].lit += temp1;
            fin >> temp2;
            matrix[tempNode1][tempNode2].output += temp2;
        }
    }

    for(int i = 0; i < nodes; i++) {
        for(int j = 0; j < nodes; j++){
            fout << matrix[i][j].lit << "," << matrix[i][j].output << "    ";
        }
        fout << '\n';
    }
    fin >> initialState;
    fin >> noOfFinalStates;
    int tempstate;
    for(int i = 0; i < noOfFinalStates; i++) {
        fin >> tempstate;
        finalStates.insert(tempstate);
    }
    fin >> noOfTests;
    for(int i = 0; i < noOfTests; i++) {
        fin >> currentTest;
        currentNode = initialState;
        string currentPath = to_string(initialState) + ' ';
        string currentOutput;
        while(currentTest.length()>0) {
            bool found = false;
            for(int j = 0; j < nodes; j++){
                if(matrix[currentNode][j].lit.find(currentTest[0])!=string::npos){
                    currentOutput += matrix[currentNode][j].output[matrix[currentNode][j].lit.find(currentTest[0])];
                    currentNode = j;
                    found = true;
                    currentPath += to_string(currentNode) + ' ';
                    break;
                }
            }
            if(found) {
                currentTest = currentTest.substr(1, currentTest.length() - 1);
            }
            else break;
        }
        if(finalStates.find(currentNode) != finalStates.end()) {
            fout << "ye" << '\n';
            fout << currentOutput << '\n';
            fout << "Traseu: " << currentPath << '\n';
        }
        else
            fout << "nay" << '\n';
    }
    return 0;
}