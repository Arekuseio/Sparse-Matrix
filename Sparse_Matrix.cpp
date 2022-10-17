#include "Sparse_Matrix.h"

#include <iostream>

namespace SMatrix {
    SparseMatrix::SparseMatrix() {
        size = 0;
        row_val.resize(1, 0);
        nnz = 0;
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
        nnz = val.size();
    }

    size_t SparseMatrix::getSize() const {
        return this->size;
    }

    SparseMatrix::SparseMatrixLine SparseMatrix::operator[] (size_t row) const {
        return {row, *this};
    }

    double SparseMatrix::SparseMatrixLine::operator[] (size_t column) const {
        size_t upper_bound = row < (matrix.row_val.size() - 1) ? matrix.row_val[row + 1] : matrix.val.size();
        for (size_t i = matrix.row_val[row]; i < upper_bound; ++i) {
            if (matrix.column_val[i] == column)
                return matrix.val[i];
        }
        return 0.f;
    }
}

int main (int argc, char* argv[]) {
    using namespace std;
    vector<double> a = {1, 2, 3};
    vector<size_t> b = {0, 1, 2};
    vector<size_t> c = {0, 1, 2, 3};
    SMatrix::SparseMatrix A(a, 3, b, c);
    for (size_t i = 0; i < A.getSize(); ++i) {
        for (size_t j = 0; j < A.getSize(); ++j) {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}