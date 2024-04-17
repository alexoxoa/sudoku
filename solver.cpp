#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>
#include <unordered_set>

using namespace std;

typedef pair<int, int> pii;
typedef pair<string, pii> spii;

vector<vector<int>> grid;

vector<spii> createX(int N, int R, int C) {
    vector<spii> X;
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            X.push_back(make_pair("rc", make_pair(r, c)));
        }
    }
    for (int r = 0; r < N; r++) {
        for (int n = 1; n <= N; n++) {
            X.push_back(make_pair("rn", make_pair(r, n)));
        }
    }
    for (int c = 0; c < N; c++) {
        for (int n = 1; n <= N; n++) {
            X.push_back(make_pair("cn", make_pair(c, n)));
        }
    }
    for (int r = 0; r < N; r += R) {
        for (int c = 0; c < N; c += C) {
            for (int n = 1; n <= N; n++) {
                X.push_back(make_pair("bn", make_pair(r / R * R + c / C, n)));
            }
        }
    }
    return X;
}

unordered_map<pii, vector<spii>> createY(int N, int R, int C) {
    unordered_map<pii, vector<spii>> Y;

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            for (int n = 1; n <= N; n++) {
                int b = (r / R) * R + (c / C); // Box number

                vector<spii> neighbors;
                neighbors.push_back(make_pair("rc", make_pair(r, c)));
                neighbors.push_back(make_pair("rn", make_pair(r, n)));
                neighbors.push_back(make_pair("cn", make_pair(c, n)));
                neighbors.push_back(make_pair("bn", make_pair(b, n)));

                pii key = make_pair(r, c);
                Y[key] = neighbors;
            }
        }
    }

    return Y; // возвращаем созданный unordered_map
}

unordered_map<string, vector<pii>> createExactCover(vector<spii>& X, unordered_map<pii, vector<spii>>& Y) {
    unordered_map<string, vector<pii>> exactCover;
    for (const auto& row : Y) {
        for (const auto& col : row.second) {
            exactCover[col.first].push_back(row.first);
        }
    }
    return exactCover;
}

vector<unordered_set<int>> select(vector<unordered_set<int>>& X, vector<unordered_set<int>>& Y, int r) {
    vector<unordered_set<int>> cols;
    for (int j : Y[r]) {
        for (int i : X[j]) {
            for (auto it = Y[i].begin(); it != Y[i].end(); ) {
                if (*it != j) {
                    it = Y[i].erase(it);
                }
                else {
                    ++it;
                }
            }
        }
        cols.push_back(move(X[j]));
        X[j].clear();
    }
    return cols;
}



void deselect(unordered_map<string, vector<pii>>& X, unordered_map<pii, vector<spii>>& Y, pii r, vector<vector<pii>>& cols) {
    for (auto it = Y[r].rbegin(); it != Y[r].rend(); ++it) {
        X[it->first] = cols.back();
        for (const auto& i : X[it->first]) {
            for (const auto& k : Y[i]) {
                if (k != *it) {
                    X[k.first].push_back(i);
                }
            }
        }
        cols.pop_back();
    }
}

vector<vector<int>> solve(unordered_map<int, unordered_set<int>>& X, unordered_map<int, unordered_set<int>>& Y, vector<int>& solution) {
    if (X.empty()) {
        return { solution };
    }
    else {
        int c = X.begin()->first;
        vector<vector<int>> result;
        for (int r : X[c]) {
            solution.push_back(r);
            vector<unordered_set<int>> cols = select(X, Y, r);
            vector<vector<int>> subResult = solve(X, Y, solution);
            result.insert(result.end(), subResult.begin(), subResult.end());
            deselect(X, Y, r, cols);
            solution.pop_back();
        }
        return result;
    }
}

vector<unordered_set<int>> select(unordered_map<int, unordered_set<int>>& X, unordered_map<int, unordered_set<int>>& Y, int r) {
    vector<unordered_set<int>> cols;
    for (int j : Y[r]) {
        for (int i : X[j]) {
            for (int k : Y[i]) {
                if (k != j) {
                    X[k].erase(i);
                }
            }
        }
        cols.push_back(move(X[j]));
        X.erase(j);
    }
    return cols;
}

void deselect(unordered_map<int, unordered_set<int>>& X, unordered_map<int, unordered_set<int>>& Y, int r, const vector<unordered_set<int>>& cols) {
    int j = 0;
    for (int j : Y[r]) {
        X[j] = cols[j];
        for (int i : X[j]) {
            for (int k : Y[i]) {
                if (k != j) {
                    X[k].insert(i);
                }
            }
        }
    }
}

vector<vector<int>> solveSudoku(int R, int C, vector<vector<int>>& grid) {
    int N = R * C;
    auto X = createX(N, R, C);
    auto Y = createY(N, R, C);
    auto exactCover = createExactCover(X, Y);
    unordered_map<string, vector<pii>> XCopy = X;
    vector<vector<int>> solution;
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            int n = grid[r][c];
            if (n) {
                select(X, Y, make_pair("rc", make_pair(r, c, n)), solution);
            }
        }
    }
    solve(X, Y, solution);
    for (const auto& s : solution) {
        grid[s[0]][s[1]] = s[2];
    }
    return grid;
}
//
//int main() {
//    vector<vector<int>> grid = {
//        {5, 3, 0, 0, 7, 0, 0, 0, 0},
//        {6, 0, 0, 1, 9, 5, 0, 0, 0},
//        {0, 9, 8, 0, 0, 0, 0, 6, 0},
//        {8, 0, 0, 0, 6, 0, 0, 0, 3},
//        {4, 0, 0, 8, 0, 3, 0, 0, 1},
//        {7, 0, 0, 0, 2, 0, 0, 0, 6},
//        {0, 6, 0, 0, 0, 0, 2, 8, 0},
//        {0, 0, 0, 4, 1, 9, 0, 0, 5},
//        {0, 0, 0, 0, 8, 0, 0, 7, 9}
//    };
//    int R = 3;
//    int C = 3;
//    solveSudoku(R, C, grid);
//    for (const auto& row : grid) {
//        for (const auto& num : row) {
//            cout << num << " ";
//        }
//        cout << endl;
//    }
//    return 0;
//}
//
//




#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <map>

using namespace std;

typedef pair<int, int> pii;
typedef pair<string, pii> spii;

vector<vector<int>> grid;

vector<spii> createX(int N, int R, int C) {
    vector<spii> X;
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            X.push_back(make_pair("rc", make_pair(r, c)));
        }
    }
    for (int r = 0; r < N; r++) {
        for (int n = 1; n <= N; n++) {
            X.push_back(make_pair("rn", make_pair(r, n)));
        }
    }
    for (int c = 0; c < N; c++) {
        for (int n = 1; n <= N; n++) {
            X.push_back(make_pair("cn", make_pair(c, n)));
        }
    }
    for (int r = 0; r < N; r += R) {
        for (int c = 0; c < N; c += C) {
            for (int n = 1; n <= N; n++) {
                X.push_back(make_pair("bn", make_pair(r / R * R + c / C, n)));
            }
        }
    }
    return X;
}

unordered_map<pii, vector<spii>> createY(int N, int R, int C) {
    unordered_map<pii, vector<spii>> Y;

    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            for (int n = 1; n <= N; n++) {
                int b = (r / R) * R + (c / C); // Box number

                vector<spii> neighbors;
                neighbors.push_back(make_pair("rc", make_pair(r, c)));
                neighbors.push_back(make_pair("rn", make_pair(r, n)));
                neighbors.push_back(make_pair("cn", make_pair(c, n)));
                neighbors.push_back(make_pair("bn", make_pair(b, n)));

                pii key = make_pair(r, c);
                Y[key] = neighbors;
            }
        }
    }

    return Y; // возвращаем созданный unordered_map
}

unordered_map<string, vector<pii>> createExactCover(vector<spii>& X, unordered_map<pii, vector<spii>>& Y) {
    unordered_map<string, vector<pii>> exactCover;
    for (const auto& row : Y) {
        for (const auto& col : row.second) {
            exactCover[col.first].push_back(row.first);
        }
    }
    return exactCover;
}

void select(unordered_map<string, vector<pii>>& X, unordered_map<pii, vector<spii>>& Y, pii r, vector<vector<pii>>& solution) {
    vector<pii> cols;
    for (auto it = Y[r].begin(); it != Y[r].end(); ++it) {
        for (auto itr = X[it->first].begin(); itr != X[it->first].end(); ++itr) {
            for (auto itk = Y[*itr].begin(); itk != Y[*itr].end(); ++itk) {
                if (*itk != *it) {
                    X[itk->first].erase(itr);
                }
            }
        }
        cols.push_back(*it);
        X.erase(it->first);
    }
    solution.push_back(cols);
}

void deselect(unordered_map<string, vector<pii>>& X, unordered_map<pii, vector<spii>>& Y, pii r, vector<vector<pii>>& cols) {
    for (auto it = Y[r].rbegin(); it != Y[r].rend(); ++it) {
        X[it->first] = cols.back();
        for (const auto& i : X[it->first]) {
            for (const auto& k : Y[i]) {
                if (k != *it) {
                    X[k.first].insert(i);
                }
            }
        }
        cols.pop_back();
    }
}

bool solve(unordered_map<string, vector<pii>>& X, unordered_map<pii, vector<spii>>& Y, vector<vector<int>>& solution) {
    if (X.empty()) {
        return true;
    }
    auto comp = [](const auto& a, const auto& b) {
        return a.second.size() < b.second.size();
        };
    auto it = min_element(X.begin(), X.end(), comp);
    string c = it->first;
    for (const auto& r : it->second) {
        solution.push_back({ r.first.first, r.first.second, stoi(r.second.first) });
        vector<vector<pii>> cols;
        select(X, Y, r, cols);
        if (solve(X, Y, solution)) {
            return true;
        }
        deselect(X, Y, r, cols);
        solution.pop_back();
    }
    return false;
}

vector<vector<int>> solveSudoku(int R, int C, vector<vector<int>>& grid) {
    int N = R * C;
    auto X = createX(N, R, C);
    auto Y = createY(N, R, C);
    auto exactCover = createExactCover(X, Y);
    unordered_map<string, vector<pii>> XCopy = X;
    vector<vector<int>> solution;
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            int n = grid[r][c];
            if (n) {
                select(XCopy, Y, make_pair("rc", make_pair(r, c, n)), solution);
            }
        }
    }
    solve(XCopy, Y, solution);
    for (const auto& s : solution) {
        grid[s[0]][s[1]] = s[2];
    }
    return grid;
}

//int main() {
//    vector<vector<int>> grid = {
//        {5, 3, 0, 0, 7, 0, 0, 0, 0},
//        {6, 0, 0, 1, 9, 5, 0, 0, 0},
//        {0, 9, 8, 0, 0, 0, 0, 6, 0},
//        {8, 0, 0, 0, 6, 0, 0, 0, 3},
//        {4, 0, 0, 8, 0, 3, 0, 0, 1},
//        {7, 0, 0, 0, 2, 0, 0, 0, 6},
//        {0, 6, 0, 0, 0, 0, 2, 8, 0},
//        {0, 0, 0, 4, 1, 9, 0, 0, 5},
//        {0, 0, 0, 0, 8, 0, 0, 7, 9}
//    };
//    int R = 3;
//    int C = 3;
//    grid = solveSudoku(R, C, grid);
//    for (const auto& row : grid) {
//        for (const auto& num : row) {
//            cout << num << " ";
//        }
//        cout << endl;
//    }
//    return 0;
//}
