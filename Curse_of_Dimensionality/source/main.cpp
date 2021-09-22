#include <random>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <ratio>
#include <chrono>
using namespace std;

random_device rd;  //Will be used to obtain a seed for the random number engine
mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
uniform_int_distribution<> distrib(1, 1000);

vector<int> generadorPuntos(int dimensiones){
    vector<int> punto;
    for (int a = 0; a < dimensiones; ++a)
    {
        int rand = distrib(gen);
        //cout << rand << ' ';
        punto.push_back(rand);
    }
    //cout << '\n';
    return punto;
}
float distanciaEuclidiana(int dimensiones, vector<int> a, vector<int> b){
    int dist = 0;
    for (int i = 0; i < dimensiones; ++i)
    {
        int t = a[i] - b[i];
        dist += (t * t);
    }
    return (sqrt(dist));
}
int main(){
    srand(time(NULL));
    ofstream file;
    file.open("tablas.txt");
    int num_puntos = 20000;
    vector<int> v_dimenciones = {2, 5, 10, 15, 20, 25};
    vector<int> v_time;
    chrono::time_point<std::chrono::high_resolution_clock> start, end;
    for (int j = 0; j < 6; j++){
        start = chrono::high_resolution_clock::now();
        vector<vector<int>> puntos;
        int dimensiones = v_dimenciones[j];
        //cout<<"                      "<< dimensiones<<"                      "<<endl;
        vector<int> distancias;
        int max = 0;
        int min = 500000;
        puntos.push_back(generadorPuntos(dimensiones));
        vector<int> p_ini = puntos[0];
        for (int i = 1; i < num_puntos; i++){
            puntos.push_back(generadorPuntos(dimensiones));
            distancias.push_back(distanciaEuclidiana(dimensiones, p_ini, puntos[i]));
            if (distancias[i - 1] > max){
                max = distancias[i - 1];
            }
            else if (distancias[i - 1] < min){
                min = distancias[i - 1];
            }
        }
        vector<int> tabla(11, 0);
        int razon = max - min;
        for (int i = 1; i < num_puntos; i++){
            double t = (distancias[i - 1] - min) / (razon + 0.0);

            double parteDecimal, parteEntera;
            parteDecimal = modf(t * 10, &parteEntera);

            int pos = (int)parteEntera;
            //cout<< distancias[i-1]<< "  "<< t<< "  "<< pos<<" "<<endl;
            tabla[pos] += 1;
        }

        for (int i = 0; i < 11; i++){
            //cout<< i <<" "<< tabla[i]<<endl;
            file << tabla[i] << " ";
        }
        file << endl;
        // cout<<endl;
        // cout<< "max "<<max<<" min "<<min<<endl;
        puntos.empty();
        distancias.empty();
        end = chrono::high_resolution_clock::now();
        int64_t duration = chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        v_time.push_back(duration);
    }
    for(int i=0;i<v_time.size();i++) {
        cout<<v_dimenciones[i]<<" Dimensiones "<< v_time[i]<<"s "<<endl;
    }
    file.close();
}   