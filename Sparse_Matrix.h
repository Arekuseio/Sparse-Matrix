#pragma once
#include <vector>

namespace SMatrix {

class SparseMatrix {
    std::vector<double> val;
    std::vector<size_t> column_val;
    std::vector<size_t> row_val;
    size_t size;
    size_t nnz; // number of non-zero elements

    struct SparseMatrixLine {
        size_t row = 0;
        const SparseMatrix& matrix;
        double operator[] (size_t column) const;
    };
public:
    SparseMatrix();
    SparseMatrix(const std::vector<double>& val, size_t size,
        const std::vector<size_t>& column_val, const std::vector<size_t>& row_val);

    size_t getSize() const;
    
    SparseMatrix::SparseMatrixLine operator[] (size_t row) const;

    std::vector<double> operator* (const std::vector<double>& v) const;

    std::vector<double> SolveSystem(std::vector<double> f);
};

}