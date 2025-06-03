#include <iostream>
#include<fstream>
#include<cmath>
#include<math.h>
#include<vector>
#include <iomanip> 
const double a1 = sqrt(3);
const double a2 = sqrt(7) + 7;
const double a3 = log(3) / log(10);
const double a = -1;
const double b = 0;
double AimFunc(const double x)
{
    double r1, r2;
    r1 = std::pow(((a1 * std::pow(x, 3) - 2 * x + 5) / a2), a3);
    r2 = asin((std::pow(x, 2) + x + a1) / (2 * x - 2));
    return r1 + r2;
}
std::vector<double> Gold(double eps)
{
    std::vector<double> otr;
    double tau1 = 2 / (sqrt(5) + 3);
    double tau2 = 2 / (sqrt(5) + 1);
    double ak = a;
    double bk = b;
    double x1, x2,f1,f2;
    int count=0;
    x1 = ak + tau1 * (bk - ak);
    x2 = ak + tau2 * (bk - ak);
    f1 = AimFunc(x1);
    f2 = AimFunc(x2);
    otr.push_back(x1);
    otr.push_back(x2);
    otr.push_back(f1);
    otr.push_back(f2);
    while (abs(bk - ak) > eps)
    {
        if (count > 100)
        {
            break;
        }
        count++;
        if (f1 > f2)
        {
            bk = x2;
            x2 = x1;
            f2 = f1;
            x1= ak + tau1 * (bk - ak);
            f1 = AimFunc(x1);
        }
        else
        {
            ak = x1;
            x1 = x2;
            f1 = f2;
            x2 = ak + tau2 * (bk - ak);
            f2 = AimFunc(x2);
        }
        otr.push_back(ak);
        otr.push_back(bk);
        otr.push_back(f1);
        otr.push_back(f2);
    }
    return otr;
}
std::vector<double> Dich(double eps)
{
    std::vector<double> otr;
    double ak = a;
    double bk = b;
    double delta = eps / 2 - eps / 10;
    double x1, x2, f1, f2;
    while (abs(bk - ak) > eps)
    {
        x1 = (bk + ak) / 2 - delta;
        x2 = x1 + 2 * delta;
        f1 = AimFunc(x1);
        f2 = AimFunc(x2);
        if (f1 > f2)
        {
            bk = x2;
        }
        else
        {
            ak = x1;
        }
        otr.push_back(ak);
        otr.push_back(bk);
        otr.push_back(f1);
        otr.push_back(f2);
    }
    return otr;
}

int main()
{
    double eps[3];
    int n;
    eps[0] = 0.01;
    eps[1] = 0.000001;
    eps[2] = 1e-17;
    std::vector<double> otrdich,otrgold;
    otrdich = Dich(eps[2]);
    n = otrdich.size();
    std::ofstream file;
    file.open("Dich3.txt");
    file << std::setprecision(17);
    for (int i = 0; i < n; i += 4)
    {
        file << i/4+1 << ' ' << otrdich[i] << ' ' << otrdich[i+1] << ' ' << otrdich[i+2] << ' ' << otrdich[i+3] <<' '<< (otrdich[i] + otrdich[i + 1])/2<<  std::endl;
    }
    file.close();
    otrgold = Gold(eps[2]);
    n = otrgold.size();
    file.open("Gold3.txt");
    for (int i = 0; i < n; i += 4)
    {
        file << i / 4 + 1 << ' ' << otrgold[i] << ' ' << otrgold[i + 1] << ' ' << otrgold[i + 2] << ' ' << otrgold[i + 3] << ' '<< (otrgold[i]+ otrgold[i+1])/2<< std::endl;
    }
    file.close();
    std::cout << "Hello World!\n";

    return 0;
}

