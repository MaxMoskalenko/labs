#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;
struct Matrix
{
    int rows;
    int cols;
    bool isExist;
    vector<vector<double>> values;

    Matrix(string type, int r, int c)
    {
        if (type == "identity")
        {
            for (int i = 0; i < r; i++)
            {
                vector<double> row;

                for (int j = 0; j < c; j++)
                    if (i == j)
                    {
                        row.push_back(1);
                    }
                    else
                    {
                        row.push_back(0);
                    }
                values.push_back(row);
            }
            rows = r;
            cols = c;
            isExist = true;
        }
    }

    Matrix(int r, int c)
    {
        for (int i = 0; i < r; i++)
        {
            vector<double> row;

            for (int j = 0; j < c; j++)
                row.push_back(0);

            values.push_back(row);
        }
        rows = r;
        cols = c;
        isExist = true;
    }

    Matrix()
    {
        isExist = true;
    }

    Matrix(bool exictance)
    {
        isExist = exictance;
    }

    Matrix(const Matrix &A)
    {
        for (int i = 0; i < A.rows; i++)
        {
            vector<double> row;

            for (int j = 0; j < A.cols; j++)
                row.push_back(A.values[i][j]);

            values.push_back(row);
        }
        rows = A.rows;
        cols = A.cols;
        isExist = true;
    }

    void genrateForTest(int r, int c)
    {
        for (int i = 0; i < r; i++)
        {
            vector<double> row;

            for (int j = 0; j < c; j++)
                row.push_back(rand() % 10);

            values.push_back(row);
        }
        rows = r;
        cols = c;
        isExist = true;
    }

    Matrix T()
    {
        Matrix A(rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                A.values[i][j] = values[j][i];
            }
        }
        return A;
    }

    Matrix I()
    {
        Matrix A = adj();
        return (1 / det()) * A;
    }

    Matrix uTriangular(int &detChanges)
    {
        detChanges = 0;
        Matrix A(cols, rows);
        // Matrix A(*this);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
                A.values[i][j] = values[i][j];
        }

        double coef;
        for (int i = 0; i < rows; i++)
        {
            if (A.values[i][i] == 0)
            {
                for (int j = i + 1; j < cols; j++)
                {
                    if (A.values[j][i] == 0)
                    {
                        continue;
                    }
                    for (int k = 0; k < cols; k++)
                    {
                        double tmp = A.values[j][k];
                        A.values[j][k] = A.values[i][k];
                        A.values[i][k] = tmp;
                    }
                    detChanges++;
                }
            }
            if (A.values[i][i] == 0)
            {
                continue;
            }
            for (int j = i + 1; j < rows; j++)
            {

                coef = (A.values[j][i] / A.values[i][i]);

                for (int k = 0; k < cols; k++)
                {
                    A.values[j][k] -= coef * A.values[i][k];
                    if (fabs(A.values[j][k]) < 1e-10)
                    {
                        A.values[j][k] = 0;
                    }
                }
            }
        }
        return A;
    }

    double det()
    {
        double detNum;
        int changeCoef;
        Matrix B = uTriangular(changeCoef);
        detNum = (changeCoef % 2 == 0) ? 1 : -1;

        for (int i = 0; i < rows; i++)
        {
            detNum *= B.values[i][i];
        }
        return detNum;
    }

    Matrix adj()
    {
        Matrix A(cols, rows);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
                A.values[i][j] = values[i][j];
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                Matrix minor = getMinor(i, j);
                int coef = ((i + j) % 2 == 0) ? 1 : -1;
                A.values[j][i] = coef * minor.det();
            }
        }
        return A;
    }

    Matrix getMinor(int row, int col)
    {

        Matrix A(rows - 1, cols - 1);
        for (int i = 0, mi = 0; i < rows; i++, mi++)
        {
            if (i == row)
            {
                mi--;
                continue;
            }
            for (int j = 0, mj = 0; j < cols; j++, mj++)
            {
                if (j == col)
                {
                    mj--;
                    continue;
                }
                A.values[mi][mj] = values[i][j];
            }
        }

        return A;
    }

    int rang()
    {
        int block;
        Matrix A = uTriangular(block);

        int numberOfPivots = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (A.values[i][j] != 0)
                {
                    numberOfPivots++;
                    break;
                }
            }
        }
        return numberOfPivots;
    }

    friend istream &operator>>(istream &in, Matrix &M);
    friend ostream &operator<<(ostream &out, const Matrix &M);
    friend Matrix operator+(const Matrix &A, const Matrix &B);
    friend Matrix operator*(const Matrix &A, const Matrix &B);
    friend Matrix operator*(const double scalar, const Matrix &A);
    friend Matrix operator*(const Matrix &A, const double scalar);
    friend Matrix operator-(const Matrix &A, const Matrix &B);
};

void displayMatrices(unordered_map<string, Matrix> matrices);
void showInstructions();
void addNewMatrix(unordered_map<string, Matrix> &matrices);
void addition(unordered_map<string, Matrix> &matrices);
void multiplication(unordered_map<string, Matrix> &matrices);
void substraction(unordered_map<string, Matrix> &matrices);
void scalarMultiplication(unordered_map<string, Matrix> &matrices);
void transposition(unordered_map<string, Matrix> &matrices);
void inverse(unordered_map<string, Matrix> &matrices);
void adjoint(unordered_map<string, Matrix> &matrices);
void determinant(unordered_map<string, Matrix> &matrices);
void upperTriangular(unordered_map<string, Matrix> &matrices);
void rang(unordered_map<string, Matrix> &matrices);
void matrixPower(unordered_map<string, Matrix> &matrices);
vector<int> rowOfLongest(Matrix A);
void formatedOutput(Matrix A, Matrix B = Matrix(false), Matrix C = Matrix(false), string prefix = "", string abSplitter = "", string bcSplitter = "", string aPower = "");

int main()
{
    srand(time(NULL));
    showInstructions();
    string choice;
    string name;
    unordered_map<string, Matrix> matrices;
    Matrix A;
    Matrix B;
    A.genrateForTest(4, 4);
    B.genrateForTest(4, 4);
    matrices.insert({"A", A});
    matrices.insert({"B", B});

    while (true)
    {
        cout << "\nYour choice: ";
        cin >> choice;
        if (choice == "new")
        {
            addNewMatrix(matrices);
        }
        else if (choice == "dsp")
        {
            displayMatrices(matrices);
        }
        else if (choice == "add")
        {
            addition(matrices);
        }
        else if (choice == "mul")
        {
            multiplication(matrices);
        }
        else if (choice == "sub")
        {
            substraction(matrices);
        }
        else if (choice == "inv")
        {
            inverse(matrices);
        }
        else if (choice == "adj")
        {
            adjoint(matrices);
        }
        else if (choice == "ut")
        {
            upperTriangular(matrices);
        }
        else if (choice == "smul")
        {
            scalarMultiplication(matrices);
        }
        else if (choice == "tr")
        {
            transposition(matrices);
        }
        else if (choice == "det")
        {
            determinant(matrices);
        }
        else if (choice == "rang")
        {
            rang(matrices);
        }
        else if (choice == "pow")
        {
            matrixPower(matrices);
        }
        else if (choice == "help")
        {
            showInstructions();
        }
        else if (choice == "exit")
        {
            break;
        }
        else
        {
            cout << "Ooops, unknown command. Try again." << endl;
        }
    }
}

void addNewMatrix(unordered_map<string, Matrix> &matrices)
{
    string name;
    cout << "Enter name of new matrix (or old one if you want to change): ";
    cin >> name;
    Matrix matrix;
    cin >> matrix;
    try
    {
        matrices[name] = matrix;
    }
    catch (std::out_of_range)
    {
        matrices.insert({name, matrix});
    }
}

void formatedOutput(Matrix A, Matrix B, Matrix C, string prefix, string abSplitter, string bcSplitter, string aPower)
{
    vector<int> wA = rowOfLongest(A);
    vector<int> wB, wC;
    if (B.isExist)
    {
        wB = rowOfLongest(B);
    }
    if (C.isExist)
    {
        wC = rowOfLongest(C);
    }

    int numberOfRows = B.isExist ? max(A.rows, B.rows) : A.rows;
    int center = numberOfRows / 2;

    char shifted = 'A';
    int abShift = 0;
    if (B.isExist)
    {
        if (A.rows > B.rows)
        {
            shifted = 'B';
        }
        else
        {
            shifted = 'A';
        }
        abShift = ceil((double)abs(A.rows - B.rows) / 2);
    }

    for (int i = 0, bi = 0, ci = 0, ai = 0; i < numberOfRows; i++)
    {
        if (i == center)
        {
            cout << prefix;
        }
        else
        {
            for (int j = 0; j < prefix.length(); j++)
            {
                cout << " ";
            }
        }

        if ((shifted != 'A' || i >= abShift) && ai < A.rows)
        {
            cout << "| ";
            for (int j = 0; j < A.cols; j++)
            {
                cout << setw(wA[j]) << A.values[ai][j] << " ";
            }
            cout << "| ";
            ai++;
        }
        else
        {
            cout << "    "; //for 2 sticks and 2 spaces
            for (int j = 0; j < A.cols; j++)
            {
                for (int k = 0; k < wA[j]; k++)
                {
                    cout << " ";
                }

                cout << " ";
            }
        }

        if (i == 0)
        {
            cout << aPower;
        }
        else
        {
            for (int j = 0; j < aPower.length(); j++)
            {
                cout << " ";
            }
        }
        if (i == center)
        {
            cout << abSplitter;
        }
        else
        {
            for (int j = 0; j < abSplitter.length(); j++)
            {
                cout << " ";
            }
        }
        if (B.isExist && (shifted != 'B' || i >= abShift) && bi < B.rows)
        {
            cout << " | ";
            for (int j = 0; j < B.cols; j++)
            {
                cout << setw(wB[j]) << B.values[bi][j] << " ";
            }
            cout << "| ";
            bi++;
        }
        else if (B.isExist)
        {
            cout << "     "; //for 2 sticks and 3 spaces
            for (int j = 0; j < B.cols; j++)
            {
                for (int k = 0; k < wB[j]; k++)
                {
                    cout << " ";
                }

                cout << " ";
            }
        }
        if (i == center)
        {
            cout << bcSplitter;
        }
        else
        {
            for (int j = 0; j < bcSplitter.length(); j++)
            {
                cout << " ";
            }
        }
        if (C.isExist && (shifted != 'A' || i >= abShift) && ci < C.rows)
        {
            cout << " | ";
            for (int j = 0; j < C.cols; j++)
            {
                cout << setw(wC[j]) << C.values[ci][j] << " ";
            }
            cout << "| ";
            ci++;
        }
        cout << endl;
    }
}

void save(Matrix matrix, unordered_map<string, Matrix> &matrices)
{
    string input;

    cout << "Do you want to save this matrix? (yes/no): ";
    while (true)
    {
        cin >> input;

        if (input == "no")
            return;

        if (input != "yes")
        {
            cout << "Repeat please (yes or no): ";
            continue;
        }

        cout << "Enter name for this matrix (if this matrix already exist it will be overwrite): ";
        cin >> input;

        try
        {
            matrices[input] = matrix;
        }
        catch (std::out_of_range)
        {
            matrices.insert({input, matrix});
        }

        return;
    }
}

void showInstructions()
{
    cout << "----- Matrix Calculator -----" << endl;
    cout << "Enter \"new\" to create new matrix" << endl;
    cout << "Enter \"dsp\" to display matrices" << endl;
    cout << "Enter \"add\" to add matrices" << endl;
    cout << "Enter \"mul\" to multiply matrices" << endl;
    cout << "Enter \"sub\" to subtract matrices" << endl;
    cout << "Enter \"inv\" to inverse matrix" << endl;
    cout << "Enter \"adj\" to find adjoint matrix" << endl;
    cout << "Enter \"ut\" to find upper triangular matrix" << endl;
    cout << "Enter \"smul\" to multiply matrix on scalar" << endl;
    cout << "Enter \"tr\" to transpose matrix" << endl;
    cout << "Enter \"det\" to find determinant" << endl;
    cout << "Enter \"rang\" to find rang of matrix" << endl;
    cout << "Enter \"pow\" to power matrix" << endl;
    cout << "Enter \"help\" to show instructions" << endl;
    cout << "Enter \"exit\" to exit" << endl;
};

void displayMatrices(unordered_map<string, Matrix> matrices)
{
    for (auto kv : matrices)
    {
        cout << "Matrix " << kv.first << " with shape " << kv.second.rows << "x" << kv.second.cols << endl;
        cout << kv.second;
        cout << endl;
    }
}

Matrix getMatrix(unordered_map<string, Matrix> &matrices, string specifier = " ")
{
    string input;
    Matrix matrix;
    cin.ignore();
    cout << "Enter name of" + specifier + " matrix (print '-' if you want to enter new): ";

    cin >> input;
    if (input != "-")
    {
        try
        {
            matrix = matrices.at(input);
        }
        catch (std::out_of_range)
        {
            cout << "There is no such matrix, do you want to try again? (yes/no): ";
            cin >> input;
            if (input == "yes")
                return getMatrix(matrices, specifier);
            else
                return Matrix(false);
        }
    }
    else
        cin >> matrix;
    return matrix;
}

void addition(unordered_map<string, Matrix> &matrices)
{
    Matrix A, B;
    A = getMatrix(matrices, " first");
    if (!A.isExist)
        return;
    B = getMatrix(matrices, " second");
    if (!B.isExist)
        return;

    if (A.rows != B.rows || A.cols != B.cols)
    {
        cout << "Invalid sizes of matrices: " << A.rows << "x" << A.cols << " and " << B.rows << "x" << B.cols << endl;
        return;
    }
    Matrix C = A + B;
    formatedOutput(A, B, C, "", "+", "=");
    save(C, matrices);
}

void multiplication(unordered_map<string, Matrix> &matrices)
{
    Matrix A, B;
    A = getMatrix(matrices, " first");
    if (!A.isExist)
        return;
    B = getMatrix(matrices, " second");
    if (!B.isExist)
        return;

    if (A.cols != B.rows)
    {
        cout << "Invalid sizes of matrices: " << A.rows << "x" << A.cols << " and " << B.rows << "x" << B.cols << endl;
        return;
    }
    Matrix C = A * B;
    formatedOutput(A, B, C, "", "x", "=");
    save(C, matrices);
}

void substraction(unordered_map<string, Matrix> &matrices)
{
    Matrix A, B;
    A = getMatrix(matrices, " first");
    if (!A.isExist)
        return;
    B = getMatrix(matrices, " second");
    if (!B.isExist)
        return;

    if (A.rows != B.rows || A.cols != B.cols)
    {
        cout << "Invalid sizes of matrices: " << A.rows << "x" << A.cols << " and " << B.rows << "x" << B.cols << endl;
        return;
    }
    Matrix C = A - B;
    formatedOutput(A, B, C, "", "-", "=");
    save(C, matrices);
}

void scalarMultiplication(unordered_map<string, Matrix> &matrices)
{
    Matrix A;
    A = getMatrix(matrices);
    if (!A.isExist)
        return;
    double scalar;
    cout << "Enter scalar to multiply: ";
    cin >> scalar;
    Matrix B = scalar * A;
    stringstream ss;
    ss << scalar;
    string scalarStr;
    ss >> scalarStr;
    formatedOutput(A, Matrix(false), B, "", "x " + scalarStr, " =");
    save(B, matrices);
}

void transposition(unordered_map<string, Matrix> &matrices)
{
    Matrix A;
    A = getMatrix(matrices);
    if (!A.isExist)
        return;
    if (A.rows != A.cols)
    {
        cout << "Invalid sizes of matrix: " << A.rows << "x" << A.cols << ". It is not square" << endl;
        return;
    }
    Matrix B = A.T();
    formatedOutput(A, Matrix(false), B, "", "", "=", "T");
    save(B, matrices);
}

void inverse(unordered_map<string, Matrix> &matrices)
{
    Matrix A;
    A = getMatrix(matrices);
    if (!A.isExist)
        return;

    if (A.rows != A.cols)
    {
        cout << "Invalid sizes of matrix: " << A.rows << "x" << A.cols << ". It is not square" << endl;
        return;
    }

    if (A.det() == 0)
    {
        cout << "This matrix is not invertible (determinant is zero)" << endl;
        return;
    }

    Matrix B = A.I();
    formatedOutput(A, Matrix(false), B, "", "", "=", "-1");
    save(B, matrices);
}

void adjoint(unordered_map<string, Matrix> &matrices)
{
    Matrix A;
    A = getMatrix(matrices);
    if (!A.isExist)
        return;

    if (A.rows != A.cols)
    {
        cout << "Invalid sizes of matrix: " << A.rows << "x" << A.cols << ". It is not square" << endl;
        return;
    }

    Matrix B = A.adj();
    formatedOutput(A, Matrix(false), B, "", "", "=", "*");
    save(B, matrices);
}

void determinant(unordered_map<string, Matrix> &matrices)
{
    Matrix A;
    A = getMatrix(matrices);
    if (!A.isExist)
        return;

    if (A.rows != A.cols)
    {
        cout << "Invalid sizes of matrix: " << A.rows << "x" << A.cols << ". It is not square" << endl;
        return;
    }

    double det = A.det();

    stringstream ss;
    ss << det;
    string detStr;
    ss >> detStr;

    formatedOutput(A, Matrix(false), Matrix(false), "det", "", "= " + detStr);
}

void upperTriangular(unordered_map<string, Matrix> &matrices)
{
    Matrix A;
    A = getMatrix(matrices);
    if (!A.isExist)
        return;

    int block;
    Matrix B = A.uTriangular(block);
    formatedOutput(A, Matrix(false), B, "", "", "~");
    save(B, matrices);
}

void rang(unordered_map<string, Matrix> &matrices)
{
    Matrix A;
    A = getMatrix(matrices);
    if (!A.isExist)
        return;

    int rang = A.rang();

    stringstream ss;
    ss << rang;
    string rangStr;
    ss >> rangStr;

    formatedOutput(A, Matrix(false), Matrix(false), "rang", "", "= " + rangStr);
}

void matrixPower(unordered_map<string, Matrix> &matrices)
{
    Matrix A, B;
    A = getMatrix(matrices);
    if (!A.isExist)
        return;

    if (A.rows != A.cols)
    {
        cout << "Invalid sizes of matrix: " << A.rows << "x" << A.cols << ". It is not square" << endl;
        return;
    }
    B = Matrix("identity", A.rows, A.cols);
    int power;
    cout << "Enter power of matrix: ";
    cin >> power;

    if (power < 1)
    {
        cout << "Maybe you want to invert matrix?" << endl;
    }

    for (int i = 0; i < abs(power); i++)
    {
        B = B * A;
    }

    stringstream ss;
    ss << power;
    string powerStr;
    ss >> powerStr;
    formatedOutput(A, Matrix(false), B, "", "", "=", powerStr);
    save(B, matrices);
}

vector<int> rowOfLongest(Matrix A)
{
    vector<int> lengths;
    if (!A.isExist)
    {
        return lengths;
    }

    string str;

    int currentLength;
    for (int i = 0; i < A.cols; i++)
    {
        lengths.push_back(0);
        for (int j = 0; j < A.rows; j++)
        {
            ostringstream stream;
            stream << A.values[j][i];
            string str = stream.str();

            // str = to_string(fabs(A.values[j][i]));
            if (str.find('.') != string::npos)
            {
                str.erase(str.find_last_not_of('0') + 1, string::npos);
                str.erase(str.find_last_not_of('.') + 1, string::npos);
            }

            int currentLength = str.size();
            // if (A.values[j][i] < 0)
            // {
            //     currentLength++;
            // }

            if (str.length() > 12)
            {
                currentLength = 12;
            }
            else
            {
                currentLength = str.length();
            }

            if (currentLength > lengths[i])
            {
                lengths[i] = currentLength;
            }
        }
    }
    return lengths;
}

istream &operator>>(istream &in, Matrix &M)
{
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter matrix`s values (press Enter on empty string to stop):\n";
    string value;
    int maxRowSize = 0;
    M.rows = 0;
    while (getline(in, value, '\n') && !value.empty())
    {
        vector<double> row;
        istringstream ss(value);
        string token;
        while (ss >> token)
        {
            row.push_back(stod(token));
        }
        M.values.push_back(row);
        if (maxRowSize < M.values[M.rows].size())
            maxRowSize = M.values[M.rows].size();

        M.rows++;
    }

    for (int i = 0; i < M.values.size(); i++)
    {
        int oldSize = M.values[i].size();
        for (int j = 0; j < maxRowSize - oldSize; j++)
        {
            M.values[i].push_back(0);
        }
    }
    M.rows = M.values.size();
    M.cols = maxRowSize;
    return in;
}

ostream &operator<<(ostream &out, const Matrix &M)
{
    vector<int> widths = rowOfLongest(M);
    for (int i = 0; i < M.rows; i++)
    {
        out << "| ";
        for (int j = 0; j < M.cols; j++)
        {
            out << setw(widths[j]) << M.values[i][j] << " ";
        }
        out << "|\n";
    }
    return out;
}

Matrix operator+(const Matrix &A, const Matrix &B)
{
    Matrix C(A.rows, A.cols);
    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.cols; j++)
        {
            C.values[i][j] = A.values[i][j] + B.values[i][j];
        }
    }
    return C;
}

Matrix operator*(const Matrix &A, const Matrix &B)
{
    Matrix C(A.rows, B.cols);
    for (int i = 0; i < A.rows; ++i)
    {
        for (int j = 0; j < B.cols; ++j)
        {
            for (int k = 0; k < A.cols; ++k)
            {
                C.values[i][j] += A.values[i][k] * B.values[k][j];
            }
        }
    }
    return C;
}

Matrix operator*(const double scalar, const Matrix &A)
{
    Matrix C(A.rows, A.cols);

    for (int i = 0; i < A.rows; i++)
    {
        for (int j = 0; j < A.cols; j++)
        {
            C.values[i][j] = A.values[i][j] * scalar;
        }
    }
    return C;
}

Matrix operator*(const Matrix &A, const double scalar)
{
    return scalar * A;
}

Matrix operator-(const Matrix &A, const Matrix &B)
{
    return A + (-1 * B);
}
