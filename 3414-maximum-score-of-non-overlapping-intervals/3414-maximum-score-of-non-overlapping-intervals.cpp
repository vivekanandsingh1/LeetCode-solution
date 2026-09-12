class Solution {
public:
    struct Interval {
        long long l, r, w;
        int idx;
    };

    struct State {
        long long score;
        vector<int> list; 

        
        bool betterThan(const State& other) const {
            if (score != other.score) return score > other.score;
            return list < other.list; 
        }
    };

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<Interval> iv(n);
        for (int i = 0; i < n; i++) {
            iv[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }
        
        sort(iv.begin(), iv.end(), [](const Interval& a, const Interval& b) {
            return a.r < b.r;
        });

        vector<long long> rArr(n);
        for (int i = 0; i < n; i++) rArr[i] = iv[i].r;

        
        vector<vector<State>> dp(n + 1, vector<State>(5, {0, {}}));

        for (int i = 1; i <= n; i++) {
            const Interval& cur = iv[i - 1];
            
            int p = lower_bound(rArr.begin(), rArr.end(), cur.l) - rArr.begin();

            for (int j = 0; j <= 4; j++) {
                State best = dp[i - 1][j]; 

                if (j >= 1) {
                    State cand = dp[p][j - 1]; 
                    cand.score += cur.w;
                    auto pos = lower_bound(cand.list.begin(), cand.list.end(), cur.idx);
                    cand.list.insert(pos, cur.idx);

                    if (cand.betterThan(best)) {
                        best = cand;
                    }
                }
                dp[i][j] = best;
            }
        }

        return dp[n][4].list;
    }
};