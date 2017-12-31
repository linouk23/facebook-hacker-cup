#include "bits/stdc++.h"
#include "gtest/gtest.h"

using namespace std;

// Idea:
// Using DP, it is often possible to change an iteration over
// permutations into an iteration over subsets.
// The DP state is dp[mask] = the least lexicographic string using the words in the mask.
// The answer is dp[(1<<M)-1], that is the least lexicographic string using all the words.
class Solution {
public:
    static string studiousStudent(vector<string> words) {
        int numOfWords = (int)words.size();
        vector<string> dp(pow(2, numOfWords), string(1e2, 'z'));
        int emptySet = 0;
        dp[emptySet] = "";
        for (int mask = 1; mask < pow(2, numOfWords); ++mask) {
            for (int idx = 0; idx < numOfWords; ++idx) {
                bool maskHasItem = (mask & (1 << idx));
                if (!maskHasItem) { continue; }
                int maskWOItem = mask ^ (1 << idx);
                string minConcat = min(dp[maskWOItem] + words[idx],
                                       words[idx] + dp[maskWOItem]);
                dp[mask] = min(dp[mask], minConcat);
            }
        }
        // 2^n - 1 = 11..11
        return dp[pow(2, numOfWords) - 1];
    }
    static void generateResult() {
        ios::sync_with_stdio(false);
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        int N;
        cin >> N;
        int idx = 1;
        while (N--) {
            vector<string> words;
            int numOfWordsLeft;
            cin >> numOfWordsLeft;
            while (numOfWordsLeft--) {
                string word;
                cin >> word;
                words.emplace_back(word);
            }
            cout << "Case #" << idx++ << ": " << Solution::studiousStudent(words) << '\n';
        }
    }
};

TEST(SolutionTest, Small) {
    EXPECT_EQ("duzklvrawqrc",
              Solution::studiousStudent({"k", "duz", "q", "rc", "lvraw"}));
    EXPECT_EQ("cupfacebookforhackerstudentsstudious",
              Solution::studiousStudent({"facebook", "hacker", "cup", "for", "studious", "students"}));
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    Solution::generateResult();
//    return RUN_ALL_TESTS();
}
