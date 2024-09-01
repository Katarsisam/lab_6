#include <vector>
#include <iostream>
#include <stdio.h>
#include <random>
#include <ctime>
#include <algorithm>
#include <stack>
using namespace std;


vector<vector<int>>  Task_1( int n);
vector<vector<int>> Task_2(int n, int m);
int Task_3(int X,vector<vector<int>> &vec, int n, int m);
void print_vector(vector<vector<int>> vec);
vector<vector<int>> Generator(int n, int m);

int main(){
    int N, n, m;
    int X = 1;
    int Summ = 1;
    int fSumm = 0;
    vector<vector<int>> vec;
    scanf("%d",&N);
    switch (N)
    {
    case 1:
        scanf("%d",&n);
        print_vector(Task_1(n));
        break;
    case 2:
        scanf("%d%d",&n,&m);
        print_vector(Task_2(n,m));
        break;
    case 3:
        scanf("%d%d",&n,&m);
        vec = Generator(n,m);
        print_vector(vec);
        do{          
            Summ = Task_3(X,vec,n,m);
            fSumm += Summ;
            printf("%d matrixes of %d size\n",Summ,X);
            X++;
        }while(Summ>0);
        printf("%d matrixes\n",fSumm);
        print_vector(vec);
        
        
           
        break;   
    default:
        break;
    }
    
    
    return 0;
}

vector<vector<int>> Task_1(int n){
    vector<vector<int>> vec(n,vector<int>(n));
    srand(time(0));
    int cass;
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<n; j++){

        cass = rand()%101-50;
        if((j+1)%2==0)
            while (abs(cass)<=10)
            {
                cass = rand()%101-50;
            }
            
           vec[i][j] =  cass;}

           }
           return vec;
}
vector<vector<int>> Task_2(int n, int m){
    vector<vector<int>> vec(n,vector<int>(m));
    
    vector<int> vecX(m/2);
    int cass;
    int counter;
    srand(time(0));
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<m; j++){

        cass = rand()%201-100;
            
           vec[i][j] =  cass;
           printf("%4d|", vec[i][j]);
           }
           printf("\n");
    }
    printf("\n");

    for(int i = 0; i<m; i++) {
        for(int j = 0; j<n; j++){
            if(vec[j][i]>0)
            counter++;
            else if (vec[j][i]<0)
            counter--;
            }
            
            if(counter>0){
                for(int j = 0; j<n/2; j++)
                    vecX[j] = vec[j][i];
                sort(vecX.begin(),vecX.end());
                for(int j = 0; j<n/2; j++)
                    vec[j][i] = vecX[j];}
            else if (counter<0)
                for(int j = 0; j<n; j++)
                    vec[j][i] = vec[j][i]*vec[j][i];
            else if (counter == 0)
                for(int j = 0; j<n; j++){
                    vec[j][i]=0;}
        counter = 0;

    }
           return vec;
}

int Task_3(int X, vector<vector<int>>& vec, int n, int m){
    int counter = 0;
   

    for(int i = 0; i<n; i++) 
        for(int j = 0; j<m; j++){
        if(i!=0&&j!=0&&vec[i][j]!=0)
            vec[i][j] = min (min(vec[i][j],vec[i-1][j-1]),min(vec[i][j-1],vec[i-1][j])) + 1;
        if(vec[i][j]==X)
        {
        counter++;
        }
      
    }
    return counter;
}


void print_vector(vector<vector<int>> vec) {
    for (vector<vector<int>>::iterator it = vec.begin(); it != vec.end(); ++it){
        for (auto itX = (*it).begin(); itX != (*it).end(); ++itX)
            printf("%5d|", *itX);
        printf("\n");
        }
}


vector<vector<int>> Generator(int n, int m){
    vector<vector<int>> vecX(n,vector<int>(m));
    int cass;
    srand(time(0));
    for(int i = 0; i<n; i++) {
        for(int j = 0; j<m; j++){

        cass = rand()%2;
            
           vecX[i][j] =  cass;
           //printf("%d|", vecX[i][j]);
           }
           //printf("\n");
    }
    // printf("\n");
    return vecX;
}
