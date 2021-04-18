void comprobarPSU()
{

  float Vout;
  int DigitalCharge = analogRead(sensorUPS);
  int Pendiente = 3;
  float V = 5.0 / 1023.0;
  float Carga = V * DigitalCharge * Pendiente;

  Error_Baja_Tension = comprobar_Tension(Carga, Tension_Minima);

  if (Error_Baja_Tension == LOW)
  {

    Vout = 4.5;
  } else {

    Vout = 0;
  }

  /*
    Serial.print(Carga);
    Serial.print(",");
    Serial.print(15);
    Serial.print(",");
    Serial.print(Tension_Minima);
    Serial.print(",");
    Serial.print(Vout);
    Serial.print(",");
    Serial.println(Estado_Led_Error);
  */
  parpadearLed(Error_Baja_Tension);
}

bool comprobar_Tension (float Carga, float Tension_Minima)
{
  bool tension;

  if (Carga < Tension_Minima)
  {

    if ((millis() - previus_millis_error_tension >= Tiempo_Baja_Tension))
    {

      tension = HIGH;
    }

  } else
  {

    previus_millis_error_tension = millis();
    tension = LOW;
  }


  return tension;
}

void parpadearLed(bool Error_Baja_Tension)
{
  if (Error_Baja_Tension == HIGH)
  {

    if (Estado_Led_Tension == HIGH)
    {
      
      if ((millis() - previus_millis_parpadeo_error_tension >= Tiempo_Led_Error_Tension_On))
      {

        Estado_Led_Tension = LOW;
        digitalWrite(LED_Error, Estado_Led_Tension);
        previus_millis_parpadeo_error_tension = millis();
      }
    } else
    {
      
      if ((millis() - previus_millis_parpadeo_error_tension >= Tiempo_Led_Error_Tension_Off))
      {

        Estado_Led_Tension = HIGH;
        digitalWrite(LED_Error, Estado_Led_Tension);
        previus_millis_parpadeo_error_tension = millis();
      }
    }
  }
}
