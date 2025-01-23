// 给定一棵有 n 个点的带边权树，m 次询问，每次询问给出 k，询问树上距离为 k 的点对是否存在。
// n <= 10000, m <= 100, k <= 10000000

#include <cmath>
#include <queue>
#include <cstdio>
#include <bitset>
#include <cstring>
#include <iostream>
#include <algorithm>

#define endl '\n'

using namespace std;
using i64 = long long;

const int si = 3e5 + 10;
const int inf = 1e9 + 7;

int n, m, q[si];
int tot = 0, head[si];
struct Edge { int ver, Next, w; } e[si << 1];
inline void add(int u, int v, int w) { e[tot] = (Edge){v, head[u], w}, head[u] = tot++; } 

std::queue<int> rec;
bool tf[10000010], can[si], vis[si];
// tf: 当前子树的可行性。

int cnt = 0, sum = 0;
int maxv[si], rt = 0;
int d[si], dis[si], siz[si];
// d: 当前子树的 节点-根 距离。
void calcsiz(int u, int fa) {
    siz[u] = 1, maxv[u] = 0;
    for(int i = head[u]; ~i; i = e[i].Next) {
        int v = e[i].ver;
        if(v == fa || vis[v]) continue;
        calcsiz(v, u);
        maxv[u] = max(maxv[u], siz[v]), siz[u] += siz[v];
    }
    maxv[u] = max(maxv[u], sum - siz[u]); // 注意这里是当前子树的节点个数。
    if(maxv[rt] > maxv[u]) rt = u;
}
void calcdis(int u, int fa) {
    d[++cnt] = dis[u]; // 这里复制是为了枚举的时候不全部枚举，保证复杂度。
    for(int i = head[u]; ~i; i = e[i].Next) {
        int v = e[i].ver, w = e[i].w;
        if(v == fa || vis[v]) continue;
        dis[v] = dis[u] + w, calcdis(v, u);
    }
}
void dfs(int u, int fa) {
    tf[0] = true, rec.push(0), vis[u] = true; // 打 vis 是为了确保在子树中进行操作，不会递归出去。
    // 或者不妨说，我们是利用 vis，将树划分成了一个个联通块来处理，因为它每次都只会标记到重心嘛。
    for(int i = head[u]; ~i; i = e[i].Next) {
        int v = e[i].ver, w = e[i].w;
        if(v == fa || vis[v]) continue;
        dis[v] = w, calcdis(v, u);
        for(int j = 1; j <= cnt; ++j) {
            for(int k = 1; k <= m; ++k) {
                if(q[k] >= d[j]) can[q[k]] |= tf[q[k] - d[j]];
            }
        } // 先判断再添加，不然算的不是除了自己子树的情况，这样会多算。
        for(int j = 1; j <= cnt; ++j) {
            if(d[j] < 10000010) rec.push(d[j]), tf[d[j]] = true;
        }
        cnt = 0;
    }

    while(!rec.empty()) tf[rec.front()] = false, rec.pop();
    for(int i = head[u]; ~i; i = e[i].Next) {
        int v = e[i].ver;
        if(v == fa || vis[v]) continue;
        rt = 0, maxv[rt] = inf, sum = siz[v];
        calcsiz(v, u), calcsiz(rt, -1), dfs(rt, u); // 先找重心再递归。
    }
}

int main() {

    cin.tie(0) -> sync_with_stdio(false);
    cin.exceptions(cin.failbit | cin.badbit);

    memset(tf, false, sizeof tf);
    memset(head, -1, sizeof head);
    memset(vis, false, sizeof vis);
    memset(can, false, sizeof can);

    cin >> n >> m;
    for(int i = 1; i < n; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, w);
    }
    for(int nw = 1; nw <= m; ++nw) {
        cin >> q[nw];
    }

    rt = 0, maxv[rt] = inf, sum = n;
    calcsiz(1, -1), calcsiz(rt, -1), dfs(rt, -1); // 因为本题需要用到 tf(0) 所以 fa 就用 -1 了。

    for(int nw = 1; nw <= m; ++nw) {
        if(can[q[nw]]) cout << "AYE" << endl;
        else cout << "NAY" << endl;
    }

    return 0;
}