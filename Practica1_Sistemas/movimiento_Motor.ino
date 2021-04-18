void dispensarProducto()
{

  if (moverMotor == LOW)
  {
    Serial.println("Dispensando producto");
    lastTimeDispensacion = millis();
    moverMotor = HIGH;
  }

  if (millis() - lastTimeDispensacion >= tiempoDispensacionProducto)
  {
    moverMotor = LOW;
  }

  
  trenPulsosMotor();
}

void trenPulsosMotor() 
{

  if (moverMotor == HIGH)
  {

    if (millis() - lastTimePulsoMotor >= intervaloPulsos)
    {

      if (digitalRead(ledMotor1) == HIGH)
      {

        digitalWrite(ledMotor1, LOW);
        digitalWrite(ledMotor2, HIGH);
      } else
      {

        digitalWrite(ledMotor1, HIGH);
        digitalWrite(ledMotor2, LOW);
      }

      lastTimePulsoMotor = millis();
    }


  } else {

    digitalWrite(ledMotor1, LOW);
    digitalWrite(ledMotor2, LOW);
    estado = detectarCaidaProducto;
  }
}
