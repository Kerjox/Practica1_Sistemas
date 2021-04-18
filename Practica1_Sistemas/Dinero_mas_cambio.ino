void comprobarInsercionMonedas(bool estadoPulsador) 
{

  if ((estadoPulsador == LOW) && ((millis() - previousMillisMonedas) >= intervalMonedas)) 
  {

    previousMillisMonedas = millis();
    sumarDinero();
  }
}

void sumarDinero() {

  dinero += 5;
  Serial.print("Dinero: ");
  Serial.print(dinero);
  Serial.println(" centimos");
}

void comprobarDevoluciones()
{
  if (dinero == 0) 
  {

    estado = introducirMonedas;
  }
  
  if ((estadoDevolucion == LOW)) 
  {

    estadoDevolucion = HIGH;    //Inicio la devolucion en caso que no este iniciada
    contadorDevoluciones = dinero / 5;
    intervalDevoluciones = contadorDevoluciones * 500;
    
    digitalWrite(devolucionesLed, HIGH);
    previousMillisDevoluciones = millis();

    Serial.print("Dinero a devolver: ");
    Serial.print(dinero);
    Serial.println(" centimos");
  }
  
  if ((estadoDevolucion == HIGH) && ((millis() - previousMillisDevoluciones) >= intervalDevoluciones)) 
  {

    digitalWrite(devolucionesLed, LOW);
    estadoDevolucion = LOW;
    dinero = 0;
    Serial.println("Fin devoluciones");
    estado = introducirMonedas;
  }
}
