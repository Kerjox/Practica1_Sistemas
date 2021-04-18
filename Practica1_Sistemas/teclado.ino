void leerTeclado() 
{

  char tecla = teclado.getKey();
  if (tecla) 
  {
    codigoProducto[indexCodigoTeclado] = tecla;
    indexCodigoTeclado++;
  }

  if (indexCodigoTeclado == 3) 
  {
    
    indexCodigoTeclado = 0;
    obtenerProducto();
  }
}

void obtenerProducto() 
{

  bool codigoCorrecto = LOW;
  for (int i = 0; i < 6; i++) 
  {

    if (strcmp(codigoProducto, codigosProductos[i].c_str()) == 0) 
    {
      
      Serial.print("Codigo introducido: ");
      Serial.println(codigosProductos[i]);
      Serial.print("Producto: ");
      Serial.println(nombresProductos[i]);
      Serial.print("Precio: ");
      Serial.print(preciosProductos[i]);
      Serial.println(" centimos");
      codigoCorrecto = HIGH;
      if (preciosProductos[i] > dinero)
      {
        Serial.println("Credito insuficiente");
      } else 
      {
        precioProducto = preciosProductos[i];
        estado = dispensarProductoEstado;
      }
    }
  }

  if (codigoCorrecto == LOW) 
  {
    
    Serial.println("Código no valido");
  }
}
