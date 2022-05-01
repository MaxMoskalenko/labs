#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<double> > read_matrix(string path, int &size);
vector<double> read_vector(string str, int &size, bool isFromFile);

struct SLE
{
    vector<vector<double> > A;
    vector<double> b;
    vector<double> ksi;
    vector<double> x;
    int n;
    double eps;

    SLE(vector<vector<double> > matrix, vector<double> vec, int size)
    {
        this->A = matrix;

        this->b = vec;
        this->ksi = vec;

        this->n = size;
        this->eps = 0.00001;

        for (int i = 0; i < size; i++)
        {
            this->x.push_back(0);
        }
    }

    void solve()
    {
        int iter = 1;
        print_result(0);
        while (find_residual() && max_norma(ksi) >= eps)
        {
            vector<double> next_x = x;
            for (int i = 0; i < n; i++)
            {
                next_x[i] = (b[i] - calculate_row(i)) / A[i][i];
            }
            x = next_x;

            print_result(iter);
            iter++;
        }
    }

    double calculate_row(int i)
    {
        double result = 0;
        for (int j = 0; j < n; j++)
        {
            if (j == i)
                continue;

            result += A[i][j] * x[j];
        }
        return result;
    }

    bool find_residual()
    {
        for (int r = 0; r < n; r++)
        {
            double scalar = 0;
            for (int i = 0; i < n; i++)
            {
                scalar += A[r][i] * x[i];
            }

            ksi[r] = b[r] - scalar;
        }
        return true;
    }

    double max_norma(vector<double> v)
    {
        double max_val = 0;
        for (int i = 0; i < n; i++)
        {
            max_val = max(max_val, fabs(v[i]));
        }
        return max_val;
    }

    void print_vector(vector<double> v)
    {
        cout << "[ ";
        for (int i = 0; i < n; i++)
        {
            printf("%6f ", v[i]);
        }
        cout << "]" << endl;
    }

    void print_result(int iter)
    {
        cout << "Iteration: " << iter << endl;
        cout << "x  : ";
        print_vector(x);
        find_residual();
        cout << "ksi: ";
        print_vector(ksi);
        cout << "max norma: " << max_norma(ksi) << endl;
        cout << "-----------------------------------------" << endl;
    }
};

int main()
{
    int matrix_size, vector_size;
    vector<vector<double> > matrix = read_matrix("data/A", matrix_size);
    vector<double> vec = read_vector("data/b", vector_size, true);

    if (matrix_size != vector_size)
    {
        cout << "ERR: matrix A and vector b have different sizes";
        abort();
    }

    SLE *system = new SLE(matrix, vec, matrix_size);
    system->solve();
    return 0;
}

vector<vector<double> > read_matrix(string path, int &size)
{
    fstream file;
    file.open(path, ios::in);
    if (!file.is_open())
    {
        cout << "ERR: File cannot be opened" << endl;
        abort();
    }

    vector<vector<double> > matrix;
    int prev_vec_size = -1;
    string line;

    size = 0;

    while (getline(file, line))
    {
        int vec_size;
        matrix.push_back(read_vector(line, vec_size, false));

        if (prev_vec_size == -1)
            prev_vec_size = vec_size;

        if (prev_vec_size != vec_size)
        {
            cout << "ERR: Rows of matrix have different sizes" << endl;
            abort();
        }

        prev_vec_size = vec_size;
        size++;
    }
    if (size != prev_vec_size)
    {
        cout << "ERR: number of rows and sizes of rows are different or your matrix is empty" << endl;
        abort();
    }

    file.close();
    return matrix;
}

vector<double> read_vector(string str, int &size, bool isFromFile)
{
    string line = str;
    if (isFromFile)
    {
        fstream file;
        file.open(str);
        if (!file.is_open())
        {
            cout << "ERR: File cannot be opened" << endl;
            abort();
        }
        getline(file, line);
        file.close();
    }

    int prev_token_index = -1;
    vector<double> vec;

    line = line + " ";
    size = 0;
    while (line.find(" ") != -1 && prev_token_index != line.length() - 1)
    {
        vec.push_back(stod(line.substr(prev_token_index + 1, line.find(" ", prev_token_index + 1))));
        prev_token_index = line.find(" ", prev_token_index + 1);
        size++;
    }
    return vec;
}
