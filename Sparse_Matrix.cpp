#include "Sparse_Matrix.h"

#include <iostream>

#define EPSILON 1e-10

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

    std::vector<double> SparseMatrix::operator* (const std::vector<double>& v) const {
        if (v.size() != size) {
            throw "mismatch of dimensions";
        }
        std::vector<double> result(v.size(), 0.f);
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = row_val[i]; j < row_val[i + 1]; ++j) {
                result[i] += val[j] * v[column_val[j]];
            }
        }
        return result;
    }

    double VectorNorm(const std::vector<double>& f) {
        double res = 0.L;

        for (auto& x : f) {
            res += (x * x);
        }

        return sqrt(res);
    }

    double VectorDot(const std::vector<double>& lhs, const std::vector<double>& rhs) {
        if (lhs.size() != rhs.size()) {
            throw "mismatch of dimensions";
        }

        double result = 0.L;

        for (int i = 0; i < lhs.size(); ++i) {
            result += lhs[i] * rhs[i];
        }

        return result;
    }

    std::vector<double> CalcResidual(const SparseMatrix& A, const std::vector<double>& x, const std::vector<double>& f) {

        std::vector<double> residual = (A * x) - f;

        return residual;
    }

    std::vector<double> SolveCGM(std::vector<double> f, const SparseMatrix& A) {
        size_t iterations = 0;

        std::vector<double> x(f.size(), 0.L);
        std::vector<double> r = (f - (A * x));

        if (VectorNorm(r) < EPSILON) {
            return x;
        }

        std::vector<double> p = r;
        double rsold = VectorDot(r, r);
        double rsnew;
        do {
            std::vector<double> Ap = A * p;
            double alpha = rsold / (VectorDot(p, Ap));
            x = x + (alpha * p);
            r = r - (alpha * Ap);

            rsnew = VectorDot(r, r);
            if (sqrt(rsnew) < EPSILON)
                break;
            p = r + (rsnew / rsold) * p;
            rsold = rsnew;

            iterations++;
        } while (true);

        auto residual = CalcResidual(A, x, f);
        std::cout << "Total iterations: " << iterations << '\n';
        std::cout << "Residual:" << '\n' << residual;

        return x;
    }
    
}

std::vector<double> operator-(const std::vector<double>& lhs, const std::vector<double>& rhs) {

    if (lhs.size() != rhs.size()) {
        throw "mismatch of dimensions";
    }

    std::vector<double> result(lhs.size());

    for (int i = 0; i < lhs.size(); ++i) {
        result[i] = (lhs[i] - rhs[i]);
    }

    return result;
}

std::vector<double> operator+(const std::vector<double>& lhs, const std::vector<double>& rhs) {

    if (lhs.size() != rhs.size()) {
        throw "mismatch of dimensions";
    }

    std::vector<double> result(lhs.size());

    for (int i = 0; i < lhs.size(); ++i) {
        result[i] = (lhs[i] + rhs[i]);
    }

    return result;
}

std::vector<double> operator*(const double a, const std::vector<double>& f) {
    std::vector<double> result(f.size());
    for (int i = 0; i < result.size(); ++i) {
        result[i] = a * f[i];
    }
    return result;
}

std::ostream& operator<<(std::ostream& stream, std::vector<double> v) {
    for (auto& x : v) {
        stream << x << '\n';
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, SMatrix::SparseMatrix& matrix) {
    for (auto i = 0; i < matrix.getSize(); ++i) {
        for (auto j = 0; j < matrix.getSize(); ++j) {
            stream << matrix[i][j] << " ";
        }
        stream << '\n';
    }
    return stream;
}

int main (int argc, char* argv[]) {
    using namespace std;
    vector<double> a = {1, 2, 3};
    vector<size_t> b = {0, 1, 2};
    vector<size_t> c = {0, 1, 2, 3};
    SMatrix::SparseMatrix A(a, 3, b, c);
    //cout << A;

    vector<double> a1 = { 4, 1, 1, 3 };
    vector<size_t> b1 = { 0, 1, 0, 1 };
    vector<size_t> c1 = { 0, 2, 4 };
    SMatrix::SparseMatrix B(a1, 2, b1, c1);
    cout << B;

    vector<double> f = {1, 2};

    vector<double> res = SMatrix::SolveCGM(f, B);
    cout << "Result:" << '\n' << res;

    return 0;
}