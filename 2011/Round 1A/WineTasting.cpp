#include "bits/stdc++.h"
#include "gtest/gtest.h"

using namespace std;

typedef long long ll;
const ll MOD = 1051962371;

// Idea: number of derangements: https://en.wikipedia.org/wiki/Derangement
// (a * b) mod m = (a mod m * b mod m) mod m
// (a + b) mod m = (a mod m + b mod m) mod m

ll mult(ll a, ll b) {
    return ((a % MOD) * (b % MOD)) % MOD;
}

vector<ll> dp;
vector<vector<ll>> ch;
const ll MAXN = 123;
void computeNumOfDerangements(ll N) {
    // Return number of permutations where r positions is right
    // and other N - r should be a derangement
    // !n = (n - 1)! (!(n - 2) + !(n - 1)) -> read a nice proof about hats on Wikipedia
    dp.resize(N, 0L);
    dp[0] = 0;
    dp[1] = 0;
    dp[2] = 1;
    for (int k = 3; k <= N; ++k) {
        dp[k] = ((dp[k - 1] % MOD) + (dp[k - 2] % MOD)) % MOD;
        dp[k] = (dp[k] * (k - 1)) % MOD;
    }
}

void computeСhoose(ll N) {
    ch.resize(N + 1, vector<ll> (N + 1, 0L));
    for (int n = 1; n <= N; ++n) {
        ch[n][0] = ch[n][n] = 1;
        for (int k = 1; k < n; ++k) {
            ch[n][k] = ch[n - 1][k] % MOD + ch[n - 1][k - 1] % MOD;
            ch[n][k] %= MOD;
        }
    }
}

class Solution {
private:
public:
    static ll numOfDerangements(ll N) {
        return dp[N];
    }
    static ll choose(ll r, ll N) {
        return ch[N][r];
    }
    static int wineTasting(ll N, ll C) {
        computeNumOfDerangements(MAXN);
        computeСhoose(MAXN);
        // Fix r right positions which is N choose r, r in C...N
        // and other N - r positions should be a derangement.
        // For example, r = [1, 3], n = 7 ->
        // 5 positions [2, 4, 5, 6, 7] and 5 numbers ([2, 4, 5, 6, 7]) available
        // which is exactly !N: [1, ..., n] from [1, ..., n]
        ll result = 0;
        for (ll r = C; r < N; ++r) {
            ll add = mult(choose(r, N), numOfDerangements(N - r));
            result = (result + add) % MOD;
        }
        // add 1L for r == N, otherwise numOfDerangements(0) = 0 =>
        // add = mult(choose(r, N) * 0 = 0 and it should be 1
        
        return (int)((result + 1) % MOD);
    }
    static void generateResult() {
        ios::sync_with_stdio(false);
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        int N;
        cin >> N;
        int idx = 1;
        while (N--) {
            int G, C;
            cin >> G >> C;
            cout << "Case #" << idx++ << ": " << Solution::wineTasting(G, C) << '\n';
        }
    }
};

TEST(SolutionTest, Small) {
    EXPECT_EQ(1, Solution::wineTasting(1, 1));
    EXPECT_EQ(7, Solution::wineTasting(4, 2));
    EXPECT_EQ(1, Solution::wineTasting(5, 5));
    EXPECT_EQ(651, Solution::wineTasting(13, 10));
    EXPECT_EQ(405146859, Solution::wineTasting(14, 1));
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    Solution::generateResult();
//    return RUN_ALL_TESTS();
}

