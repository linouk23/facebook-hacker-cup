#include "bits/stdc++.h"
#include "gtest/gtest.h"

using namespace std;

class Solution {
public:
    static int doubleSquares(int N) {
        if (N == 0) { return 1; }
        auto isSquare = [](int N) -> bool {
            return int(sqrt(N)) * int(sqrt(N)) == N;
        };
        
        // N = x^2 + y^2
        int result = 0;
        for (int x = 0; x <= sqrt(N); ++x) {
            int y = N - x * x;
            if (isSquare(y)) {
                ++result;
            }
        }
        return result / 2;
    }
    static void generateResult() {
        ios::sync_with_stdio(false);
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        int N;
        cin >> N;
        int idx = 1;
        while (cin >> N) {
            cout << "Case #" << idx++ << ": " << Solution::doubleSquares(N) << '\n';
        }
    }
};

TEST(SolutionTest, Small) {
    EXPECT_EQ(1, Solution::doubleSquares(10));
    EXPECT_EQ(2, Solution::doubleSquares(25));
    EXPECT_EQ(0, Solution::doubleSquares(3));
    EXPECT_EQ(0, Solution::doubleSquares(326864818));
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    Solution::generateResult();
//    return RUN_ALL_TESTS();
}
