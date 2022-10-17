#pragma once
#include <vector>

namespace SMatrix {

class SparseMatrix {
    std::vector<double> val;
    std::vector<size_t> column_val;
    std::vector<size_t> row_val;
    size_t size;
public:
    SparseMatrix();
    SparseMatrix(const std::vector<double>& val, size_t size,
        const std::vector<size_t>& column_val, const std::vector<size_t>& row_val);
};

}