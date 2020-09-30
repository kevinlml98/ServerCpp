# ServerCpp
Servidor en C++

Contiene el algoritmo de FloydWarshall con dos matrices por defecto para realizar las pruebas.
El algoritmo trabaja con dos matrices de adyacencia; una de ruta y otra de distanicia. Ambas iran cambiando sus valores conforme se ejecuta el método constructor.

    int infinit = 10000;
    int ma[5][5] = { 0, 4, 8, infinit, infinit,
                     4, 0, 1, 2, infinit,
                     8, infinit, 0, 4, 2,
                     infinit, 2, 4, 0, 7,
                     infinit, infinit, 2, 7, 0};
    char mr[5][5] = { 'a','b','c','d','e',
                      'a','b','c','d','e',
                      'a','b','c','d','e',
                      'a','b','c','d','e',
                      'a','b','c','d','e'};
                      
Este ejemplo presenta cinco nodos interconectado entre sí.

Para probar el servidor se recomienda utilizar el protocolo de telnet utilizando la dirección del servidor local y el puerto 8080

# telnet localhost 8080

Entonces se procederá a realizar la conexión y el servidor comenzará a escuchar.
Para ingresar los nodos se coloca primero el nodo inicial y luego el nodo final. El servidor retornará primero la ruta que se toma partiendo desde el nodo inicial hasta llegar al nodo final. Seguidamente muestra el valor de esa ruta

--> ae

--> ace
--> 10
