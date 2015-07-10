#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef int T;

T max(T x, T y, T z) {
    return std::max(x, std::max(y, z));
}

// Finds the maximum amount of stones possibly gathered by following coordinates
// x,y
// The topmost left is (0,0), bottom right is (columns-1,rows-1)
T max_stones_found_following(T x, T y, vector< vector<T> > A) {
    // Reached the last row?
    if (y == A.size() - 1)
        return A[y][x];
    else {
        T went_left, went_right, went_down;
        if (x - 1 >= 0)
            went_left = max_stones_found_following(x - 1, y + 1, A);
        else
            went_left = numeric_limits<T>::min();
        if (x + 1 <= A[x].size() - 1)
            went_right = max_stones_found_following(x + 1, y + 1, A);
        else
            went_right = numeric_limits<T>::min();
        went_down = max_stones_found_following(x, y + 1, A);
        return A[y][x] + max(went_left, went_right, went_down);
    }
}

int main() {
    // Initialization
    T test_cases, rows, columns, stones_found, max_stones;
    vector< vector<T> > A;
    cin >> test_cases;
    while (test_cases--) {
        // Field input
        cin >> rows >> columns;
        for (int i = 0; i < rows; i++) {
            vector<T> row;
            for (int j = 0; j < columns; j++) {
                T in;
                cin >> in;
                row.push_back(in);
            }
            A.push_back(row);
        }

        max_stones = 0;
        stones_found = 0;
        // Try starting at different positions in the first row
        for (int i = 0; i < columns; i++) {
            stones_found = max_stones_found_following(i, 0, A);
            if (stones_found > max_stones)
                max_stones = stones_found;
        }

        // Output
        cout << max_stones << endl;
    }
    return 0;
}
