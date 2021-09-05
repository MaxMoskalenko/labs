  friend istream &operator>>(istream &in, Matrix &M);
    friend ostream &operator<<(ostream &out, const Matrix &M);
    friend Matrix operator+(const Matrix &A, const Matrix &B);
    friend Matrix operator*(const Matrix &A, const Matrix &B);
    friend Matrix operator*(const double scalar, const Matrix &A);
    friend Matrix operator*(const Matrix &A, const double scalar);
    friend Matrix operator-(const Matrix &A, const Matrix &B);