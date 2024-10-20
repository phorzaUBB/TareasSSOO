// Importar librerias
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <vector>
#include <mutex>

// Definir el espacio de nombres
using namespace std;

// Vector global para almacenar la llegada de los autos
vector<int> posiciones;
// Mutex para proteger el acceso a la consola
mutex mtx;
// Mutex para proteger el acceso al vector de posiciones
mutex mtx2;


// Funcion para simular la carrera de los autos
void carrera(int id, int distancia_carrera){
    // Generar numeros aleatorios
    random_device rd;
    mt19937 gen(rd());
    // Definir el rango de los numeros aleatorios de avance
    uniform_int_distribution<> dism(1, 10);
    // Definir el rango de los numeros aleatorios de tiempo de descanso
    uniform_int_distribution<> dist(100, 500);

    // Distancia recorrida por el auto
    int distancia_recorrida = 0;

    // Bucle que simula el avance del auto
    while (distancia_recorrida < distancia_carrera) {
        // Avnce y tiempo de descanso aleatorio
        int avance = dism(gen);
        int tiempo_descanso = dist(gen);

        // Simular el tiempo de descanso en el hilo
        this_thread::sleep_for(chrono::milliseconds(tiempo_descanso));

        // Actualizar la distancia recorrida
        distancia_recorrida += avance;

        // Asegurar que la distancia recorrida no sea mayor a la distancia de la carrera
        if (distancia_recorrida > distancia_carrera) {
            distancia_recorrida = distancia_carrera;
        }

        // Bloaquear mutex para imprimir por consola
        mtx.lock();
        cout << "Auto" << id << " avanza " << avance << " metros (total: " << distancia_recorrida << " metros)" << endl;
        mtx.unlock();

        // Verificar si el auto llega a la meta
        if (distancia_recorrida >= distancia_carrera) {
            // Bloquear mutex para actualizar el vector de posiciones
            mtx2.lock();
            posiciones.push_back(id);
            int posicion = posiciones.size();
            cout << "Auto" << id << " avanza " << avance << " metros y termina la carrera en el lugar " << posicion << endl;
            mtx2.unlock();
        }
    }
}

int main(int argc, char* argv[]) {
    // Verificar que se ingresen los argumentos correctos
    if (argc != 3) {
        cerr << "Use el comando: " << argv[0] << " <distancia_carrera> <numero_autos>" << endl;
        return 1;
    }

    // Convertir los argumentos a enteros
    int distancia_total = stoi(argv[1]);
    int numero_autos = stoi(argv[2]);

    // Validar los argumentos
    if (distancia_total < 0){
        cerr << "La distancia de la carrera debe ser un numero positivo" << endl;
        return 1;
    } else if (distancia_total == 0){
        cerr << "La distancia de la carrera no puede ser 0" << endl;
        return 1;
    }

    if (numero_autos < 0){
        cerr << "El numero de autos debe ser un numero positivo" << endl;
        return 1;
    } else if (numero_autos == 0){
        cerr << "El numero de autos no puede ser 0" << endl;
        return 1;
    }

    // Declaracion del vector de hilos para los autos
    vector<thread> cars;

    // Crear hilos para cada auto
    for (int i = 0; i < numero_autos; i++) {
        cars.push_back(thread(carrera, i, distancia_total));
    }

    // Esperar a que todos los hilos terminen
    for (auto& car : cars) {
        car.join();
    }

    // Imprimir el orden de llegada de los autos
    cout << "\nOrden de llegada:\n";
    cout << "Lugar\tAuto\n";

    for (size_t i = 0; i < posiciones.size(); i++) {
        cout << i + 1 << "\tAuto" << posiciones[i] << endl;
    }

    // Salir del programa
    return 0;
}