#### 1. Introducción al Proyecto Philosophers
   *************************************
El proyecto Philosophers es una simulación del famoso problema de los filósofos cenando (Dining Philosophers Problem). El objetivo es evitar que los filósofos mueran de hambre o entren en un estado de bloqueo (deadlock) mientras comparten recursos (tenedores) usando hilos y mutex.

Requisitos del Proyecto
Debes usar hilos (pthread) para representar a cada filósofo.

Debes usar mutex para proteger los recursos compartidos (tenedores).

Cada filósofo debe realizar tres acciones: pensar, comer y dormir.

Debes evitar el deadlock y garantizar que todos los filósofos coman.

#### 2. Estructura del Proyecto
   ************************
El proyecto se divide en varias partes:

Inicialización: Crear los hilos y los mutex.

Simulación: Cada filósofo debe pensar, comer y dormir.

Sincronización: Usar mutex para evitar condiciones de carrera y deadlock.

Finalización: Liberar recursos y asegurar que el programa termine correctamente.


Documentación Adicional
pthreads: Guía de pthreads en C

Mutex: Documentación de mutex

Problema de los Filósofos: Wikipedia
