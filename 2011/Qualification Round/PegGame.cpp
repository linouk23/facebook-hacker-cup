#include "bits/stdc++.h"
#include "gtest/gtest.h"

using namespace std;

// Idea: https://habrahabr.ru/post/111898
class Solution {
public:
    static string pegGame(int R, int C, int K, vector<pair<int, int>> cells) {
        char EMPTY = '.', PEG = 'X', WALL = 'W';
        vector<vector<char>> board(R, vector<char> (2 * C, EMPTY));
        vector<vector<double>> probs(R, vector<double> (2 * C, 0.0));
        for (int row = 0; row < R; ++row) {
            if (row % 2) {
                for (int col = 0; col < C - 1; ++col) {
                    board[row][2 * col + 1] = PEG;
                }
                board[row][0] = WALL;
                board[row][2 * C - 2] = WALL;
            } else {
                for (int col = 0; col < C; ++col) {
                    board[row][2 * col] = PEG;
                }
            }
        }
        
        for (const auto &cell : cells) {
            int row, col;
            tie(row, col) = cell;
            board[row][2 * col + row % 2] = EMPTY;
        }
        
        probs[R - 1][2 * K + 1] = 1.0;
        
        // Start from the Bottom
        for (int row = R - 2; row >= 0; --row) {
            for (int col = 0; col < 2 * C - 1; ++col) {
                if (board[row][col] != '.') { continue; }
                if (board[row + 1][col] == PEG) {
                    if (board[row + 1][col - 1] == WALL) {
                        probs[row][col] = probs[row + 1][col + 1];
                    } else if (board[row + 1][col + 1] == WALL) {
                        probs[row][col] = probs[row + 1][col - 1];
                    } else {
                        probs[row][col] = (probs[row + 1][col + 1]
                                           + probs[row + 1][col - 1]) / 2.0;
                    }
                } else if (board[row + 1][col] == EMPTY){
                    probs[row][col] = probs[row + 1][col];
                }
            }
        }
        struct Result {
            double prob;
            int column;
        } result { -1, 0 };
        int firstRow = 0;
        for (int col = 0; col < C - 1; ++col) {
            if (probs[firstRow][2 * col + 1] > result.prob) {
                result = { probs[firstRow][2 * col + 1], col };
            }
        }
        return to_string(result.column) + " " + to_string(result.prob);
    }
    static void generateResult() {
        ios::sync_with_stdio(false);
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        int N;
        cin >> N;
        int idx = 1;
        while (N--) {
            int R, C, K, numOfPairs;
            cin >> R >> C >> K >> numOfPairs;
            vector<pair<int, int>> cells(numOfPairs);
            for (int pairIdx = 0; pairIdx < numOfPairs; ++pairIdx) {
                cin >> cells[pairIdx].first >> cells[pairIdx].second;
            }
            cout << "Case #" << idx++ << ": " << Solution::pegGame(R, C, K, cells) << '\n';
        }
    }
};

TEST(SolutionTest, Small) {
    EXPECT_EQ("0 0.375000", Solution::pegGame(5, 4, 0, {{2, 2}}));
    EXPECT_EQ("1 1.000000", Solution::pegGame(3, 3, 1, {{1, 1}, {1, 0}}));
    EXPECT_EQ("0 1.000000", Solution::pegGame(3, 4, 0, {{1, 0}, {1, 1}}));
    EXPECT_EQ("0 0.500000", Solution::pegGame(3, 4, 0, {{1, 1}}));
    EXPECT_EQ("0 0.625000", Solution::pegGame(5, 5, 0, {{3, 0}}));
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    Solution::generateResult();
//    return RUN_ALL_TESTS();
}

