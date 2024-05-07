#include <iostream>
#include <string>
#include <cstdlib> 
#include <ctime>   

using namespace std;

class Lancha {
private:
    string nombre;
    int velocidad;
    int distanciaRecorrida;
    int nitro;

public:
    // Constructor con nombre
    Lancha(string n) {
        nombre = n;
        velocidad = 0;
        distanciaRecorrida = 0;
        nitro = 1;
    }

    // Getter y Setter para Nombre
    void setNombre(string n) {
        nombre = n;
    }

    string getNombre() {
        return nombre;
    }

    // Getter y Setter para Velocidad
    void setVelocidad(int v) {
        velocidad = v;
    }

    int getVelocidad() {
        return velocidad;
    }

    // Getter y Setter para Distancia Recorrida
    void setDistanciaRecorrida(int d) {
        distanciaRecorrida = d;
    }

    int getDistanciaRecorrida() {
        return distanciaRecorrida;
    }

    // Getter y Setter para Nitro
    void setNitro(int n) {
        nitro = n;
    }

    int getNitro() {
        return nitro;
    }

    // Método para lanzar el dado y actualizar la velocidad
    void lanzarDado() {
        int dado = rand() % 6 + 1; // "Obtener entre 1 y 6 puntos" (+1 para evitar número 0)
        velocidad += dado;
    }

    // Método para calcular distancia recorrida en un turno
    void calcularDistanciaRecorrida() {
        distanciaRecorrida += velocidad * 100;
    }

    // Método para usar el nitro
    void usarNitro() {
        velocidad *= 2; // Aumentar velocidad al utilizar nitro
        nitro = 0; // Desactivar nitro después de usarlo
    }
};

void introduccion(Lancha& lancha1, Lancha& lancha2) {
    cout << "¡Bienvenido a la carrera de lanchas acuáticas!" << endl;
    cout << "Por favor, introduce el nombre de tu lancha: ";
    string nombre1;
    cin >> nombre1;
    lancha1 = Lancha(nombre1);
    cout << "¡Prepárate para la carrera!" << endl << endl;
}

int lanzarDado() {
    int resultado = rand() % 6 + 1;
    cout << "Ha salido un " << resultado << " en el dado." << endl;
    return resultado;
}

void mostrarEstado(Lancha& lancha1, Lancha& lancha2, int turno) {
    cout << "Turno " << turno << ":\n";
    cout << "Estado de las lanchas:\n";
    cout << lancha1.getNombre() << " - Velocidad: " << lancha1.getVelocidad() << ", Distancia Recorrida: " << lancha1.getDistanciaRecorrida() << endl;
    cout << lancha2.getNombre() << " - Velocidad: " << lancha2.getVelocidad() << ", Distancia Recorrida: " << lancha2.getDistanciaRecorrida() << endl;
}

int main() {
    srand(time(0)); // Inicializamos la semilla del generador de números aleatorios

    // Creamos objetos de la clase Lancha
    Lancha lanchaUsuario("");
    Lancha lanchaMaquina("Maquina");

    // Introducción del juego y solicitud del nombre de la lancha del usuario
    introduccion(lanchaUsuario, lanchaMaquina);

    // Variable para controlar si se ha utilizado el nitro
    bool nitroUtilizado = false;

    // Gestión de los cinco turnos de la carrera
    for (int turno = 1; turno <= 5; turno++) {
        // Lanzamiento del dado y actualización de la velocidad para ambas lanchas
        int dadoUsuario = lanzarDado();
        int dadoMaquina = lanzarDado();

        lanchaUsuario.setVelocidad(0); // Reiniciamos la velocidad del usuario en cada turno
        lanchaMaquina.setVelocidad(0); // Reiniciamos la velocidad de la máquina en cada turno

        lanchaUsuario.lanzarDado();
        lanchaMaquina.lanzarDado();

        // Mostrar estado de las lanchas en este turno
        mostrarEstado(lanchaUsuario, lanchaMaquina, turno);

        // Si no se ha utilizado el nitro aún, preguntar al usuario si desea utilizarlo
        if (!nitroUtilizado && turno > 1) {
            char respuesta;
            cout << "¿Deseas utilizar el nitro en este turno? (S/N): ";
            cin >> respuesta;
            if (toupper(respuesta) == 'S') {
                nitroUtilizado = true; // Marcar que el nitro ha sido utilizado antes de usarlo
                lanchaUsuario.usarNitro();
                cout << "Has utilizado el nitro en este turno." << endl;
            }
        }

        // Calcular la distancia recorrida para ambas lanchas
        lanchaUsuario.calcularDistanciaRecorrida();
        lanchaMaquina.calcularDistanciaRecorrida();
    }

    // Determinar el ganador al final de la carrera
    if (lanchaUsuario.getDistanciaRecorrida() > lanchaMaquina.getDistanciaRecorrida()) {
        cout << "¡Felicidades! ¡Has ganado la carrera!" << endl;
    }
    else if (lanchaUsuario.getDistanciaRecorrida() < lanchaMaquina.getDistanciaRecorrida()) {
        cout << "¡Te ha ganado la máquina! ¡Inténtalo de nuevo!" << endl;
    }
    else {
        cout << "¡Ha habido un empate!" << endl;
    }

    return 0;
}
