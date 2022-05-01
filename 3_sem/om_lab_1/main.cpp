#include <iostream>
#include <cmath>

using namespace std;

struct Response
{
    double result;
    string method;
    int number_of_iterations;
    Response(double result, string method, int number_of_iterations)
    {
        this->result = result;
        this->method = method;
        this->number_of_iterations = number_of_iterations;
    }
    void print()
    {
        printf("Result %lf was gained by %s method in %i iterations\n", result, method.c_str(), number_of_iterations);
    }
};

struct Polinom
{
    double lb, rb, eps;
    Polinom(double l_border, double r_border, double epsilon)
    {
        this->lb = l_border;
        this->rb = r_border;
        this->eps = epsilon;
    }
    double f(double x)
    {
        return 4 * pow(x, 5) - 3 * pow(x, 4) + pow(x, 3) + 2 * pow(x, 2) - 4 * x + 7;
    }
    double df(double x)
    {
        return 20 * pow(x, 4) - 12 * pow(x, 3) + 3 * pow(x, 2) + 4 * x - 4;
    }
    double ddf(double x)
    {
        return 80 * pow(x, 4) - 36 * pow(x, 2) + 6 * x + 4;
    }
    Response *bisection_method()
    {
        cout << "\nBISECTION METHOD\n\n";
        double left = lb;
        double right = rb;
        double center = (lb + rb) / 2;
        int iter_num = 0;
        printf("B Iter: %d (a=%lf f(a)=%lf); (b=%lf f(b)=%lf)\n", iter_num, left, f(left), right, f(right));

        while (fabs(right - left) >= eps && fabs(f(center)) >= eps)
        {
            iter_num++;
            center = (left + right) / 2;
            double y = f(center);
            if (y > 0)
                right = center;
            if (y < 0)
                left = center;
            if (y == 0)
                break;

            printf("B Iter: %d (a=%lf f(a)=%lf); (b=%lf f(b)=%lf)\n", iter_num, left, f(left), right, f(right));
        }
        return new Response(center, "bisection", iter_num);
    }

    Response *chord_method()
    {
        cout << "\nCHORD METHOD\n\n";

        double left = lb;
        double right = rb;
        double cur_x = lb;
        int iter_num = 0;
        double prev_x;
        printf("C Iter: %d (a=%lf f(a)=%lf); (b=%lf f(b)=%lf)\n", iter_num, left, f(left), right, f(right));

        do
        {
            iter_num++;
            prev_x = cur_x;
            cur_x = (left * f(right) - right * f(left)) / (f(right) - f(left));
            double y = f(cur_x);
            if (y > 0)
                right = cur_x;
            if (y < 0)
                left = cur_x;
            if (y == 0)
                break;

            printf("C Iter: %d (a=%lf f(a)=%lf); (b=%lf f(b)=%lf)\n", iter_num, left, f(left), right, f(right));

        } while (fabs(cur_x - prev_x) >= eps && fabs(f(cur_x)) >= eps);

        return new Response(cur_x, "chord", iter_num);
    }

    Response *newton_method()
    {
        cout << "\nNEWTON METHOD\n\n";

        double prev_x = f(lb) * ddf(lb) > 0 ? rb : lb;
        double cur_x = prev_x - (f(prev_x) / df(prev_x));
        int iter_num = 0;
        printf("N Iter: x%d=%lf f(x%d)=%lf\n", iter_num, cur_x, iter_num, f(cur_x));

        while (abs(cur_x - prev_x) >= eps && abs(f(cur_x)) >= eps)
        {
            iter_num++;
            prev_x = cur_x;
            cur_x = prev_x - (f(prev_x) / df(prev_x));
            printf("N Iter: x%d=%lf f(x%d)=%lf\n", iter_num, cur_x, iter_num, f(cur_x));
        }
        return new Response(cur_x, "newton", iter_num);
    }
};

int main(int argc, char const *argv[])
{
    if (argc < 4)
    {
        cout << "There are no enough arguments (you need two borders and precision)\n";
        return 1;
    }

    Polinom *p;

    if (stod(argv[1]) > stod(argv[2]))
        p = new Polinom(stod(argv[2]), stod(argv[1]), stod(argv[3]));
    else
        p = new Polinom(stod(argv[1]), stod(argv[2]), stod(argv[3]));

    if (p->f(stod(argv[1])) * p->f(stod(argv[2])) > 0)
    {
        cout << "This borders are invalid (0 or >1 root)\n";
        return 1;
    }

    p->bisection_method()->print();
    p->chord_method()->print();
    p->newton_method()->print();

    return 0;
}
