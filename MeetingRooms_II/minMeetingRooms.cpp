int minMeetingRooms(vector<vector<int>>& intervals) {
#if 1
#if 1
    sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b){return a[0] < b[0];});
    priority_queue<int, vector<int>, greater<int>> q;
    for (auto interval : intervals) {
        if (!q.empty() && q.top() <= interval[0])
            q.pop();
        q.push(interval[1]);
    }
    return q.size();
#else
    vector<int> starts, ends;
    int res = 0, endpos = 0;
    for (auto a : intervals) {
        starts.push_back(a[0]);
        ends.push_back(a[1]);
    }
    sort(starts.begin(), starts.end());
    sort(ends.begin(), end.end());
    for (int i = 0; i < intervals.size(); i++) {
        if (starts[i] < ends[endpos])
            res++;
        else
            endpos++;
    }
#endif
#else
    map<int, int> mp;
    for (auto a : intervals) {
        mp[a[0]]++;
        mp[a[1]]--;
    }
    int rooms = 0, res = 0;
    for (auto it : mp) {
        res = max(res, rooms += it.second);
    }
#endif
    return res;
}
