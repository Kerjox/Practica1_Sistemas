

void controlTemperatura() {

  unsigned int A1Read = analogRead(sensorTemp);
  float Temperatura = V * A1Read * 10.0 - 10.0;
  bool refrigeradorState = Funcion_Bascula(Temperatura, Histeresis, tObj);
  digitalWrite(refrigerador, refrigeradorState);

  bool sobrecalentamiento = comprobarSobretemperatura(Temperatura);
  funcionTempWarningLed(sobrecalentamiento);

/*
  Serial.print(Temperatura);
  Serial.print(",");
  Serial.print(14.25);
  Serial.print(",");
  Serial.print(15.75);
  Serial.print(",");
  Serial.print(refrigeradorState);
  Serial.print(",");
  Serial.println(sobrecalentamiento);
  */
}

bool comprobarSobretemperatura(float Temperatura) 
{

  bool sobrecalentamiento;

  if (Temperatura >= Tmax) {

    if ((millis() - lastTimeSobretemperatura) >= tiempoMaxSobretemperatura) 
    {

      if (sobrecalentamiento == LOW) 
      {

        sobrecalentamiento = HIGH;
      }
    }

  } else 
  {

    lastTimeSobretemperatura = millis();
    sobrecalentamiento = LOW;
  }

  return sobrecalentamiento;
}

bool Funcion_Bascula (float Temperatura, float Histeresis, float tObj) 
{

  static bool estado;

  if (tObj + Histeresis < Temperatura) 
  {
    estado = HIGH;
  }
  if (tObj - Histeresis > Temperatura) 
  {
    estado = LOW;
  }
  return estado;
}

void funcionTempWarningLed(bool sobrecalentamiento) 
{

  if (Error_Baja_Tension == LOW) 
  {

    if (sobrecalentamiento == HIGH) 
    {

      if ((millis() - lastTimetempWarningLed) >= intervalTempWarningLed) 
      {

        lastTimetempWarningLed = millis();
        digitalWrite(LED_Error, !digitalRead(LED_Error));
        Serial.println("Sobrecalentamiento");
      }
    } else if (digitalRead(LED_Error) == HIGH) 
    {

      digitalWrite(LED_Error, LOW);
    }
  }
}
