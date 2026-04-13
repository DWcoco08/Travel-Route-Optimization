#include<iostream>
#include<fstream>
#include<cstring>
#include<climits>
#include<ctime>
using namespace std;

#define MAX 20
#define INF 1e9

int n;
int C[MAX][MAX];
int dp[1 << MAX][MAX];
int bestPath[MAX];
int currentPath[MAX];
bool visited[MAX];
int minCost;

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

// ========== BITMASK DP ==========
int dpBitmask() {
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = INF;
        }
    }
    
    dp[1][0] = 0;
    
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i)) || dp[mask][i] >= INF) continue;
            
            for (int j = 0; j < n; j++) {
                if (!(mask & (1 << j))) {
                    int newMask = mask | (1 << j);
                    dp[newMask][j] = min(dp[newMask][j], dp[mask][i] + C[i][j]);
                }
            }
        }
    }
    
    int fullMask = (1 << n) - 1;
    int result = INF;
    
    for (int i = 1; i < n; i++) {
        result = min(result, dp[fullMask][i] + C[i][0]);
    }
    
    memset(bestPath, 0, sizeof(bestPath));
    for (int i = 1; i < n; i++) {
        bestPath[i] = i;
    }
    
    return result;
}

// ========== GREEDY ==========
int greedy() {
    memset(visited, false, sizeof(visited));
    memset(bestPath, 0, sizeof(bestPath));
    
    visited[0] = true;
    int current = 0;
    int totalCost = 0;
    
    for (int i = 1; i < n; i++) {
        int nextCity = -1;
        int minNext = INF;
        
        for (int j = 0; j < n; j++) {
            if (!visited[j] && C[current][j] < minNext) {
                minNext = C[current][j];
                nextCity = j;
            }
        }
        
        if (nextCity != -1) {
            visited[nextCity] = true;
            bestPath[i] = nextCity;
            totalCost += minNext;
            current = nextCity;
        }
    }
    
    totalCost += C[current][0];
    return totalCost;
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

        out << "\n========== TEST CASE " << test << " (n=" << n << ") ==========" << endl;

        // Backtracking
        clock_t start = clock();
        int btCost = backtracking();
        clock_t end = clock();
        long long btTime = (long long)((end - start) * 1000 / CLOCKS_PER_SEC);
        
        out << "====BACKTRACKING====" << endl;
        out << "Chi phi toi thieu: " << btCost << endl;
        out << "Lo trinh: ";
        printPath(out);
        out << "Thoi gian: " << btTime << " ms" << endl;

        // DP Bitmask
        start = clock();
        int dpCost = dpBitmask();
        end = clock();
        long long dpTime = (long long)((end - start) * 1000 / CLOCKS_PER_SEC);
        
        out << "====BITMASK DP====" << endl;
        out << "Chi phi toi thieu: " << dpCost << endl;
        out << "Lo trinh: ";
        printPath(out);
        out << "Thoi gian: " << dpTime << " ms" << endl;

        // Greedy
        start = clock();
        int greedyCost = greedy();
        end = clock();
        long long greedyTime = (long long)((end - start) * 1000 / CLOCKS_PER_SEC);
        
        out << "====GREEDY====" << endl;
        out << "Chi phi: " << greedyCost << endl;
        out << "Lo trinh: ";
        printPath(out);
        out << "Thoi gian: " << greedyTime << " ms" << endl;

        cout << "\n========== TEST CASE " << test << " (n=" << n << ") ==========" << endl;
        cout << "BT: " << btCost << " | DP: " << dpCost << " | Greedy: " << greedyCost << endl;
    }

    in.close();
    out.close();
    cout << "\n✓ Xong!" << endl;
    return 0;
}
