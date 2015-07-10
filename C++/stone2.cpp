#include <algorithm>
#include <iostream>
#include <vector>

typedef std::vector<int> row_t;
typedef std::vector<row_t> matrix_t;

int main() {
    // Initialization
    int test_cases, rows, columns;
    matrix_t A;
    std::cin >> test_cases;
    while (test_cases--) {
        std::cin >> rows >> columns;
        for (int i = 0; i < rows; i++) {
            row_t row(columns);
            int in;
            for (int j = 0; j < columns; j++) {
                std::cin >> in;
                row[j] = in;
            }
            A.push_back(row);
        }
		if(rows > 0 && columns > 0) {

			// For storing the best path to each cell
			matrix_t best_A (rows, row_t(columns, 0));
			std::copy(A[0].begin(), A[0].end(), best_A[0].begin());

			for (int i = 1; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					// right down
					if (j > 0 && best_A[i - 1][j - 1] + A[i][j] > best_A[i][j]) {
						best_A[i][j] = best_A[i - 1][j - 1] + A[i][j];
					}
					// left down
					if (j < columns - 1 && best_A[i - 1][j + 1] + A[i][j] > best_A[i][j]) {
						best_A[i][j] = best_A[i - 1][j + 1] + A[i][j];
					}
					// down
					if (best_A[i - 1][j] + A[i][j] > best_A[i][j]) {
						best_A[i][j] = best_A[i - 1][j] + A[i][j];
					}
				}
			}

			// Output
			std::cout << *std::max_element(best_A[best_A.size() - 1].begin(), best_A[best_A.size() - 1].end()) << std::endl;
		} else {
			std::cout << 0 << std::endl;
		}
    }
    return 0;
}
