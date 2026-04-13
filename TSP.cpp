#include<iostream>
#include<fstream>
#include<cstring>
#include<climits>
#include<ctime>
using namespace std;

#define MAX 20

int n;
int C[MAX][MAX];
int minCost;
int bestPath[MAX];
int currentPath[MAX];
bool visited[MAX];

// ========== BACKTRACKING ==========
void dfs(int current, int costSoFar, int count) {
    if (costSoFar >= minCost) return;
    
    if (count == n) {
        int totalCost = costSoFar + C[current][0];
        if (totalCost < minCost) {
            minCost = totalCost;
            memcpy(bestPath, currentPath, sizeof(currentPath));
        }
        return;
    }
    
    for (int next = 1; next < n; next++) {
        if (!visited[next]) {
            visited[next] = true;
            currentPath[count] = next;
            dfs(next, costSoFar + C[current][next], count + 1);
            visited[next] = false;
        }
    }
}

int backtracking() {
    minCost = INT_MAX;
    memset(visited, false, sizeof(visited));
    memset(bestPath, 0, sizeof(bestPath));
    visited[0] = true;
    currentPath[0] = 0;
    dfs(0, 0, 1);
    return minCost;
}

void printPath(ofstream &out) {
    out << "0 ";
    for (int i = 1; i < n; i++) {
        out << bestPath[i] << " ";
    }
    out << "0" << endl;
}

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt", ios::app);
    
    if (!in.is_open() || !out.is_open()) {
        cout << "Loi mo file!" << endl;
        return 1;
    }

    int numTests;
    in >> numTests;

    for (int test = 1; test <= numTests; test++) {
        in >> n;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                in >> C[i][j];
            }
        }

        clock_t start = clock();
        int cost = backtracking();
        clock_t end = clock();
        long long timeMs = (long long)((end - start) * 1000 / CLOCKS_PER_SEC);

        out << "\n========== TEST CASE " << test << " (n=" << n << ") ==========" << endl;
        out << "====BACKTRACKING====" << endl;
        out << "Chi phi toi thieu: " << cost << endl;
        out << "Lo trinh: ";
        printPath(out);
        out << "Thoi gian: " << timeMs << " ms" << endl;

        cout << "\n========== TEST CASE " << test << " (n=" << n << ") ==========" << endl;
        cout << "====BACKTRACKING====" << endl;
        cout << "Chi phi toi thieu: " << cost << endl;
        cout << "Lo trinh: 0 ";
        for (int i = 1; i < n; i++) cout << bestPath[i] << " ";
        cout << "0" << endl;
        cout << "Thoi gian: " << timeMs << " ms" << endl;
    }

    in.close();
    out.close();
    cout << "\n✓ Xong!" << endl;
    return 0;
}
