//Find the shortest path between A and B in a graph
#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>

#define maxN 100001
#define Infi 200000001

using namespace std;

struct Edge {
    int point, weight;

    Edge(int u, int w) {
        point = u;
        weight = w;
    };

    bool operator<(const Edge &right) const {
        return weight > right.weight || (weight == right.weight && point > right.point);
    }
};

vector<Edge>Graph[maxN];

priority_queue <Edge> priorityQ;
int N; //number of nodes
int isolatedN; //number of isolated nodes
int A, B; //start and end position
int isolated = 0;
int Parent[maxN];
int Distance[maxN];
bool b[maxN];
bool Done[maxN];

void Dijkstra(int r) {
    int distance;

    Edge e = Edge(0, 0);
    Edge u = Edge(0, 0);

    for (int i = 1; i <= N; ++i) {
        Done[i] = false;
        Distance[i] = Infi;
    }

    Distance[r] = 0;
    Parent[r] = 0;
    priorityQ.push(Edge(r, Distance[r]));

    while (!priorityQ.empty()) {
        u = priorityQ.top();
        priorityQ.pop();

        if ( Done[u.point] )
            continue;

        Done[u.point] = true;

        for (Edge uv:Graph[u.point]) {

           distance = Distance[u.point] + uv.weight;

            if (!Done[uv.point] && distance < Distance[uv.point]) {
                e.point = uv.point;
                e.weight = distance;
                priorityQ.push(e);
                Distance[uv.point] = distance;
                Parent[uv.point] = u.point;
            }
        }
    }
}

void Read() {
    int M = 0, u, v;
    int isolate = 0;
    cin >> N >> M >> isolate;
    cin >> A >> B;

    for (int i = 0; i < N; i++) {
        b[i] = false;
    }

    for (int i = 0; i < isolate; i++) {
        cin >> isolate;
        b[isolate] = true;
    }

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &u, &v);
        if (b[v]) {
            priorityQ.push(Edge(v, 1));
        } else {
            Graph[u].emplace_back(v, 0);
        }
        priorityQ.push(Edge(u, b[u] ? 1 : 0));
    }
}

int main() {
    Read();
    Dijkstra(A);
    vector<int> Path;
    int x = B;
    while (x != A) {
        Path.push_back(x);
        x = Parent[x];
    }
    cout << Path.size() + 1 << " " << Distance[B] << endl;
    cout << A;

    int i;
    for (i = Path.size() - 1; i >= 0; i--)
        cout << " " << Path[i];

    cout << endl;
}
