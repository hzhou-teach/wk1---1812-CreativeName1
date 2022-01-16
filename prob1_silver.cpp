// Name: Ben Wei
// 50 minutes spent
// Tests: all correct
// Feedback: It took me a couple minutes to get to the binary search solution,
// but once I got there the algorithm isn't very complex. The main problem
// I ran into was nailing the binary search because I always had some off
// by one errors when I wasn't thinking about it properly.

#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)(x).size()

int n, m, c; 
vector<int> cows;

void setIO(string name = "") { // name is nonempty for USACO file I/O
    ios_base::sync_with_stdio(0); cin.tie(0); // see Fast Input & Output
    // alternatively, cin.tie(0)->sync_with_stdio(0);
    if (sz(name)) {
        freopen((name+".in").c_str(), "r", stdin); // see Input & Output
        freopen((name+".out").c_str(), "w", stdout);
    }
}

bool test(int t) {
    int buses = 1, buscap = 1, busbegin = cows[0];
    for (int i = 1; i < n; i++) {
        if (cows[i] - busbegin > t || buscap >= c) { //create new bus if prev is full or waiting too long
            buses++;
            buscap = 0;
            busbegin = cows[i];
        }
        buscap++;
    }
    return buses <= m;
    //iterate through
    //if current cow - prev > t, move to next bus
    //add one to current bus
    //if number of buses used exceeds the number of buses, break, return false
    //return true
}

int main() {
    setIO("convention");
    cin >> n >> m >> c;
    for (int i = 0; i < n; i++) {
        int a; cin >> a; cows.push_back(a);
    }
    sort(cows.begin(), cows.end());
    //binary search
    int low = 0;
    int high = *cows.end()-1;
    int ans;
    //false means impossible; too high
    while (low <= high) {
        int mid = (low + high) / 2;
        if (high-low <= 1) {
            if (test(low)) {
                ans = low;
                break;
            }
            else {
                ans = high;
                break;
            }

        }
        if (test(mid)) high = mid;
        else low = mid+1;
    }
    cout << ans << "\n";
}
