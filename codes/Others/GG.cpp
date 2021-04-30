#pragma GCC optimize("O2")
//
// Created by KID on 2021/4/20.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> graph;
vector<int> xMatch;
vector<int> yMatch;
vector<int> visited;

// int next(int x, int y)
// {
//     int index;
//     for (index = 0; index < graph[x].size(); index++)
//     {
//         if(graph[x][index] == y)
//             break;
//     }
//     if(index + 1 >= graph[x].size())
//         return -1;
//     else return graph[x][index + 1];
// }

bool match(int x, int y)
{
    if(visited[y])
        return false;
    visited[y] = 1;
    if (x == -1 || y == -1)
        return false;
    if(yMatch[y] == -1) {
        xMatch[x] = y;
        yMatch[y] = x;
        return true;
    }
    int from = yMatch[y];
    for(auto to : graph[from])
    {
        if(match(from, to)){
            xMatch[x] = y;
            yMatch[y] = x;
            return true;
        }
    }
    return false;
}


int main() {
    int X, Y;
    cin >> X >> Y;
    xMatch.resize(X, -1);
    yMatch.resize(Y + 1, -1);
    graph.resize(X);
    for (int i = 0; i < X; i++)
    {
        int size;
        cin >> size;
        graph[i].resize(size);
        for(int j = 0; j < size; j++)
        {
            cin >> graph[i][j];
        }

    }
    for(int i = 0; i < graph.size(); i++)
    {
        visited.clear();
        visited.resize(Y + 1, 0);
        for(int j : graph[i])
        {
            if (match(i,j)) break;
        }
    }
    int count = 0;
    for(int matched : xMatch){
        if(matched != -1)
            count++;
    }
    cout << count;
    return 0;
}