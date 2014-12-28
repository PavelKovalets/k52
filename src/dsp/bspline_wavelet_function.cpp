#include <k52/dsp/bspline_wavelet_function.h>
#include <math.h>

namespace 
{
/// всякая полезная математика
double m1k(int k);                              // четность
int fact(int n);                                // факториал
double xplus(double x, int n);                  // стремная хрень
}

namespace k52
{
namespace dsp
{

/// Bspline implementation
double BSplineWaveletFunction::real(double x, int n)
{
    x /= 2;
    double res = 0;
    static double c6k[] = {1, 6, 15, 20, 15, 6, 1};
    static double c5k[] = {1, 5, 10, 10, 5, 1};
    static double c4k[] = {1, 4, 6, 4, 1};
    static double c3k[] = {1, 3, 3, 1};
    static double c2k[] = {1, 2, 1};
    static double c1k[] = {1, 1};
    double nn = n;

    for (int k=0; k<=(n+1); k++)
    {
        double kk = k;
        double cnk=1;
        if (n + 1 == 1) cnk = c1k[k];
        if (n + 1 == 2) cnk = c2k[k];
        if (n + 1 == 3) cnk = c3k[k];
        if (n + 1 == 4) cnk = c4k[k];
        if (n + 1 == 5) cnk = c5k[k];
        if (n + 1 == 6) cnk = c6k[k];
        res += m1k(k) * (cnk) * xplus((x + (nn + 1) / 2 - kk), n) / (float)fact(n);
    }

    res *= cos(2 * M_PI * x);
    return res;
}

double BSplineWaveletFunction::imag(double x, int n)
{
    x /= 2;

    static double res = 0;
    static double c6k[] = {1, 6, 15, 20, 15, 6, 1};
    static double c5k[] = {1, 5, 10, 10, 5, 1};
    static double c4k[] = {1, 4, 6, 4, 1};
    static double c3k[] = {1, 3, 3, 1};
    static double c2k[] = {1 ,2, 1};
    static double c1k[] = {1, 1};
    double nn = n;

    for (int k = 0; k <= n + 1; k++)
    {
        double kk = k;
        double cnk = 1;
        if (n + 1 == 1) cnk = c1k[k];
        if (n + 1 == 2) cnk = c2k[k];
        if (n + 1 == 3) cnk = c3k[k];
        if (n + 1 == 4) cnk = c4k[k];
        if (n + 1 == 5) cnk = c5k[k];
        if (n + 1 == 6) cnk = c6k[k];
        res += m1k(k) * (cnk) * xplus((x + (nn + 1) / 2 - kk), n) / (float)fact(n);
    }

    res *= sin(2 * M_PI * x);
    return res;
}

} // namespace dsp
} // namespace k52

namespace
{
// some usefull mathematical functions
double m1k(int k)
{
    return k % 2 == 0 ? 1 : -1;
}

int fact(int n)
{
    int res=1;
    for (int i=2; i<=n; ++i)
    {
        res *= i;
    }

    return res;
}

double xplus(double x, int n)
{
    if ((n < 0)||(x < 0)) 
    {
        return 0;
    }

    if (0 == n) 
    {
        return 1;
    }
    
    double res=1.0;
    for (int i=0; i<n; i++)
    {
        res *= x;
    }

    return res;
}
} // namespace
