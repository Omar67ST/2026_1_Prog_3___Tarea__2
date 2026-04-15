// test.cpp
#include "core_numeric.cpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using namespace core_numeric;

int main() {
    // Casos válidos
    vector<int> vi{1, 2, 3};
    vector<double> vd{1.0, 2.0, 3.0};

    cout << "----------------------------------" << endl;
    cout << "sum(int): " << sum(vi) << "\n";
    cout << "mean(double): " << mean(vd) << "\n";
    cout << "variance(double): " << variance(vd) << "\n";
    cout << "max(double): " << max(vd) << "\n";
    cout << "----------------------------------" << endl;

    cout << "----------------------------------" << endl;
    //La funcion debe recibirse como parametro template.
    cout << "transform_reduce: "
         << transform_reduce(vd, [](double x){ return x * x; }) << "\n";

    cout << "sum_variadic: " << sum_variadic(1, 2, 3, 4) << "\n";
    cout << "mean_variadic: " << mean_variadic(1.0, 2.0, 3.0, 4.0) << "\n";
    cout << "variance_variadic: " << variance_variadic(1.0, 2.0, 3.0, 4.0) << "\n";
    cout << "max_variadic: " << max_variadic(1.0, 2.7, 0.3, 4.1) << "\n";
    cout << "----------------------------------" << endl;

    // Casos con clases personalizadas
    cout << "----------------------------------" << endl;
    vector<Coordenadas> puntos{{1,2}, {3,4}, {5,6}};
    cout << "sum(Coordenadas): (" << sum(puntos).x << "," << sum(puntos).y << ")\n";
    cout << "mean(Coordenadas): (" << mean(puntos).x << "," << mean(puntos).y << ")\n";
    cout << "max(Coordenadas): (" << max(puntos).x << "," << max(puntos).y << ")\n";
    cout << "----------------------------------" << endl;

    cout << "----------------------------------" << endl;
    vector<Vector3D> vectores{{1,2,3}, {4,5,6}, {7,8,9}};
    cout << "mean(Vector3D): (" << mean(vectores).x << "," << mean(vectores).y << "," << mean(vectores).z << ")\n";
    cout << "----------------------------------" << endl;

    cout << "----------------------------------" << endl;
    vector<Esfera> esferas{{1}, {2}, {3}};
    cout << "sum(Esfera): " << sum(esferas).radio << "\n";
    cout << "mean(Esfera): " << mean(esferas).radio << "\n";
    cout << "variance(Esfera): " << variance(esferas).radio << "\n";
    cout << "max(Esfera): " << max(esferas).radio << "\n";
    cout << "----------------------------------" << endl;

    show_type_info<int>();
    show_type_info<double>();
    cout << "----------------------------------" << endl;
    // Casos que NO deben compilar (comentados) (invalido)
    // vector<string> vs{"Hola", "Mundo"};
    // vector < std :: string > data {"a", "b", "c"};
    // auto v = core_numeric :: max ( data ) ;
    // sum(vs);       // ERROR: string no cumple Addable
    // mean(vs);      // ERROR: string no cumple Divisible
    // variance(vs);  // ERROR: string no cumple Addable/Divisible
    // max(vs);       // ERROR: string no cumple Comparable

    return 0;
}
