#include "Sparse_Matrix.h"

namespace SMatrix {
    SparseMatrix::SparseMatrix() {
        size = 0;
        row_val.resize(1, 0);
    }

    SparseMatrix::SparseMatrix(const std::vector<double>& val, size_t size,
        const std::vector<size_t>& column_val, const std::vector<size_t>& row_val) {
        if (val.size() != column_val.size()) {
            throw "Invalid sizes of column_val and val";
        }
        if (val.size() != row_val.back() || row_val.front() != 0) {
            throw "Invalid values in row_val";
        }
        this->size = size;
        this->val = val;
        this->column_val = column_val;
        this->row_val = row_val;
    }
}

int main (int argc, char* argv[]) {
    SMatrix::SparseMatrix A({1, 2, 3}, 3, {0, 1, 2}, {0, 1, 2, 3});
    return 0;
}