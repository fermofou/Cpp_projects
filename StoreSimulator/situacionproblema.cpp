#include <iostream>
#include <string.h>

using namespace std;

//Clase Comida
class Comida {
private:
  string fabricante;
  int cantidad;
  double precio;
  double subtotal;

public:
  Comida();
  Comida(string, int, double);
  
  void muestraComida();
  void subtotalComida();
};

//Clase Bebida
class Bebida {
private:
  string fabricante;
  int litros;
  double precio;
  double subtotal;

public:
  Bebida();
  Bebida(string, int, double);

  void muestraBebida();
  void subtotalBebida();
};

//Clase Envio
class Envio {
private:
  string repartidor;
  double precio;

public:
  Envio();
  Envio(string, double);
  void muestraEnvio();
};

//Clase Tienda (junta las otras clases)
class Tienda {
private:
  string cliente;
  Comida plato;
  Comida pago_com;
  Bebida vaso;
  Bebida pago_beb;
  Envio rappi;
  int propina;
  string encuesta;
  double total;

public:
  Tienda();
  Tienda(string, Comida, Comida, Bebida, Bebida, Envio, int, string);

  void muestraTienda();
  void calculaTotal();
};

// Definimos el constructor por default de comida
Comida::Comida() {
  fabricante = "caramelos";
  cantidad = 1;
  precio = 15.34;
}

// Definimos el constructor con todos los parametros
Comida::Comida(string _fabricante, int _cantidad, double _precio) {
  fabricante = _fabricante;
  cantidad = _cantidad;
  precio = _precio;

}

// Definimos metodos
void Comida::muestraComida() {
  cout << "Plato: " << fabricante << ", serán " << cantidad << ", cuesta $" << precio << "" << endl;
}

void Comida::subtotalComida(){
  subtotal = cantidad * precio;
  cout << subtotal << endl;
}

// Definimos el constructor por default de bebida
Bebida::Bebida() {
  fabricante = "coca";
  litros = 15;
  precio = 16.68;
}

// Definimos el constructor con todos los parametros
Bebida::Bebida(string _fabricante, int _litros, double _precio) {
  fabricante = _fabricante;
  litros = _litros;
  precio = _precio;
}

// Definimos metodos
void Bebida::muestraBebida() {
  cout << "Bebida: " << fabricante << ", serán " << litros << " litros, cada litro cuesta $" << precio << "" << endl;
}

void Bebida::subtotalBebida(){
  subtotal = litros * precio;
  cout << subtotal << endl;
}

// Definimos el constructor por default de envio
Envio::Envio() {
  repartidor = "Juan";
  precio = 30.61;
}

// Definimos el constructor con todos los parametros
Envio::Envio(string _repartidor, double _precio) {
  repartidor = _repartidor;
  precio = _precio;
}

// Definimos el metodo muestraEnvio
void Envio::muestraEnvio() {
  cout << "El envió sera hecho por " << repartidor << ", costará " << precio << endl;
}
// Ahora definiremos los metodos de la clase Tienda
Tienda::Tienda() {
  cliente = "fermofou";
  Comida plato("sabritas", 1, 15.67);
  Bebida vaso("dr pepper", 3, 17.43);
  Envio rappi("Juan", 50.23);
  propina = 10;
  encuesta = "me gusto el servicio, al fin tienen envio a domicilio!";
}


// Constructor con todos los parametros
Tienda::Tienda(string _cliente, Comida _plato, Comida _pago_com, Bebida _vaso, Bebida _pago_beb, Envio _rappi, int _propina, string _encuesta) {
  cliente = _cliente;
  plato = _plato;
  pago_com= _pago_com;
  pago_beb= _pago_beb;
  vaso = _vaso;
  rappi = _rappi;
  propina = _propina;
  encuesta = _encuesta;
}

void Tienda::muestraTienda() {
  cout << "Cliente: " << cliente << endl;
  plato.muestraComida();
  vaso.muestraBebida();
  cout << "Entrega: ";
  rappi.muestraEnvio();
  cout << "Propina: " << propina << endl;
  cout << "Encuesta: " << encuesta << endl << endl;
}

void Tienda::calculaTotal() {
  double total;
  cout<< "RECIBO DE COMPRA" <<endl;
  cout << "Pago por comida: ";
  pago_com.subtotalComida();
  cout << "Pago por bebidas: ";
  pago_beb.subtotalBebida();
  cout << "Propina: ";
  cout << propina;

};

int main() {
  cout<< endl << "Bienvenidos al nuevo servicio domicilio de la tienda de tu esquina ;) " << endl;
  
  string ped_com, ped_beb;
  int ctdad_com, ctdad_beb;
  double precio=0.0;
  cout << "Ingrese su nombre: "; 
  string nombre;
  cin >> nombre;
  cout << "Ingrese lo que desea comer: "; 
  cin >> ped_com;

  cout << "Ingrese la cantidad: "; 
  cin >> ctdad_com;
  
  cout << "Ingrese lo que desea beber: "; 
  cin >> ped_beb;

  cout << "Ingrese la cantidad: "; 
  cin >> ctdad_beb;

  
  if (ped_com == "sabritas")
    precio = 15.67;
  else if (ped_com == "gomitas")
    precio = 10.05;
  else if (ped_com == "galletas")
    precio = 16.88;
  else if (ped_com == "cacahuates")
    precio = 13.31;
  else if (ped_com == "barritas")
    precio = 17.2;
  else
    precio = 15.34;
  
  Comida plato1(ped_com, ctdad_com, precio);

  precio = 0.00;
  if (ped_beb == "dr pepper")
    precio = 19.33;
  else if (ped_beb == "jugo")
    precio = 26.97;
  else if (ped_beb == "te")
    precio = 15.31;
  else if (ped_beb == "agua")
    precio = 8.12;
  else if (ped_beb == "limonada")
    precio = 25.04;
  else
    precio = 17.54;
  
  Bebida vaso1(ped_beb, ctdad_beb, precio);
  
  Envio rappi1("Juan", 50.23);

  Tienda cliente1(nombre, plato1, plato1, vaso1, vaso1, rappi1, 10, "excelente servicio!"), cliente2;
  
  cout << endl << "Los datos de la comida son: " << endl;
  plato1.muestraComida();
  cout << endl << "Los datos de la bebida  son: " << endl;
  vaso1.muestraBebida();
  cout << endl << "Los datos del envio son: " << endl;
  rappi1.muestraEnvio();

  cout << endl << "Los datos del pedido completo son: " << endl;
  cliente1.muestraTienda();
  cliente2.muestraTienda();

  cout << endl;
  cout<<"Cliente 1: " << endl;
  cliente1.calculaTotal();

  cout << endl << endl;
  cout << "Cliente 2: " << endl;
  cliente2.calculaTotal();
  
  return 0;
}