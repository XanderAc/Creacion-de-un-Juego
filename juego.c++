#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime> // agregamos un temporizador 
#include <thread> // Para agregar una pausa de varios segundos antes de ejecutar el otro pedaso de codigo
#include <cctype> // Para tolower
using namespace std;

// Constantes
const int MAX_INTENTOS = 6;

struct Jugador {
    string nombre;
    int puntaje;
};

//Funciones para el menu 
int jugar(vector<Jugador>& jugadores);
void mostrarPuntajes(vector<Jugador>& jugadores);
void limpiarPantalla();
int mostrarCreditos();

// Funciones para el juego 
void agregarJugador(vector<Jugador>& jugadores);
void Ahorcado(vector<Jugador>& jugadores);
void convertirAMinusculas(string& texto);
void dibujarAhorcado(int intentosRestantes);
void puntaje(int vida,vector<Jugador>& jugadores);


int main() {
    int opcion;
    vector<Jugador> jugadores;

    do {
        limpiarPantalla();
        cout << "\n:::Menu:::\n";
        cout << "1. Jugar\n";
        cout << "2. Puntajes\n";
        cout << "3. Salir\n";
        cout << "4. Creditos\n";
        cout << "Ingrese su opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                jugar(jugadores);
                break;
            case 2:
                mostrarPuntajes(jugadores);
                break;
            case 3:
                cout << "Gracias por jugar. ¡Hasta luego!\n";
                return 0;
            case 4:
                mostrarCreditos();
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 3);

    return 0;
}

int mostrarCreditos(){
    cout << "Creditos:\n";
    cout << "Antony Contreras\n";
    cout << "Leonardo Alava\n";
    cout << "Sebastian Pazmino\n";
    this_thread::sleep_for(chrono::seconds(2));
    return 0; 
}

int jugar(vector<Jugador>& jugadores) {
    string opc;
    int seleccion;
    cout << "Jugar con jugador existente? (Si/No): ";
    cin >> opc;
    // Convierte opc a minúsculas para que no importe si el usuario escribe "Si" o "si"
    convertirAMinusculas(opc);

    if (opc == "si") {
        if (jugadores.empty()) {// El método empty devuelve True si tiene algún valor, en caso contrario devuelve False
            cout << "No hay jugadores existentes para jugar." << endl;
            cout << "Elija otra opcion." << endl;
            //Se agrega una pausa de dos segundos antes de retornar el valor de 1
            this_thread::sleep_for(chrono::seconds(2));
            return 1;
        } else {
            cout << "Lista de usuarios que ya existen:" << endl;
            for (int i = 0; i < jugadores.size(); i++) {
                cout << i + 1 << ". Nombre: " << jugadores[i].nombre << endl;
            }
            cout << "Seleccione el numero del jugador con el que desea jugar: ";
            cin >> seleccion;
            if (seleccion >= 1 && seleccion <= jugadores.size()) {
                cout << "Ha seleccionado jugar con " << jugadores[seleccion - 1].nombre << "." << endl;
                Ahorcado(jugadores);
            } else {
                cout << "Seleccion no valida." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                return 2;
            }
        }
    } else if (opc == "no") {
        cout << "Ha seleccionado jugar sin un jugador existente." << endl;
        agregarJugador(jugadores);
        Ahorcado(jugadores);
    } else {
        cout << "Opcion no valida." << endl;
        this_thread::sleep_for(chrono::seconds(2));
        return 4;
    }

    return 0;
}

void Ahorcado(vector<Jugador>& jugadores) {
    int nA, vida = MAX_INTENTOS;
    char letra;
    string palabras[] = {"programacion", "segunda", "aso", "cafeteria", "pantera"}; // -> aqui van las palabras de la facultad
    srand(static_cast<unsigned int>(time(NULL)));
    nA = rand() % 5;// Genera aleatoriamente un número del 0 hasta la cantidad de palabras que tenemos
    string palabraAleatoria = palabras[nA];
    string adivinarPalabra(palabraAleatoria.length(), '_');
    dibujarAhorcado(0);
    this_thread::sleep_for(chrono::seconds(2));
    while (vida > 0) {
        limpiarPantalla();
        cout << "Palabra a adivinar: " << adivinarPalabra << endl;
        cout << "Numero de intentos para adivinar la palabra: " << vida << endl;
        cout << "Ingrese una letra en minusculas: ";
        cin >> letra;
        
        bool letraAdivinar = false;
        for (int i = 0; i < palabraAleatoria.length(); i++) {
            if (palabraAleatoria[i] == letra) {
                adivinarPalabra[i] = letra;
                letraAdivinar = true;
            }
        }
        if (!letraAdivinar) {
            vida--;
            dibujarAhorcado(MAX_INTENTOS - vida); // Dibuja el ahorcado
            cout << "Letra incorrecta. Pierdes una vida." << endl;
            this_thread::sleep_for(chrono::seconds(2));
        } else {
            cout << "La letra es correcta." << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
        if (adivinarPalabra == palabraAleatoria) {
            limpiarPantalla();
            cout << "¡Ganaste! La palabra es: " << palabraAleatoria << endl;
            this_thread::sleep_for(chrono::seconds(1));
            break;
        }
    }
    if (vida == 0) {
        limpiarPantalla();
        cout << "¡Haz perdido! Intentalo de nuevo." << endl;
        cout << "La palabra era: " << palabraAleatoria;
        this_thread::sleep_for(chrono::seconds(5));
    }
    puntaje(vida,jugadores);
}

//Funcion que dibuja el ahorcado 
void dibujarAhorcado(int intentosRestantes) {
    cout << endl;
    cout << "  +---+" << endl;
    cout << "  |   |" << endl;

    switch (intentosRestantes) {
        case 0:
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            break;
        case 1:
            cout << "  O   |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            break;
        case 2:
            cout << "  O   |" << endl;
            cout << "  |   |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            break;
        case 3:
            cout << "  O   |" << endl;
            cout << " /|   |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            break;
        case 4:
            cout << "  O   |" << endl;
            cout << " /|\\  |" << endl;
            cout << "      |" << endl;
            cout << "      |" << endl;
            break;
        case 5:
            cout << "  O   |" << endl;
            cout << " /|\\  |" << endl;
            cout << " /    |" << endl;
            cout << "      |" << endl;
            break;
        case 6:
            cout << "  O   |" << endl;
            cout << " /|\\  |" << endl;
            cout << " / \\  |" << endl;
            cout << "      |" << endl;
            break;
    }
    cout << "_______" << endl;
    cout << endl;
}

void convertirAMinusculas(string& texto) {
    transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
}

void agregarJugador(vector<Jugador>& jugadores) {
    Jugador jugador;// -> Se inicializa la estructura
    cout << "Ingrese el nombre del jugador: ";
    cin >> jugador.nombre;
    jugador.puntaje = 0;// -> Por defecto el puntaje de un jugador recién agregado será cero
    jugadores.push_back(jugador);// -> Se guarda al nuevo jugador en la estructura principal
    cout << "Jugador agregado con exito." << endl;
}

void puntaje(int vida, vector<Jugador>& jugadores) {
    switch (vida) {
        case 6:
            jugadores.back().puntaje = 100; // Asignar puntaje al último jugador agregado
            break;
        case 5:
            jugadores.back().puntaje = 75;
            break;
        case 4:
            jugadores.back().puntaje = 60;
            break;
        case 3:
            jugadores.back().puntaje = 45;
            break;
        case 2:
            jugadores.back().puntaje = 30;
            break;
        case 1:
            jugadores.back().puntaje = 15;
            break;
        case 0:
            jugadores.back().puntaje = 0;
            break;
    }
}

// Esta función permite mostrar los puntajes de todos los jugadores
void mostrarPuntajes(vector<Jugador>& jugadores) {
    if (jugadores.empty()) {
        cout << "No hay jugadores registrados." << endl;
    } else {
        cout << "El puntaje de los jugadores es el siguiente:" << endl;
        sort(jugadores.begin(), jugadores.end(), [](const Jugador& a, const Jugador& b) {
            return a.puntaje > b.puntaje;
        });// La función sort ordena el arreglo, en este caso queremos que se ordene de mayor a menor, (Utilicé una función lambda para que compare el puntaje de ambos jugadores y lo utilice como argumento para ordenar)
        for (const Jugador& jugador : jugadores) {// Iteramos para mostrar los puntajes de cada jugador
            cout << "Nombre: " << jugador.nombre << ", Puntaje: " << jugador.puntaje << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }
}

void limpiarPantalla() {
    if (system("cls") == -1) {
        cout << "Error al limpiar la pantalla." << endl;
    }
}
