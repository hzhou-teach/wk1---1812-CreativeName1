// Name: Ben Wei
// 40 mins spent
// Tests: all correct
// Feedback: The "seniority" in this problem made me think of priority queue instantly.
// From there, the coding wasn't super complicated so I mainly just tried to solve this
// problem as fast as I could.

#include <bits/stdc++.h>
using namespace std;

void setIO(string name = "") { // name is nonempty for USACO file I/O
    ios_base::sync_with_stdio(0); cin.tie(0); // see Fast Input & Output
    // alternatively, cin.tie(0)->sync_with_stdio(0);
    if (name.size() > 0) {
        freopen((name+".in").c_str(), "r", stdin); // see Input & Output
        freopen((name+".out").c_str(), "w", stdout);
    }
}

bool comp(const array<int, 3> &a, const array<int, 3> &b) {
    return a[0] < b[0];
}



int main() {
    setIO("convention2");
    int n; cin >> n;
    vector<array<int, 3>> original;
    vector<array<int, 3>> cows;
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        original.push_back({a, b, i});
        cows.push_back({a, b, i}); //ai, ti, seniority
    }
    sort(cows.begin(), cows.end(), comp);
    
    //iterate through list
    //go through all the events in the future that happen before this event ends
    //if event occurs before, add to queue based on seniority (index)
    //endtime = endtime + ti
    //store waiting time for each item
        //waiting time = endtime of previous - ai of original cow
    //change events ai to be equal to ai + waiting time

    int ind = 1, ans = 0, waittime;
    set<pair<int, int>> queue; //priority queue (seniority (for sorting), index)
    int endtime = cows[0][0] + cows[0][1];

    while (ind < n || queue.size() > 0) {
        while (ind < n && cows[ind][0] <= endtime) {
            queue.insert({cows[ind][2], ind});
            ind++;
        }
        if (queue.size() > 0) {
            auto q = queue.begin();
            
            //cows[(*q).second][0] = endtime;
            waittime = endtime - cows[(*q).second][0];
            endtime = endtime + cows[(*q).second][1];
            ans = max(ans, waittime);
            //cout << "q: "  << (*q).first << "," << (*q).second << "cows[second.." << cows[(*q).second][0] << "," << cows[(*q).second][1] << "\n";
            //cout << "ind:" << ind << "endtime:" << endtime << "waittime" << waittime << "\n";
            //cout << "qsize="<< queue.size() << ",";
            queue.erase(q);
            //cout << queue.size() << ",";
            //cout << queue.begin()->second << "\n";
        }
        else {
            endtime = cows[ind][0] + cows[ind][1];
            ind++;
        }
    }
    cout << ans << "\n";
}
