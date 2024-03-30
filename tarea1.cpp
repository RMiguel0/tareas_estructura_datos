#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// variables usadas:
char X; // rey de ton
char K; // rey de sebastian
char R; // reina de sebastian
char P; // peon de sebastian
char A; // alfol de sebastian
char C; // caballo de sebastian
char T; // torre de sebastian

int todos_movimientos[100];

int numero_piezas = 0;
string texto[9];

struct Pieza {
  char simbolo; // Define qué tipo de pieza es y su caracter
  int x, y;     // Su posición dentro del tablero [0, 7] x [0, 7]
};

struct Tablero {
  Pieza *piezas_tablero; // Lista de piezas que tiene el tablero
};

struct Jugadas {
  char Pieza;
  int movimientos[32];
  int *movimientos_finales;
  int tamanio;
};

/*****
*Puntero_del_tipo_Tablero guardar_tablero
******
* Crear un nuevo objeto del tipo "Tablero" al que se le asigna memoria dinámica
según la cantidad de piezas encontadas en el tablero. A las cuales se les asigna
su simbolo y coordenada. Para finalmente retornar un puntero del tablero.
******
* Input:
* int numero_piezas: Cantidad de piezas que hay en el tablero.
* string *texto: es una referencia a la variable texto la cual es un arreglo de
strings donde están almacenados las lineas del archivo.
******
* Returns:
* Retorna un puntero del tipo Tablero, el cual tiene la informacion de cada
pieza y sus respectivas coordenadas.
*****/

Tablero guardar_tablero(int numero_piezas, string *texto) {
  int k = 0; // contador para añadir el numero de piezas
  Tablero tablero;
  tablero.piezas_tablero = new Pieza[numero_piezas];
  for (int y = 1; y < 9; y++) {
    for (int x = 0; x < 8; x++) {
      if (texto[y][x] != '.') {
        tablero.piezas_tablero[k].simbolo = texto[y][x];
        tablero.piezas_tablero[k].x = x;
        tablero.piezas_tablero[k].y = y;
        k++;
      }
    }
  }
  return tablero;
}

Jugadas posibles_jugadas(Pieza *piezas, Tablero *tablero) {
  Jugadas jugadas;
  jugadas.Pieza = piezas->simbolo;
  char comparacion = piezas->simbolo;
  int coords_y = piezas->y * 10;
  int coords_x = piezas->x;
  int pos_actual = coords_x + coords_y;

  int pos_piezas_en_tablero[numero_piezas]; // guarda todas las casillas
                                            // ocupadas en el tablero

  for (int i = 0; i < numero_piezas; i++) {
    if (comparacion != 'X') {
      pos_piezas_en_tablero[i] =
          tablero->piezas_tablero[i].y * 10 + tablero->piezas_tablero[i].x;
    }
  }

  // comparación peón//
  if (comparacion == 'P') {
    cout << comparacion << endl;
    int i = 0;
    int adelante_der = (coords_y - 10) + (coords_x + 1);
    int adelante_izqrd = (coords_y - 10) + (coords_x - 1);

    bool flag2 = false;
    bool flag3 = false;

    for (int d = 0; d < numero_piezas; d++) {
      if (pos_piezas_en_tablero[d] == adelante_der) {
        flag2 = true;
      }
    }

    for (int d = 0; d < numero_piezas; d++) {
      if (pos_piezas_en_tablero[d] == adelante_izqrd) {
        flag3 = true;
      }
    }

    if (coords_x + 1 < 8 && coords_y - 10 > 0 && flag2 == false) {
      jugadas.movimientos[i] = adelante_der;
      i++;
    }
    if (coords_x - 1 > (-1) && coords_y - 10 > 0 && flag3 == false) {
      jugadas.movimientos[i] = adelante_izqrd;
      i++;
    }

    int *lista_definitiva = new int[i];
    int *pointer;
    pointer = lista_definitiva;
    for (int d = 0; d < i; d++) {
      lista_definitiva[d] = jugadas.movimientos[d];
      cout << lista_definitiva[d] << endl;
    }
    jugadas.movimientos_finales = pointer;
    jugadas.tamanio = i;
  }
  // comparación caballo//
  else if (comparacion == 'C') {
    cout << comparacion << endl;
    int i = 0;
    int t_izq = (coords_y - 20) + (coords_x - 1);
    int t_der = (coords_y - 20) + (coords_x + 1);
    int adelante_izqrd = (coords_y - 10) + (coords_x - 2);
    int adelante_der = (coords_y - 10) + (coords_x + 2);
    int abajo_der = (coords_y + 10) + (coords_x + 2);
    int abajo_izqrd = (coords_y + 10) + (coords_x - 2);
    int j_izqrd = (coords_y + 20) + (coords_x - 1); // aqui
    int j_der = (coords_y + 20) + (coords_x + 1);
    if (coords_x - 1 > (-1) && coords_y - 20 > 0) {
      jugadas.movimientos[i] = t_izq;
      i++;
    }
    if (coords_x + 1 < 8 && coords_y - 20 > 0) {
      jugadas.movimientos[i] = t_der;
      i++;
    }
    if (coords_x - 2 > (-1) && coords_y - 10 > 0) {
      jugadas.movimientos[i] = adelante_izqrd;
      i++;
    }
    if (coords_x + 2 < 8 && coords_y - 10 > 0) {
      jugadas.movimientos[i] = adelante_der;
      i++;
    }
    if (coords_x + 2 < 8 && coords_y + 10 <= 80) {
      jugadas.movimientos[i] = abajo_der;
      i++;
    }
    if (coords_x - 2 > (-1) && coords_y + 10 <= 80) {
      jugadas.movimientos[i] = abajo_izqrd;
      i++;
    }
    if (coords_x - 1 > (-1) && coords_y + 20 <= 80) {
      jugadas.movimientos[i] = j_izqrd;
      i++;
    }
    if (coords_x + 1 < 8 && coords_y + 20 <= 80) {
      jugadas.movimientos[i] = j_der;
      i++;
    }
    int *lista_definitiva = new int[i];
    int *pointer;
    pointer = lista_definitiva;
    cout << i << endl;
    for (int d = 0; d < i; d++) {
      lista_definitiva[d] = jugadas.movimientos[d];
      cout << lista_definitiva[d] << endl;
    }
    jugadas.movimientos_finales = pointer;
    jugadas.tamanio = i;
  }
  // comparación Rey Ton//
  else if (comparacion == 'X') {
    cout << comparacion << endl;
    int i = 0;
    int adelante = pos_actual - 10;
    int atras = pos_actual + 10;
    int derecha = pos_actual + 1;
    int izquierda = pos_actual - 1;
    int adelante_izq = (coords_y - 10) + (coords_x - 1);
    int adelante_der = (coords_y - 10) + (coords_x + 1);
    int atras_izq = (coords_y + 10) + (coords_x - 1);
    int atras_der = (coords_y + 10) + (coords_x + 1);
    if (coords_y - 10 > 0) {
      jugadas.movimientos[i] = adelante;
      i++;
    }
    if (coords_y + 10 <= 80) {
      jugadas.movimientos[i] = atras;
      i++;
    }
    if (coords_x + 1 < 8) {
      jugadas.movimientos[i] = derecha;
      i++;
    }
    if (coords_x - 1 > (-1)) {
      jugadas.movimientos[i] = izquierda;
      i++;
    }
    if (coords_x - 1 > (-1) && coords_y - 10 > 0) {
      jugadas.movimientos[i] = adelante_izq;
      i++;
    }
    if (coords_x + 1 < 8 && coords_y - 10 > 0) {
      jugadas.movimientos[i] = adelante_der;
      i++;
    }
    if (coords_x - 1 > (-1) && coords_y + 10 <= 80) {
      jugadas.movimientos[i] = atras_izq;
      i++;
    }
    if (coords_x + 1 < 8 && coords_y + 10 <= 80) {
      jugadas.movimientos[i] = atras_der;
      i++;
    }
    int *lista_definitiva = new int[i];
    int *pointer;
    pointer = lista_definitiva;
    for (int d = 0; d < i; d++) {
      lista_definitiva[d] = jugadas.movimientos[d];
      cout << lista_definitiva[d] << endl;
    }
    jugadas.movimientos_finales = pointer;
    jugadas.tamanio = i;
  }
  // comparacion Torre//
  else if (comparacion == 'T') {
    cout << comparacion << endl;
    int k = 0;
    int espacios_izq =
        abs(coords_y - pos_actual); // determina la cantidad de espacios que hay
                                    // a la izquierda de la torre.
    int espacios_der = abs(coords_x - 7); // determina la cantidad de espacios
                                          // que hay a la derecha de la torre.
    int espacios_arriba =
        ((coords_y - 10) /
         10); // determina la cantidad de espacios que hay arriba de la torre.
    int espacios_abajo =
        (80 - coords_y) /
        10; // determina la cantidad de espacios que hay abajo de la torre.
    bool flag_T = false;

    for (int i = 1; i <= espacios_izq; i++) {
      for (int d = 0; d < numero_piezas; d++) {
        if (pos_actual - i == pos_piezas_en_tablero[d]) {
          flag_T = true;
          break;
        }
      }
      if (coords_x - 1 > (-1) && flag_T == false) {
        jugadas.movimientos[k] = pos_actual - i;
        k++;
      }
    }
    flag_T = false;

    for (int i = 1; i <= espacios_der; i++) {
      for (int d = 0; d < numero_piezas; d++) {
        if (pos_actual + i == pos_piezas_en_tablero[d]) {
          flag_T = true;
          break;
        }
      }
      if (coords_x + 1 < 8 && flag_T == false) {
        jugadas.movimientos[k] = pos_actual + i;
        k++;
      }
    }
    flag_T = false;

    for (int i = 1; i <= espacios_arriba; i++) {
      for (int d = 0; d < numero_piezas; d++) {
        if (pos_actual - 10 == pos_piezas_en_tablero[d]) {
          flag_T = true;
          break;
        }
      }
      if (coords_y - 10 > 0 && flag_T == false) {
        jugadas.movimientos[k] = pos_actual - (i * 10);
        k++;
      }
    }
    flag_T = false;

    for (int i = 1; i <= espacios_abajo; i++) {
      for (int d = 0; d < numero_piezas; d++) {
        if (pos_actual + 10 == pos_piezas_en_tablero[d]) {
          flag_T = true;
          break;
        }
      }
      if (coords_y + 10 > 0 && flag_T == false) {
        jugadas.movimientos[k] = pos_actual + (i * 10);
        k++;
      }
    }
    int *lista_definitiva = new int[k];
    int *pointer;
    pointer = lista_definitiva;
    for (int d = 0; d < k; d++) {
      lista_definitiva[d] = jugadas.movimientos[d];
      cout << lista_definitiva[d] << endl;
    }
    jugadas.movimientos_finales = pointer;
    jugadas.tamanio = k;
  }
  // comparación Alfil//
  else if (comparacion == 'A') {
    cout << comparacion << endl;
    int k = 0;
    int aumentador_x = 1;
    int aumentador_y = 10;
    int contador_externo = 0;

    for (int i = 0; i < 4; i++) {
      int contador_x = coords_x;
      int contador_y = coords_y;
      bool flag = true;

      while (flag == true) {
        contador_x += aumentador_x;
        contador_y += aumentador_y;
        int posible_movimiento = contador_y + contador_x;
        bool flag2 = false;

        for (int d = 0; d < numero_piezas; d++) {
          if (pos_piezas_en_tablero[d] == posible_movimiento) {
            flag2 = true;
          }
        }

        if (posible_movimiento < 90 && contador_x <= 7 &&
            posible_movimiento >= 0 && contador_x >= 0 && flag2 == false) {
          jugadas.movimientos[k] = contador_y + contador_x;
          k++;
        } else {
          flag = false;
        }
      }

      if (contador_externo == 0) {
        aumentador_x *= (-1);
      } else if (contador_externo == 1) {
        aumentador_y *= (-1);
      } else if (contador_externo == 2) {
        aumentador_x *= (-1);
      }
      contador_externo++;
    }
    int *lista_definitiva = new int[k];
    int *pointer;
    pointer = lista_definitiva;
    for (int d = 0; d <= k; d++) {
      lista_definitiva[d] = jugadas.movimientos[d];
      cout << lista_definitiva[d] << endl;
    }
    jugadas.movimientos_finales = pointer;
    jugadas.tamanio = k;
  }
  // comparacion Reina//
  else if (comparacion == 'R') {
    cout << comparacion << endl;
    int k = 0;
    int espacios_izq =
        abs(coords_y - pos_actual); // determina la cantidad de espacios que hay
                                    // a la izquierda de la torre.
    int espacios_der = abs(coords_x - 7); // determina la cantidad de espacios
                                          // que hay a la derecha de la torre.
    int espacios_arriba =
        ((coords_y - 10) /
         10); // determina la cantidad de espacios que hay arriba de la torre.
    int espacios_abajo =
        (80 - coords_y) /
        10; // determina la cantidad de espacios que hay abajo de la torre.
    bool flag_T = false;

    for (int i = 1; i <= espacios_izq; i++) {
      for (int d = 0; d < numero_piezas; d++) {
        if (pos_actual - i == pos_piezas_en_tablero[d]) {
          flag_T = true;
          break;
        }
      }
      if (coords_x - 1 > (-1) && flag_T == false) {
        jugadas.movimientos[k] = pos_actual - i;
        k++;
      }
    }
    flag_T = false;

    for (int i = 1; i <= espacios_der; i++) {
      for (int d = 0; d < numero_piezas; d++) {
        if (pos_actual + i == pos_piezas_en_tablero[d]) {
          flag_T = true;
          break;
        }
      }
      if (coords_x + 1 < 8 && flag_T == false) {
        jugadas.movimientos[k] = pos_actual + i;
        k++;
      }
    }
    flag_T = false;

    for (int i = 1; i <= espacios_arriba; i++) {
      for (int d = 0; d < numero_piezas; d++) {
        if (pos_actual - 10 == pos_piezas_en_tablero[d]) {
          flag_T = true;
          break;
        }
      }
      if (coords_y - 10 > 0 && flag_T == false) {
        jugadas.movimientos[k] = pos_actual - (i * 10);
        k++;
      }
    }
    flag_T = false;

    for (int i = 1; i <= espacios_abajo; i++) {
      for (int d = 0; d < numero_piezas; d++) {
        if (pos_actual + 10 == pos_piezas_en_tablero[d]) {
          flag_T = true;
          break;
        }
      }
      if (coords_y + 10 > 0 && flag_T == false) {
        jugadas.movimientos[k] = pos_actual + (i * 10);
        k++;
      }
    }

    int aumentador_x = 1;
    int aumentador_y = 10;
    int contador_externo = 0;

    for (int i = 0; i < 4; i++) {
      int contador_x = coords_x;
      int contador_y = coords_y;
      bool flag = true;

      while (flag == true) {
        contador_x += aumentador_x;
        contador_y += aumentador_y;
        int posible_movimiento = contador_y + contador_x;
        bool flag2 = false;

        for (int d = 0; d < numero_piezas; d++) {
          if (pos_piezas_en_tablero[d] == posible_movimiento) {
            flag2 = true;
          }
        }

        if (posible_movimiento < 90 && contador_x <= 7 &&
            posible_movimiento >= 0 && contador_x >= 0 && flag2 == false) {
          jugadas.movimientos[k] = contador_y + contador_x;
          k++;
        } else {
          flag = false;
        }
      }

      if (contador_externo == 0) {
        aumentador_x *= (-1);
      } else if (contador_externo == 1) {
        aumentador_y *= (-1);
      } else if (contador_externo == 2) {
        aumentador_x *= (-1);
      }
      contador_externo++;
    }
    int *lista_definitiva = new int[k];
    int *pointer;
    pointer = lista_definitiva;
    for (int d = 0; d < k; d++) {
      lista_definitiva[d] = jugadas.movimientos[d];
      cout << lista_definitiva[d] << endl;
    }
    jugadas.movimientos_finales = pointer;
    jugadas.tamanio = k;
  }
  // comparación Rey de Sebas.
  else if (comparacion == 'K') {
    cout << comparacion << endl;
    int i = 0;
    int adelante = pos_actual - 10;
    int atras = pos_actual + 10;
    int derecha = pos_actual + 1;
    int izquierda = pos_actual - 1;
    int adelante_izq = (coords_y - 10) + (coords_x - 1);
    int adelante_der = (coords_y - 10) + (coords_x + 1);
    int atras_izq = (coords_y + 10) + (coords_x - 1);
    int atras_der = (coords_y + 10) + (coords_x + 1);
    if (coords_y - 10 > 0) {
      jugadas.movimientos[i] = adelante;
      i++;
    }
    if (coords_y + 10 <= 80) {
      jugadas.movimientos[i] = atras;
      i++;
    }
    if (coords_x + 1 < 8) {
      jugadas.movimientos[i] = derecha;
      i++;
    }
    if (coords_x - 1 > (-1)) {
      jugadas.movimientos[i] = izquierda;

      i++;
    }
    if (coords_x - 1 > (-1) && coords_y - 10 > 0) {
      jugadas.movimientos[i] = adelante_izq;
      i++;
    }
    if (coords_x + 1 < 8 && coords_y - 10 > 0) {
      jugadas.movimientos[i] = adelante_der;
      i++;
    }
    if (coords_x - 1 > (-1) && coords_y + 10 <= 80) {
      jugadas.movimientos[i] = atras_izq;
      i++;
    }
    if (coords_x + 1 < 8 && coords_y + 10 <= 80) {
      jugadas.movimientos[i] = atras_der;
      i++;
    }
    int *lista_definitiva = new int[i];
    int *pointer;
    pointer = lista_definitiva;
    for (int d = 0; d < i; d++) {
      lista_definitiva[d] = jugadas.movimientos[d];
      cout << lista_definitiva[d] << endl;
    }
    jugadas.movimientos_finales = pointer;
    jugadas.tamanio = i;
  }
  return jugadas;
}

bool tableroEnJaqueMate(Tablero *tablero, int numero_piezas,
                        Jugadas *jugadas_piezas) {
  bool jaque_mate = false;
  char comparacion = 'X';
  int tamanio_ton = 0;
  int tamanio_sebas = 0;
  int pos_ton = 0;
  int posiciones_sebas[numero_piezas-1];

  int d=0;
  for (int i = 0; i < numero_piezas; i++) {
    if (comparacion == jugadas_piezas[i].Pieza) {
      pos_ton = i;
      tamanio_ton = jugadas_piezas[i].tamanio;
    } else {
      //cout << d << endl;
      posiciones_sebas[d] = d;
      tamanio_sebas += jugadas_piezas[i].tamanio;
    }
    d++;
  }


  int jugadas_ton[tamanio_ton];
  int jugadas_sebas[tamanio_sebas];

  int m = 0;
  for (int i = 0; i < tamanio_ton; i++) {
    cout <<"es jugada: "<< jugadas_piezas[pos_ton].movimientos_finales[i] << " en esta posicion: "<< m << endl;
    jugadas_ton[m] = jugadas_piezas[pos_ton].movimientos_finales[i];
    m++;
  }

  int num_jugadas_sebas = tamanio_sebas;

  int j = 0;
  for (int i = 0; i <= numero_piezas-1; i++) {
    int ubicacion = posiciones_sebas[i];
    for(int h = 0; h < jugadas_piezas[ubicacion].tamanio; h++){
      jugadas_sebas[j] = jugadas_piezas[ubicacion].movimientos_finales[h];
      j++;
    }
  }

  int coincidencias = 0;

  for (int a = 0; a < num_jugadas_sebas; a++){
    for (int b = 0; b < tamanio_ton; b++){
      if (jugadas_ton[b] == jugadas_sebas[a]){
        coincidencias++;
        jugadas_ton[b] = -1;
      }
    }
  }

  if (coincidencias == tamanio_ton) {
    jaque_mate = true;
  }
  return jaque_mate;
}

int main() {
  cout << "Wenas" << endl;
  ifstream archivo("tablero.txt");
  for (int i = 0; i < 9; i++) {
    getline(archivo, texto[i]);
  }
  archivo.close();

  numero_piezas = stoi(texto[0]);
  Tablero tablero = guardar_tablero(numero_piezas, texto);

  Jugadas jugadas_piezas[numero_piezas];
  for (int i = 0; i < numero_piezas; i++) {
    Pieza mini_pieza = tablero.piezas_tablero[i];
    jugadas_piezas[i] = posibles_jugadas(&mini_pieza, &tablero);
  }

  bool veredicto = tableroEnJaqueMate(&tablero, numero_piezas, jugadas_piezas);

  if (veredicto) {
    cout << "Si" << endl;
  } else {
    cout << "No" << endl;
  }

  delete[] tablero.piezas_tablero;

  return 0;
}