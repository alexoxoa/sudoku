//#include <iostream>
//#include <vector>
//#include <unordered_map>
//#include <algorithm>
//#include <map>
//#include <unordered_set>
//#include <utility>
//#include <cmath>
//using namespace std;
//
//typedef pair<int, int> pii;
//typedef pair<string, pii> spii;
//
//vector<vector<int>> grid;
//
//void exact_cover(const unordered_set<int>& X, unordered_map<pii, vector<spii>>& Y, unordered_map<int, unordered_set<int>>& X_new) {
//    for (const auto& x : X) {
//        X_new[x] = unordered_set<int>();
//    }
//
//    for (const auto& row : Y) {
//        int i = row.first.first;
//        for (const auto& j : row.second) {
//            X_new[j.second.first].insert(i);
//        }
//    }
//}
//
//void select(unordered_map<int, unordered_set<int>>& X, unordered_map<pii, vector<spii>>& Y, int r, unordered_set<int>& cols) {
//    for (int c : cols) {
//        for (const auto& neighbor : Y[{r, c}]) {
//            const string& type = neighbor.first;
//            const pii& pos = neighbor.second;
//            if (type == "rc") {
//                X[pos.first].erase(pos.second);
//            }
//            else if (type == "rn") {
//                X[pos.first * grid.size() + pos.second].erase(r);
//            }
//            else if (type == "cn") {
//                X[pos.second * grid.size() + pos.first].erase(r);
//            }
//            else if (type == "bn") {
//                int box_size = sqrt(grid.size());
//                int box_row = r / box_size;
//                int box_col = c / box_size;
//                int box_num = box_row * box_size + box_col;
//                X[(box_num)*grid.size() + pos.second].erase(r);
//            }
//        }
//    }
//}
//
//void deselect(unordered_map<int, unordered_set<int>>& X, unordered_map<pii, vector<spii>>& Y, int r, unordered_set<int>& cols) {
//    for (int c : cols) {
//        for (const auto& neighbor : Y[{r, c}]) {
//            const string& type = neighbor.first;
//            const pii& pos = neighbor.second;
//            if (type == "rc") {
//                X[pos.first].insert(pos.second);
//            }
//            else if (type == "rn") {
//                X[pos.first * grid.size() + pos.second].insert(r);
//            }
//            else if (type == "cn") {
//                X[pos.second * grid.size() + pos.first].insert(r);
//            }
//            else if (type == "bn") {
//                int box_size = sqrt(grid.size());
//                int box_row = r / box_size;
//                int box_col = c / box_size;
//                int box_num = box_row * box_size + box_col;
//                X[(box_num)*grid.size() + pos.second].insert(r);
//            }
//        }
//    }
//}
//
//vector<vector<int>> solve(const unordered_map<int, unordered_set<int>>& X, const unordered_map<pii, vector<spii>>& Y, vector<int>& solution) {
//    vector<vector<int>> results;
//    if (X.empty()) {
//        results.push_back(solution);
//        return results;
//    }
//    int c = X.begin()->first;
//    for (const int& r : X.at(c)) {
//        solution.push_back(r);
//        unordered_set<int> cols;
//        for (const auto& neighbor : Y.at({ r, c })) {
//            cols.insert(neighbor.second.second);
//        }
//        unordered_map<int, unordered_set<int>> X_new = X;
//        unordered_map<pii, vector<spii>> Y_new = Y;
//        select(X_new, Y_new, r, cols);
//        vector<vector<int>> subresults = solve(X_new, Y_new, solution);
//        results.insert(results.end(), subresults.begin(), subresults.end());
//        solution.pop_back();
//        deselect(X_new, Y_new, r, cols);
//    }
//    return results;
//}
//
//vector<vector<int>> solve_sudoku(const pii& size, vector<vector<int>>& grid) {
//    int R = size.first;
//    int C = size.second;
//    int N = R * C;
//    vector<pair<string, pii>> X;
//    for (int rc = 0; rc < N; rc++) {
//        for (int rn = 1; rn <= N; rn++) {
//            X.push_back({ "rc", {rc, rn} });
//        }
//    }
//    for (int rn = 0; rn < N; rn++) {
//        for (int cn = 1; cn <= N; cn++) {
//            X.push_back({ "rn", {rn, cn} });
//        }
//    }
//    for (int cn = 0; cn < N; cn++) {
//        for (int bn = 1; bn <= N; bn++) {
//            X.push_back({ "cn", {cn, bn} });
//        }
//    }
//    for (int bn = 0; bn < N; bn++) {
//        for (int bn = 1; bn <= N; bn++) {
//            X.push_back({ "bn", {bn, bn} });
//        }
//    }
//    unordered_map<pii, vector<spii>> Y;
//    for (int r = 0; r < N; r++) {
//        for (int c = 0; c < N; c++) {
//            for (int n = 1; n <= N; n++) {
//                int b = (r / R) * R + (c / C); // Box number
//                vector<spii> neighbors;
//                neighbors.push_back(make_pair("rc", make_pair(r, c)));
//                neighbors.push_back(make_pair("rn", make_pair(r, n)));
//                neighbors.push_back(make_pair("cn", make_pair(c, n)));
//                neighbors.push_back(make_pair("bn", make_pair(b, n)));
//                Y[make_pair(r, c)] = neighbors;
//            }
//        }
//    }
//    unordered_set<int> X_set;
//    for (int i = 0; i < X.size(); i++) {
//        X_set.insert(i);
//    }
//    unordered_map<int, unordered_set<int>> X_new;
//    exact_cover(X_set, Y, X_new);
//    for (int i = 0; i < grid.size(); i++) {
//        for (int j = 0; j < grid[i].size(); j++) {
//            if (grid[i][j] != 0) {
//                unordered_set<int> column = { j };
//                select(X_new, Y, i, column);
//            }
//        }
//    }
//    vector<int> empty_solution;
//    return solve(X_new, Y, empty_solution);
//}
//
//int main() {
//    pii size = make_pair(3, 3);
//    vector<vector<int>> grid = {
//        { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
//        { 6, 0, 0, 1, 9, 5, 0, 0, 0 },
//        { 0, 9, 8, 0, 0, 0, 0, 6, 0 },
//        { 8, 0, 0, 0, 6, 0, 0, 0, 3 },
//        { 4, 0, 0, 8, 0, 3, 0, 0, 1 },
//        { 7, 0, 0, 0, 2, 0, 0, 0, 6 },
//        { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
//        { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
//        { 0, 0, 0, 0, 8, 0, 0, 7, 9 }
//    };
//    vector<vector<int>> result = solve_sudoku(size, grid);
//    for (const auto& solution : result) {
//        for (auto num : solution) {
//            cout << num << " ";
//        }
//        cout << endl;
//    }
//    return 0;
//}