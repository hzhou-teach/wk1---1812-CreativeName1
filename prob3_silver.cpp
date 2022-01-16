// Name: Ben Wei
// 2 hr spent
// Tests: 1, 5, 7, 9, 10 correct; all others incorrect
// Feedback: The low n meant that a large complexity could be used
// for this problem (n^4), so I didn't think about the algorithm 
// much and just went for the easiest and most obvious solution.
// I didn't get 100% on the test cases but I already spent a long 
// time on this problem and just wanted to move on to the others.

#include <iostream>
#include <vector>
using namespace std;

/* algorithm:
while true:
    first, delete all groups with size > k:
        assign groups via floodfill from each tile  
        for group in groups:
            if size > k:
                set all in tiles that are in group to 0

        if none have size > k; return grid

    then, apply gravity (n^2 solution):
        for column in columns:
            for i in column: iterate bottom to top
                while column[i-1] == 0: continuously shift tile i down until it no longer can
                    column[i-1] = column[i]
                    column[i] = 0
*/

const int maxn = 100;

int n, k;
int tiles[10][maxn];
vector<vector<pair<int, int>>> groups;
bool visited[10][maxn];

void setIO(string name = "") { // name is nonempty for USACO file I/O
    ios_base::sync_with_stdio(0); cin.tie(0); // see Fast Input & Output
    // alternatively, cin.tie(0)->sync_with_stdio(0);
    if (name.size() > 0) {
        freopen((name+".in").c_str(), "r", stdin); // see Input & Output
        freopen((name+".out").c_str(), "w", stdout);
    }
}

void test(int i) {
    //cout << "reached " << i << "\n";
}
void floodfill(int i, int j, int group, int color) {
    if (visited[i][j]) return;
    if (tiles[i][j] != color) return;
    if (i < 0 || i > 9 || j < 0 || j >= n) return;
    visited[i][j] = true;
    // cout << "group: " << group << "\n";
    // cout << "color: " << color << "\n";
    groups[group].push_back(make_pair(i, j));
    floodfill(i+1, j, group, color);
    floodfill(i-1, j, group, color);
    floodfill(i, j+1, group, color);
    floodfill(i, j-1, group, color);
}

//runs one iteration, returns false when end
bool run() {
    int group = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < n; j++) {
            
            
            if (!visited[i][j] && tiles[i][j]) {
                groups.push_back({});
                floodfill(i, j, group, tiles[i][j]);
                group++;
            }
        }
    }

    bool flag = false;
    for (vector<pair<int, int>> group : groups) {
        // cout << group.size() << "\n";
        if (group.size() >= k) {
            flag = true;
            for (pair<int, int> coord : group) {
                tiles[coord.first][coord.second] = 0;
            }
        }
    }
    
    // for (int j = 0; j < n; j++) {
    //     for (int i = 0; i < 10; i++) {
    //         cout << tiles[i][j];
    //     }
    //     cout << "\n";
    // }

    //return false;
    if (!flag) return false;

    for (int column = 0; column < 10; column++) {
        // cout << "column:" << column << "\n";
        for (int h = n-1; h >= 0; h--) {
            if (tiles[column][h]) {
                while (!tiles[column][h+1] && h<n-1) {
                    tiles[column][h+1] = tiles[column][h];
                    tiles[column][h] = 0;
                    h++;
                    
                }
                if (h == 9) break;
            }
        }
    }
    // for (int j = 0; j < n; j++) {
    //     for (int i = 0; i < 10; i++) {
    //         cout << tiles[i][j];
    //     }
    //     cout << "\n";
    // }

    groups.clear();
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < n; j++) {
            visited[i][j] = false;
        }
    }

    return true;
}



int main() {
    //input
    setIO("mooyomooyo");
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        string a;
        cin >> a;
        for (int j = 0; j < 10; j++) {

            tiles[j][i] = a[j] - '0'; //converts char to int
        }
    }

    test(0);

    bool r;
    do {
        r = run();
    }
    while (r);
    
    test(999);

    //output
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < 10; i++) {
            cout << tiles[i][j];
        }
        cout << "\n";
    }
}
