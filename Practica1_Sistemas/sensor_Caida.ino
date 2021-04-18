void comprobar_Caida(){

  if (caidaProductoEnCurso == LOW)
  {
    Serial.println("Detectando caida del producto");
    caidaProductoEnCurso = HIGH;
    lastTimeCaidaProducto = millis();
  }

  if (digitalRead(pulsadorCaida) == HIGH)
  {
    dinero -= precioProducto;
    estado = devolucionCambios;
    caidaProductoEnCurso = LOW;
    Serial.println("El producto ha caido");
  }else
  {
    bool limit = comprobarTiempoLimite();

    if (limit == HIGH) {

      caidaProductoEnCurso = LOW;
      estado = devolucionCambios;
      Serial.println("Tiempo limite alcanzado, el producto no ha caido");
    }
  }
}

bool comprobarTiempoLimite() 
{

  if (millis() - lastTimeCaidaProducto >= tiempoMaxCaida) 
  {

    return HIGH;
  } else 
  {

    return LOW;
  }
}
