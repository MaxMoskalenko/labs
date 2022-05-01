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
    vector<vector<double> > T;
    vector<vector<double> > A_I;
    vector<vector<double> > I;
    vector<double> T_b;
    vector<double> b;
    vector<double> x;
    vector<double> r;
    int n;
    double det;

    SLE(vector<vector<double> > matrix, vector<double> vec, int size)
    {
        this->T = matrix;
        this->A_I = matrix;
        this->A = matrix;
        this->I = matrix;

        this->T_b = vec;
        this->b = vec;
        this->x = vec;
        this->r = vec;

        this->n = size;
        this->det = 1;
    }

    void print_matrix(vector<vector<double> > M)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                printf("%f\t", M[i][j]);
            }
            cout << "\n";
        }
        cout << "-------------------------------------------------------" << endl;
    }

    void print_vector(vector<double> v)
    {
        for (int i = 0; i < n; i++)
        {
            printf("%f\t", v[i]);
        }
        cout << endl;
    }

    void find_triangle(bool is_show_results)
    {
        for (int i = 0; i < n; i++)
        {
            int biggest_index = find_biggest_in_col(i);

            if (biggest_index != i)
                swap_rows(biggest_index, i);

            if (T[i][i] == 0)
            {
                cout << "ERR: Matrix A is singular (det = 0)" << endl;
                abort();
            }

            for (int k = i + 1; k < n; k++)
                substract_rows(k, i, T[k][i] / T[i][i]);

            det *= T[i][i];

            if (is_show_results)
            {
                printf("Matrix after forming row %d:\n", i + 1);
                print_matrix(T);
            }
        }
    }

    void substract_rows(int min, int sub, double koef)
    {
        for (int c = 0; c < n; c++)
            T[min][c] = T[min][c] - koef * T[sub][c];

        T_b[min] = T_b[min] - koef * T_b[sub];
    }

    void swap_rows(int i1, int i2)
    {
        vector<double> tmp = T[i1];
        T[i1] = T[i2];
        T[i2] = tmp;

        double tmp_d = T_b[i1];
        T_b[i1] = T_b[i2];
        T_b[i2] = tmp_d;
        det *= -1;
    }

    int find_biggest_in_col(int col)
    {
        int max_val = 0;
        int row = 0;
        for (int i = col; i < n; i++)
        {
            if (fabs(T[i][col]) > max_val)
            {
                max_val = fabs(T[i][col]);
                row = i;
            }
        }
        return row;
    }

    void backward_elimination()
    {
        for (int k = n - 1; k >= 0; k--)
        {
            double sum = 0;
            for (int j = k + 1; j < n; j++)
                sum += T[k][j] * x[j];

            x[k] = (T_b[k] - sum) / T[k][k];
        }
    }

    void get_residual_vector()
    {
        for (int i = 0; i < n; i++)
        {
            r[i] = b[i] - prod_of_vecs(x, A[i]);
        }
    }

    void find_inverse()
    {
        for (int c = 0; c < n; c++)
        {
            this->T_b = generate_single_vector(c);
            this->T = A;
            find_triangle(false);
            backward_elimination();
            for (int r = 0; r < n; r++)
                A_I[r][c] = x[r];
        }
    }

    double prod_of_vecs(vector<double> v1, vector<double> v2)
    {
        double sum = 0;
        for (int j = 0; j < n; j++)
            sum += v1[j] * v2[j];
        return sum;
    }

    void multiply_matrices()
    {
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < n; c++)
            {
                I[r][c] = prod_of_vecs(A[r], A_I[c]);
            }
        }
    }

    vector<double> generate_single_vector(int index_of_one)
    {
        vector<double> v(n, 0);
        v[index_of_one] = 1;
        return v;
    }

    void solve()
    {
        cout << "Initial matrix:" << endl;
        print_matrix(A);
        find_triangle(true);
        printf("det(A) = %f\n", det);
        backward_elimination();
        cout << "Result vector x:" << endl;
        print_vector(x);
        get_residual_vector();
        cout << "Residual vector r:" << endl;
        print_vector(r);

        find_inverse();
        cout << "Inverse matrix:" << endl;
        print_matrix(A_I);

        multiply_matrices();
        cout << "Result of A * A⁻¹:" << endl;
        print_matrix(I);
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
