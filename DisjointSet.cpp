#include <iostream>
#include <vector>

class DisjointSet {
public:
    // Constructor to initialize the disjoint set
    DisjointSet(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // Find the representative (root) of the set to which 'x' belongs
    int Find(int x) {
        if (parent[x] == x) {
            return x;
        }
        // Path compression: Make the parent of 'x' the root of the set
        return parent[x] = Find(parent[x]);
    }

    // Union two sets based on their representatives (roots)
    void Union(int x, int y) {
        int rootX = Find(x);
        int rootY = Find(y);

        if (rootX != rootY) {
            // Union by rank: Attach the smaller tree to the root of the larger tree
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

int main() {
    int n = 6; // Number of elements
    DisjointSet ds(n);

    // Union operations
    ds.Union(0, 1);
    ds.Union(1, 2);
    ds.Union(3, 4);

    // Find operations
    std::cout << "Is 0 and 2 in the same set? " << (ds.Find(0) == ds.Find(2)) << std::endl;
    std::cout << "Is 3 and 5 in the same set? " << (ds.Find(3) == ds.Find(5)) << std::endl;

    return 0;
}
