#include <iostream>
using namespace std;

void constructOBST();
void printTree(int, int);

float p[20], q[20], w[20][20], c[20][20];
int r[20][20], n;

int main() {
    cout << "\n**** PROGRAM FOR OBST ******\n";
    cout << "Enter the number of nodes: ";
    cin >> n;

    cout << "Enter probabilities for successful search:\n";
    for (int i = 1; i <= n; i++) {
        cout << "p[" << i << "]: ";
        cin >> p[i];
    }

    cout << "Enter probabilities for unsuccessful search:\n";
    for (int i = 0; i <= n; i++) {
        cout << "q[" << i << "]: ";
        cin >> q[i];
    }

    constructOBST();
    printTree(0, n);
    cout << endl;
}

void constructOBST() {
    for (int i = 0; i <= n; i++) {
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;
        if (i < n) {
            w[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
            c[i][i + 1] = w[i][i + 1];
            r[i][i + 1] = i + 1;
        }
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            c[i][j] = 1e9;
            for (int k = i + 1; k <= j; k++) {
                float cost = c[i][k - 1] + c[k][j];
                if (cost < c[i][j]) {
                    c[i][j] = cost;
                    r[i][j] = k;
                }
            }
            c[i][j] += w[i][j];
        }
    }

    cout << "\nOptimal BST Cost: " << c[0][n] << "\n";
}

void printTree(int left, int right) {
    if (left >= right) return;
    
    int root = r[left][right];
    
    if (root > 0) {
        cout << "Root of subtree [" << left + 1 << ", " << right << "]: " << root << "\n";
    }

    if (r[left][root - 1] > 0)
        cout << "Left child of " << root << ": " << r[left][root - 1] << "\n";
    if (r[root][right] > 0)
        cout << "Right child of " << root << ": " << r[root][right] << "\n";
    
    printTree(left, root - 1);
    printTree(root, right);
}
