class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals) {
#if 1
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {return a[0] < b[0];});
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] < intervals[i - 1][1]) {
                return false;
            }
        }
#else
        for (int i = 0; i < intervals.size(); i++) {
            for (int j = i+1; j < intervals.size(); j++) {
                if ((intervals[i][0] >= intervals[j][0] && interverals[i][0] < intervals[j][1]) || 
                    (intervals[j][0] >= intervals[i][0] && intervals[j][0] < intervals[i][1]))
                    return false;
            }
        }
#endif
        return true;
    }
};
