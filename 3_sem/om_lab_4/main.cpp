#include <iostream>
#include <cmath>
#include <string.h>

using namespace std;

const double EPS = 0.00001;

struct Point
{
    double x, y;

    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    string str()
    {
        return "(" + to_string(x) + "; " + to_string(y) + ")";
    }
};

struct YakobiMatrix
{
    double a00, a01, a10, a11;
    YakobiMatrix(Point *p)
    {
        a00 = cos(p->x + p->y) + 1.302;
        a01 = cos(p->x + p->y);
        a10 = 2 * p->x;
        a11 = 2 * p->y;
    }

    double det()
    {
        return a00 * a11 - (a01 * a10);
    }

    void inverse()
    {
        double det = this->det();
        double new_a00 = a11 / det;
        double new_a01 = -a10 / det;
        double new_a10 = -a01 / det;
        double new_a11 = a00 / det;

        a00 = new_a00;
        a01 = new_a01;
        a10 = new_a10;
        a11 = new_a11;
    }
};

double maxNorma(Point *p);
Point *difference(Point *a, Point *b);
Point *matrixVectorMult(Point *v, YakobiMatrix *m);

struct MethodOfSimpleIteration
{
    void calculate(Point *p)
    {
        cout << "------MSI with starting point: " << p->str() << endl;
        Point *p_next = p;
        int iter = 0;
        do
        {
            p = p_next;
            cout << "Iteration: k=" << iter << " xk=" << p->str() << " Fk=" << F(p)->str() << " |Fk|=" << F(p)->str() << endl;
            p_next = this->Phi(p);
            iter++;
        } while (maxNorma(this->F(p)) > EPS && maxNorma(difference(p_next, p)));
        delete p_next;
    }

    Point *F(Point *p)
    {
        const double x = cos(p->x + 0.812) - 1.522 * p->y - 1.302;
        const double y = p->x + sin(p->y - 1.791) - 0.793;
        return new Point(x, y);
    }

    Point *Phi(Point *p)
    {
        const double x = 0.793 - sin(p->y - 1.791);
        const double y = (1.302 - cos(p->x + 0.812)) / (-1.522);
        return new Point(x, y);
    }
};

struct MethodOfNewton
{
    void calculate(Point *p)
    {
        cout << "------MN with starting point: " << p->str() << endl;
        int iter = 0;
        Point *p_next = p;

        do
        {
            p = p_next;
            cout << "Iteration: k=" << iter << " xk=" << p->str() << " Fk=" << F(p)->str() << " |Fk|=" << F(p)->str() << endl;
            p_next = this->calcNext(p);
            iter++;
        } while (maxNorma(this->F(p)) > EPS && maxNorma(difference(p_next, p)));
        delete p_next;
    }

    Point *F(Point *p)
    {
        const double x = sin(p->x + p->y) + 1.302 * p->x - 0.793;
        const double y = pow(p->x, 2) + pow(p->y, 2) - 1;
        return new Point(x, y);
    }

    Point *calcNext(Point *p)
    {
        YakobiMatrix* W = new YakobiMatrix(p);
        W->inverse();
        return difference(p, matrixVectorMult(this->F(p), W));
    }
};

int main(int argc, char const *argv[])
{
    MethodOfSimpleIteration *MSI = new MethodOfSimpleIteration();
    MethodOfNewton* MN = new MethodOfNewton();

    Point *startPoint = new Point(0, 0);
    MSI->calculate(startPoint);
    startPoint->x = 0;
    startPoint->y = 1;
    MN->calculate(startPoint);

    startPoint->x = 1;
    startPoint->y = -1;
    MN->calculate(startPoint);

    delete startPoint;
    delete MSI;
    delete MN;

    return 0;
}

double maxNorma(Point *p)
{
    return sqrt(pow(p->x, 2) + pow(p->y, 2));
}

Point *difference(Point *a, Point *b)
{
    return new Point(a->x - b->x, a->y - b->y);
}

Point *matrixVectorMult(Point *v, YakobiMatrix *m)
{
    double x = m->a00 * v->x + m->a01 * v->y;
    double y = m->a10 * v->x + m->a11 * v->y;
    return new Point(x, y);
}