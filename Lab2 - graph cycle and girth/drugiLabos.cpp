#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

#define MAX 20 //zbog kompajlera
using namespace std;

bool matrica[MAX][MAX];

int vratiCiklus(int n){ //n je dimenzija matrice
   int najmanjiCiklus = INT_MAX;

   //iteracija za svaki vrh
   for(int vrh = 0; vrh < n; vrh++){
      vector<int> posjeceni(n, -1); //u početku nema "roditelja"
      vector<int> udaljenostiOdTrenutnogVrha (n, INT_MAX);
     
      udaljenostiOdTrenutnogVrha[vrh] = 0; //sam do sebe je udaljenosti 0
      queue<int> susjedi; //red se koristi jer je first in first out struktura
      susjedi.push(vrh);
      while (!susjedi.empty()){
         int trenutni = susjedi.front(); //spremi vrijednost prvoga na izlazu
         susjedi.pop();                  //mičem ga iz susjeda

         //sada za trenutnog moramo naći s kojima je susjed
         for(int susjed = 0; susjed < n; susjed++){
            if(matrica[susjed][trenutni]){
               if(udaljenostiOdTrenutnogVrha[susjed] == INT_MAX){
                  udaljenostiOdTrenutnogVrha[susjed] = udaljenostiOdTrenutnogVrha[trenutni] + 1;
                  susjedi.push(susjed); //nađen je susjed
                  posjeceni[susjed] = trenutni; //označi "od kuda smo došli" do susjeda
               }
               else if(posjeceni[susjed] != trenutni && posjeceni[trenutni] != susjed){
                  //sada znamo da će biti udaljenosti barem 3
                  int udaljenost = udaljenostiOdTrenutnogVrha[trenutni] + udaljenostiOdTrenutnogVrha[susjed] + 1;
                  if(udaljenost < najmanjiCiklus){
                     najmanjiCiklus = udaljenost;
                  }
               }
            }
         }
      }
   }

   if(najmanjiCiklus == INT_MAX){
      return -1; //nije validna duljina, znači nema ciklusa
   }
   return najmanjiCiklus;
}

int main(void) {
    ifstream stream;
    string imeDatoteke;
    cout << "Ime datoteke s matricom: ";
    cin >> imeDatoteke;
    stream.open(imeDatoteke);

    int n;
    stream >> n;
    
    stream.ignore(1, '\n'); //zadani format datoteke
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            stream >> matrica[i][j];
        }
    }

   int struk = vratiCiklus(n);
   if(struk != -1)
      cout << "Struk zadanog grafa je " << vratiCiklus(n);
   else
   {
      cout << "Zadani graf nema ciklus.";
   }
   cout << endl;
   
   system("pause");
   return 0;
}