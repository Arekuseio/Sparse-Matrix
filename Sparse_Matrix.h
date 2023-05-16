#pragma once
#include <vector>
#include <iostream>

namespace SMatrix {

class SparseMatrix {
    std::vector<double> val;        // vector of all non-zero elements in matrix
    std::vector<size_t> column_val; // number of column for each non-zero element
    std::vector<size_t> row_val;    // number of non-zero elements from row number i - 1 to i, always contains 0 as first element
    size_t size;                    // number of dimensions in matrix
    size_t nnz;                     // number of non-zero elements

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