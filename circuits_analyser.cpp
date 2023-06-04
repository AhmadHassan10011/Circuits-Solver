#include <bits/stdc++.h>
#include "D:\Circuits-solver\linear_algebra.cpp"
using namespace std;
vector<int>vis,super_nodes;
vector<vector<pair<int,double>>>circuit;
void get_super(int cr){
    cout<<"cr"<<cr<<'\n';
    vis[cr]=1;
    super_nodes.push_back(cr);
    for(int i=0;i<circuit[cr].size();i++){
        
    cout<<"to"<<i<<'\n';
        if(i!=cr && circuit[cr][i].first==1&&!vis[i]){
    cout<<"to'"<<i<<'\n';
            get_super(i);
        }
    }
    
}

vector<double>get_current_equation(vector<int>&nodes){
    vector<double>equation(circuit[0].size());
    for(int i=0;i<nodes.size();i++){
        for(int j=1;j<circuit.size();j++){
            if(circuit[nodes[i]][j].first==2){
                equation[nodes[i]-1]+=1/circuit[nodes[i]][j].second;
                equation[j-1]+=-1/circuit[nodes[i]][j].second;
            }
        }
    }
    return equation;

}
vector<vector<double>>get_volt_equations(vector<int>&nodes){
    vector<vector<double>>equations;
    for(int i=0;i<nodes.size();i++){
        for(int j=1;j<circuit.size();j++){
            if(circuit[nodes[i]][j].first==1){
                vector<double>equation(circuit[0].size());
                equation[nodes[i]-1]+=-1;
                equation[j-1]+=1;
                equation[circuit[0].size()-1]=circuit[nodes[i]][j].second;
                equations.push_back(equation);
            }
        }
    }
    return equations;

}

vector<double> solveCircuit(vector<vector<pair<int,double>>>comps,int n){
    circuit=comps;
    vis=vector<int>(n+5);
    vector<vector<double> >matrix;
    vector<double>ground_equation(circuit[0].size());
    ground_equation[0]=1;
    matrix.push_back(ground_equation);///ground at node 1
    for(int i=1;i<=n;i++){
        if(!vis[i]){
        super_nodes=vector<int>();
        cout<<"getting super\n";
        get_super(i);
        cout<<"gor super\n";
        for(int j=0;j<super_nodes.size();j++)cout<<super_nodes[j]<<' ';
        cout<<'\n';

        vector<double>equation=get_current_equation(super_nodes);
        matrix.push_back(equation);
        cout<<"gor current equation\n";
        for(int j=0;j<equation.size();j++)cout<<equation[j]<<' ';
        cout<<'\n';
        vector<vector<double>>equations=get_volt_equations(super_nodes);
        matrix.insert(matrix.end(),equations.begin(),equations.end());
        cout<<"gor volt equations\n";
        for(int j=0;j<equations.size();j++){
            for(int k=0;k<equations[j].size();k++){
                cout<<equations[j][k]<<' ';
            }
            cout<<'\n';
        }
        cout<<'\n';

        }


    }

    cout<<"Matrix:"<<'\n';
    for(int i=0;i<matrix.size();i++){
        for(int j=0;j<matrix[i].size();j++)cout<<matrix[i][j]<<' ';
        cout<<'\n';
    }
    solveMatrix(matrix);
    cout<<"Matrix:"<<'\n';
    for(int i=0;i<matrix.size();i++){
        for(int j=0;j<matrix[i].size();j++)cout<<matrix[i][j]<<' ';
        cout<<'\n';
    }
    vector<double>answer(n);
    for(int i=0;i<matrix.size();i++){
        int pivot=get_pivot(matrix[i]);
        if(pivot==matrix[i].size())continue;
        answer[pivot]=matrix[i][n];
    }
    return answer;
} 

void testCircuit(){
    vector<vector<pair<int,double>>>  comps{{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
                                            {{0,0},{0,0},{1,5},{2,1},{0,0},{2,1}},
                                            {{0,0},{1,-5},{0,0},{2,1},{0,0},{0,0}},
                                            {{0,0},{2,1},{2,1},{0,0},{2,1},{0,0}},
                                            {{0,0},{0,0},{0,0},{2,1},{0,0},{1,-5}},
                                            {{0,0},{2,1},{0,0},{0,0},{1,5},{0,0}}
                                            };
    cout<<"solving..\n";
    vector<double>answer=solveCircuit(comps,5);
    cout<<"solved\n";
    for(int i=0;i<answer.size();i++)cout<<answer[i]<<' ';
}