#include <Keypad.h>

// Config teclado

const byte FILAS = 4;
const byte COLUMNAS = 4;
char keys[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinesFilas[FILAS] = {9, 8, 7, 6};
byte pinesColumnas[COLUMNAS] = {5, 4, 3, 2};

Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);

char codigoProducto[3];
unsigned int indexCodigoTeclado = 0;

// Pines
const int devolucionesLed = 12;
const int pulsadorMonedas = 13;
const int pulsadorCaida = 11;
const int sensorUPS = A0;
const int LED_Error = 10;
const int refrigerador = A5;
const int sensorTemp = A1;
const int ledMotor1 = A3;
const int ledMotor2 = A4;

// Productos
String nombresProductos[] = {
  "Refresco de cola",
  "Refresco de naranja",
  "Refresco de limón",
  "Zumo",
  "Agua con gas",
  "Agua mineral"
  };

int preciosProductos[] = {  // En centimos

  150,
  150,
  150,
  250,
  125,
  100
};

String codigosProductos[] {

  "A35",
  "A36",
  "A37",
  "A38",
  "A39",
  "A40"
};

// Monedas
unsigned int contadorDevoluciones = 0;
unsigned int precioProducto = 0;
unsigned int dinero = 0;

unsigned long previousMillisMonedas = 0;
unsigned int intervalMonedas = 500;

unsigned long previousMillisDevoluciones = 0;
unsigned int intervalDevoluciones = 0;

// Temperatura
const unsigned int tiempoMaxSobretemperatura = 6000;
unsigned long lastTimeSobretemperatura;

unsigned long intervalTempWarningLed = 1000;
unsigned long lastTimetempWarningLed;

// Fuente de alimentacion
const long Tiempo_Baja_Tension = 500;
unsigned long previus_millis_error_tension;

unsigned long previus_millis_parpadeo_error_tension;
const long Tiempo_Led_Error_Tension_On = 1000;
const long Tiempo_Led_Error_Tension_Off = 5000;

// Motor
const int tiempoDispensacionProducto = 5000;
unsigned long lastTimeDispensacion;
const int intervaloPulsos = 500;
unsigned long lastTimePulsoMotor;

// Estados
bool estadoDevolucion = LOW;          // Si se ha iniciado nua devolucion
bool Estado_Led_Tension = LOW;
bool Error_Baja_Tension = LOW;
bool moverMotor = LOW;
bool caidaProductoEnCurso = LOW;

const int introducirMonedas = 0;
const int dispensarProductoEstado = 1;
const int detectarCaidaProducto = 2;
const int devolucionCambios = 3;

unsigned int estado = introducirMonedas;

// Caida Producto
unsigned int tiempoMaxCaida = 20000;
unsigned long lastTimeCaidaProducto;

// Constantes

const float V = 5.0 / 1023.0;
const int Tmax = 25;
const float Histeresis = 0.75;
const float tObj = 15.0;
const int Tension_Minima = 10;


void setup() {

  Serial.begin(9600);

  pinMode(sensorUPS, INPUT);
  pinMode(sensorTemp, INPUT);
  pinMode(pulsadorCaida, INPUT);
  pinMode(pulsadorMonedas, INPUT);
  pinMode(devolucionesLed, OUTPUT);
  pinMode(refrigerador, OUTPUT);
  pinMode(LED_Error, OUTPUT);
  pinMode(ledMotor1, OUTPUT);
  pinMode(ledMotor2, OUTPUT);


}

void loop() {

  comprobarPSU();
  controlTemperatura();

  if (Error_Baja_Tension == LOW)
  {

    switch (estado)
    {

      case 0:

        comprobarInsercionMonedas(digitalRead(pulsadorMonedas));
        leerTeclado();
        break;

      case 1:

        dispensarProducto();
        break;
      case 2:

        comprobar_Caida();
        break;

      case 3:

        comprobarDevoluciones();
        break;
    }
  }
}
