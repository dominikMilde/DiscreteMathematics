#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
long double zatvorenaFormula(int a0, int a1, long double x0, long double x1, int n)
{
    long double lambda2 = (a1 - x0 * a0) / (x1 - x0);
    long double lambda1 = a0 - lambda2;
    cout << "trazim clan po formuli: "
         << "(" << a1 << "-" << x0 << "*" << a0 << ") / (" << x1 << " - " << x0 << ") *" << x1 << "^" << n << " + (" << a0 << " - "
         << a1 << "-" << x0 << "*" << a0 << ") / (" << x1 << " - " << x0 << ")) * " << x0 << "^" << n << endl;
    return (lambda1 * pow(x0, n) + lambda2 * pow(x1, n));
}

long double rekurzivno(int a0, int a1, long double x0, long double x1, int n)
{
    if (n == 0)
    {
        return a0;
    }
    if (n == 1)
    {
        return a1;
    }
    /*if(n==2){
        return (a1*(x1+x0) - a0*(x0*x1));
    }*/
    //nepotrebno, od a2 već vrijedi rekurzija
    else
    {
        return ((x0 + x1) * rekurzivno(a0, a1, x0, x1, n - 1) - rekurzivno(a0, a1, x0, x1, n - 2) * (x0 * x1));
    }
}

long double iterativno(long double a0, long double a1, long double x0, long double x1, int n)
{
    long double rez;
    for (int i = 2; i <= n; i++)
    {
        rez = (x0 + x1) * a1 - (x0 * x1) * (a0);
        a0 = a1;
        a1 = rez; // a1 mi je prije bio int!
    }
    return rez;
}

int main(void)
{
    long int a0, a1;
    int n;
    long double x0, x1;

    cout << "Unesite prvo rjesenje x_0 karakteristicne jednadzbe: ";
    cin >> x0;

    cout << "Unesite drugo rjesenje x_1 karakteristicne jednadzbe: ";
    cin >> x1;

    cout << "Unesite vrijednost nultog clana niza a_0: ";
    cin >> a0;

    cout << "Unesite vrijednost prvog clana niza a_1: ";
    cin >> a1;

    cout << "Unesite redni broj n trazenog clana niza ";
    cin >> n;

    cout << endl;

    long double rez1 = zatvorenaFormula(a0, a1, x0, x1, n);
    cout << setprecision(10);
    cout << fixed;
    cout << "Vrijednost n-tog clana niza pomocu formule: " << rez1 << endl;

    //long double rez2 = rekurzivno(a0, a1, x0, x1, n);
    //cout << "Vrijednost n-tog clana niza iz rekurzije: " << rez2 << endl;

    long double rez3 = iterativno((long double)a0, (long double)a1, x0, x1, n);
    cout << "Vrijednost n-tog clana niza rekurzivno: " << rez3 << endl;

    cout << endl;

    system("pause");
    return 0;
}