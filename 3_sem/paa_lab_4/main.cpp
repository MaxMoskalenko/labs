#include <iostream>
#include <ctime>
#include <cmath>

using namespace std;

const double leftX = -2;
const double rightX = 2;

const double leftY = 0;
const double rightY = 2;

const double leftZ = 0;
const double rightZ = 2;


struct Point
{
    double x, y, z;
    Point(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Point()
    {
        this->x = leftX + ((double)rand() / RAND_MAX) * (rightX - leftX);
        this->y = leftY + ((double)rand() / RAND_MAX) * (rightY - leftY);
        this->z = leftZ + ((double)rand() / RAND_MAX) * (rightZ - leftZ);
    }
};

double calculateProbability(int N);
bool isInsideFigure(const Point *p);
double findM(const int N, double p);

const double m = 0.01;

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    // const double p2 = calculateProbability(10);

    //SMALL x in [-1 1]; y in [0 √3] z in [0 1]
    //BIG x in [-2 2]; y in [0 2] z in [0 2]
    const double p2 = 2*sqrt(3)/16.0;

    const int N = (powf(1.96, 2) / powf(m, 2)) * ((1 - p2) / p2);
    cout << "N is equal to " << N << endl;
    cout << "p2 is equal to " << p2 << endl;

    const double p = calculateProbability(N);

    cout << "Total probability: " << p << endl;
    cout << "From Laplas function z = 1.96" << endl;

    const double m = findM(N, p);

    cout << "m is equal to " << m << endl;
    cout << "Minimal V: " << ((rightX - leftX) * (rightY - leftY) * (rightZ - leftZ)) * p * (1-m) << endl;
    cout << "Maximum V: " << ((rightX - leftX) * (rightY - leftY) * (rightZ - leftZ)) * p * (1+m) << endl;
    return 0;
}

double findM(const int N, double p)
{
    return 1.96 * sqrt((1 - p) / (N * p));
}

double calculateProbability(int N)
{
    int success = 0;

    for (int i = 0; i < N; i++)
    {
        const Point *p = new Point();
        if (isInsideFigure(p))
        {
            success++;
        }
        delete p;
    }
    return (double)success / N;
}

bool isInsideFigure(const Point *p)
{
    if (p->x < -2 || p->x > 2)
    {
        return false;
    }
    if (p->y < 0 || p->y > sqrt(4 - pow(p->x, 2)))
    {
        return false;
    }
    if (p->z < 0 || p->z > p->y)
    {
        return false;
    }
    return true;
}
