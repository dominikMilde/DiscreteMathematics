#include <iostream>
#include <fstream>
#include <set>
using namespace std;

bool checkColoring(bool *matSusjedstva, int bojeVrhova[], int brojVrhova)
{
   for (int i = 0; i < brojVrhova; i++)
   {
      for (int j = i + 1; j < brojVrhova; j++)
      {
         if (matSusjedstva[i * brojVrhova + j]) // ako je neki od susjeda iste boje
         {
            if (bojeVrhova[i] == bojeVrhova[j])
               return false;
         }
      }
   }
   return true;
}

void printMatrix(bool *matSusjedstva, int brojVrhova)
{
   for (int i = 0; i < brojVrhova; i++)
   {
      for (int j = 0; j < brojVrhova; j++)
      {
         cout << matSusjedstva[i * brojVrhova + j] << " ";
      }
      cout << endl;
   }
}

int cromaticNumber(int bojeVrhova[], int brojVrhova)
{
   int counter = 0;
   set<int> boje;
   for (int i = 0; i < brojVrhova; i++)
   {
      if (bojeVrhova[i] == 0)
      {
         cout << "Graf nije obojan!" << endl;
         return -1;
      }
      boje.insert(bojeVrhova[i]);
   }
   return boje.size();
}

int minChromaticNumber = INT_MAX;
bool prviVrh = true;

// optimizacija: udi u prvi vrh samo jednom, nemoj rekurzivno za prvi vrh vise puta
void oboji(bool *matSusjedstva, int bojeVrhova[], int brojVrhova, int trenutniVrh, int trenutnaBoja)
{
   set<int> razliciteBoje;
   for (int i = 0; i < brojVrhova; i++)
   {
      razliciteBoje.insert(bojeVrhova[i]);
   }
   razliciteBoje.erase(0);
   if (razliciteBoje.size() >= minChromaticNumber)
   {
      return;
   }

   for (int drugiVrh = 0; drugiVrh < brojVrhova; drugiVrh++)
   {
      if (matSusjedstva[trenutniVrh * brojVrhova + drugiVrh])
      {
         if (bojeVrhova[drugiVrh] == trenutnaBoja)
         {
            return;
         }
      }
   }
   bojeVrhova[trenutniVrh] = trenutnaBoja;

   if (trenutniVrh == brojVrhova - 1)
   {
      minChromaticNumber = min(minChromaticNumber, cromaticNumber(bojeVrhova, brojVrhova));
      return;
   }

   for (int bojaSljedecegVrha = 1; bojaSljedecegVrha <= brojVrhova; bojaSljedecegVrha++)
   {
      oboji(matSusjedstva, bojeVrhova, brojVrhova, trenutniVrh + 1, bojaSljedecegVrha);
   }
}

int main(void)
{
   ifstream stream;
   string imeDatoteke;
   cout << "Ime datoteke s matricom: ";
   cin >> imeDatoteke;
   stream.open(imeDatoteke);

   int brojVrhova;
   stream >> brojVrhova;
   bool matSusjedstva[brojVrhova][brojVrhova];

   stream.ignore(1, '\n'); //zadani format datoteke

   for (int i = 0; i < brojVrhova; i++)
   {
      for (int j = 0; j < brojVrhova; j++)
      {
         stream >> matSusjedstva[i][j];
      }
   }

   // printMatrix(matSusjedstvaPointer, brojVrhova);
   bool *matSusjedstvaPointer = (bool *)(matSusjedstva);
   int bojeVrhova[brojVrhova] = {0};

   bojeVrhova[0] = 1;
   oboji(matSusjedstvaPointer, bojeVrhova, brojVrhova, 0, 1);
   cout << "kromatski broj je: " << minChromaticNumber;
   cout << endl;
   system("pause");
   return 0;
}