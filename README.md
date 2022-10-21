# Ampersand Arturo - Unidad 3
###### *Josué Quinche Parra, Ana María Diaz Rocha, Emilio José Jimenez de los Rios, Juana Valentina Rico*

Nuestro Sensor es un acelerómetro y giroscópio MPU-6050, los datos que envía son aceleración X,Y y Z, así como el giro en estos tres ejes.
Usamos los datos de la aceleración en solo dos ejes (ya que en Z no funcionaba), la información no se transmitia en números de punto flotante sino en enteros de 16 bits, asi que cuando nuestro ESP32 pasaba los datos por el puerto serial lo hacia por "paquetes" de 8 bits cada uno, asi que cuando Unity los leia solo debia ponerlos en un arreglo y el valor de cada variable eran dos de los bits que se recibian.

ESP32 envia solo 4 paquetes de 8 bits, es decir, solo dos variables, las cuales ya tienen su valor mapeado, esto se logró con algo de experimentación y la función "map":
*X = map(AcX,20000,0,0,90); Y = map(AcY,0,20000,0,90);*

Esta función toma los valores de una variable, en este caso la aceleración, y al ponerle los valores menores y mayores funcionales que arrojaba la variable, este lo "traduce" y mapea en valores de 0 a 90 grados, que es el rango que funcionaba de forma correcta (ya que anteriormente hacía saltos extraños debido a los signos)

Aun con eso, de vez en cuando los valores enviados no eran un simple 14, 57 o 78, sino que subian a 62558 o 60145, por eso pusimos un condicional para el codigo de c#, que si los valores eran mayores a 90, entonces el valor simplemente es 90.

Más aún, para rotar el cubo de la escena de Unity usabamos la función: Transform.eulerangles debido a que era un figura con el script implementado en lugar de un gameobjectt vacio.
