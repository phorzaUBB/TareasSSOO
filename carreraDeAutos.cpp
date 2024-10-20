#include <iostream>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>

using namespace std;

void avanzarDistancia(int id, int distanciaM) {
    int distanciaRecorrida = 0;

    // Bucle hasta que el auto haya recorrido la distancia total
    while (distanciaRecorrida < distanciaM) {
        // Generar un avance aleatorio entre 1 y 10 metros
        int recorreDistancia = 1 + rand() % 10;

        // Generar un tiempo de espera aleatorio entre 100 y 500 milisegundos
        int tiempoDetenido = 100 + rand() % 401;

        // Actualizar la distancia recorrida
        distanciaRecorrida += recorreDistancia;

	if((distanciaRecorrida>=distanciaM)){
	cout << "Auto" <<id << " avanza " << recorreDistancia << " metros y termina la carrera\n";
	}else{
        cout << "Auto " << id << " avanza " << recorreDistancia << " metros (total: " << distanciaRecorrida << " metros)\n";

        // Detener el hilo por el tiempo generado
        this_thread::sleep_for(chrono::milliseconds(tiempoDetenido));
   }
 }
}

int main(int argc, char* argv[]) {
    // Convertir los argumentos de la línea de comandos
    int distanciaM = stoi(argv[1]);
    int n = stoi(argv[2]);

    // Inicializar la semilla para los números aleatorios
    srand(time(0));

    // Crear un vector para almacenar los hebras
    vector<thread> hebras(n);

    // Crear cada hilo y asignarlo a la función avanzarDistancia
    for (int i = 0; i < n; i++) {
        hebras[i] = thread(avanzarDistancia, i + 1, distanciaM);
    }

    // Esperar a que todos las hebras terminen
    for (int i = 0; i < n; i++) {
        hebras[i].join();
    }

    return 0;
}

