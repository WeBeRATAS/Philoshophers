<h1 align="center">Philosophers</h1>
<p align="center">
  <b>Simulación del problema de los filósofos comensales usando hilos y mutexes.</b>
</p>

---

## **Índice**
1. [Introducción](#introducción)
2. [Estructura del Proyecto](#estructura-del-proyecto)
3. [Lógica del Programa](#lógica-del-programa)
4. [Explicación de Hilos y Mutexes](#explicación-de-hilos-y-mutexes)
5. [Ejemplos de Funcionamiento](#ejemplos-de-funcionamiento)
6. [Pruebas y Validación](#pruebas-y-validación)
7. [Compilación y Ejecución](#compilación-y-ejecución)
8. [Conclusión](#conclusión)
9. [Referencias](#referencias)

---

## **1. Introducción**
El proyecto **Philosophers** es una simulación del clásico problema de los filósofos comensales, donde varios filósofos (hilos) compiten por recursos limitados (tenedores/mutexes) para comer, dormir y pensar. El objetivo es evitar el deadlock y garantizar que todos los filósofos puedan comer sin morir de hambre.

---

## **2. Estructura del Proyecto**
El proyecto está organizado en los siguientes archivos:
- `philo.h`: Cabecera con definiciones de estructuras y prototipos de funciones.
- `routine.c`: Lógica principal de los filósofos.
- `philo_actions.c`: Funciones para comer, dormir y pensar.
- `control_time.c`: Funciones para manejar el tiempo y la sincronización.
- `utils.c`: Funciones auxiliares para el control de la simulación.

---

## **3. Lógica del Programa**
### **3.1. Inicialización**
```plaintext
Inicializar mesa (table):
    Crear mutexes para tenedores.
    Crear hilos para cada filósofo.
    Inicializar tiempos y contadores.
Rutina del filósofo (philo):
    Si el filósofo es par, esperar un poco para evitar deadlocks.
    Mientras la simulación no esté detenida:
        Comer.
        Dormir.
        Pensar.
        Si el filósofo ha comido suficiente, salir del bucle.
Comer (philo):
    Tomar tenedor izquierdo.
    Tomar tenedor derecho.
    Actualizar última comida y contador de comidas.
    Liberar tenedores.

Dormir (philo):
    Esperar un tiempo fijo.

Pensar (philo):
    Esperar un tiempo fijo.
Obtener tiempo actual (get_time_ml):
    Usar gettimeofday para obtener el tiempo en milisegundos.

Espera precisa (precise_usleep):
    Usar un bucle con usleep para esperar de manera precisa.
Controlador de filósofos (philo_controller):
    Mientras la simulación no esté detenida:
        Para cada filósofo:
            Verificar si ha muerto de hambre.
            Si un filósofo muere, detener la simulación.
Matar filósofo (kill):
    Marcar la simulación como detenida.
    Imprimir mensaje de muerte.
## 4. Explicación de Hilos y Mutexes
## 4.1. Hilos (pthread)
Cada filósofo es un hilo independiente que ejecuta la función ft_routine_philosophers.

## 4.2. Mutexes
Mutex para tenedores: Cada tenedor es un mutex que los filósofos deben bloquear para comer.

Mutex para control de la simulación (stop_m): Evita condiciones de carrera al detener la simulación.

Mutex para el tiempo de la última comida (last_m): Protege el acceso a last_meal y meals.

## 5. Ejemplos de Funcionamiento
5.1. Caso Básico
bash
Copy
./philo 5 800 200 200
Explicación: 5 filósofos, 800 ms para morir, 200 ms para comer y dormir.

Comportamiento esperado: Los filósofos comen, duermen y piensan sin morir.

5.2. Caso con Límite de Comidas
bash
Copy
./philo 5 800 200 200 7
## 8. Conclusión
El proyecto Philosophers demuestra un correcto manejo de hilos y mutexes para resolver el problema de los filósofos comensales. Se logró evitar el deadlock y garantizar que todos los filósofos puedan comer sin morir de hambre.

## 9. Referencias
Documentación de pthread: https://man7.org/linux/man-pages/man7/pthreads.7.html

Problema de los filósofos comensales: https://es.wikipedia.org/wiki/Problema_de_la_cena_de_los_filósofos
Explicación: Cada filósofo debe comer al menos 7 veces.
