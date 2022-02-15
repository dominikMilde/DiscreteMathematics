#include<iostream>
#include<fstream>
#include<cmath>

using namespace std;

int main(void) {
    ifstream stream;
    string fileName;
    cout << "Unesite ime datoteke: ";
    cin >> fileName;
    stream.open(fileName);

    int n = 0;
    stream >> n;
    bool matricaSusjedstva[n][n];
    stream.ignore(1, '\n');

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            stream >> matricaSusjedstva[i][j];
        }
    }
    stream.close();

    int min = n + 1, poljeIndeksa[n][n];
    for(auto i = 0; i < n; i++){
        int k = 0;
        for(auto j = 0; j < n; j++){
            if(matricaSusjedstva[i][j]){
                poljeIndeksa[i][k] = j+1;
                k++;
            }
        }
        for(auto j = n-1; j >= k; j--){
            poljeIndeksa[i][j] = 0;
        }
    }
    int tmp = 0;
    int prevRedovi[n], k = 0;
    for(auto i = 0; i < n; i++){
        prevRedovi[i] = -1;
    }
    for(auto j = 0; j < n; j++){
        static int i = 0,  prethodniRed = -1, stat = 0;
        if(poljeIndeksa[i][j] != 0 && poljeIndeksa[i][j] != prethodniRed + 1){
            if(i == 0) stat = j;
            tmp++;
            prethodniRed = i;
            i = poljeIndeksa[i][j] - 1;
            for(auto m = 0; m < k; m++){
                if(poljeIndeksa[prethodniRed][j] == prevRedovi[m]){
                    if(tmp < min) min = tmp;
                    tmp = 0;
                    for(auto m = 0; m < k; m++){
                        prevRedovi[m] = -1;
                    }
                    k = 0;
                }
            }
            if(prethodniRed < i){
                prevRedovi[k++] = prethodniRed;
                j = -1;
            }
            else j = stat;
        }
        else if(poljeIndeksa[i][j] == 0){
            i = 0;
            prethodniRed = -1;
            for(auto m = 0; m < k; m++){
                prevRedovi[m] = -1;
            }
            k = 0;
            tmp = 0;
        }
    }
    if(min == n + 1) min = 0;
    cout << "Struk zadanog grafa je " << min << endl;
    system("pause");
    return 0;
}