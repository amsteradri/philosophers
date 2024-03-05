# 📚 Proyecto Filósofos

Este proyecto consiste en simular la clásica paradoja de los filósofos comensales utilizando threads y mutexes en C. Los filósofos pasan su vida comiendo, pensando y durmiendo. Para comer, cada filósofo necesita dos tenedores. Sin embargo, los tenedores son compartidos entre los filósofos adyacentes. Esto puede llevar a un problema de interbloqueo si los filósofos toman los tenedores al mismo tiempo. El objetivo del proyecto es implementar un algoritmo que evite el interbloqueo, permitiendo que los filósofos cenen sin riesgo de inanición ni de interbloqueo. 🍽️🤔💤

## 🛠 Instalación

Sigue estos pasos para compilar y ejecutar el proyecto:

### 📦 Clonar el repositorio

1. Clona este repositorio en tu máquina local:

```bash
git clone https://github.com/amsteradri/philosophers.git
```
### 📂 Navegar al directorio del proyecto

```bash
cd philosophers/philo
```
### 🔨 Compilar el código
```bash
make
```
## 🖥 Uso

El programa toma los siguientes argumentos de línea de comandos:
n_philos: Número de filósofos en la mesa.
time_to_die: Tiempo en milisegundos que tarda un filósofo en morir sin comida.
time_to_eat: Tiempo en milisegundos que tarda un filósofo en comer.
time_to_sleep: Tiempo en milisegundos que tarda un filósofo en dormir.
n_meals (opcional): Número máximo de comidas que un filósofo puede comer antes de que el programa se detenga. Si no se proporciona este argumento, los filósofos continuarán comiendo hasta que el programa se detenga manualmente.

### 🚀 Ejecutar el programa

Ejecuta el programa con los argumentos necesarios. Por ejemplo, para ejecutar el programa con 5 filósofos, un tiempo para morir de 800 ms, un tiempo para comer de 200 ms y un tiempo para dormir de 200 ms, puedes utilizar el siguiente comando:

```bash
./philo 5 800 200 200
./philo 1 800 200 200 muere
./philo 5 800 200 200 viven
./philo 5 800 200 200 7 viven y cada uno come 7 veces
./philo 4 410 200 200 viven
./philo 4 310 200 100 mueren
(pruebas complejas)
./philo 3 310 103 103 (tienen que vivir)
./philo 3 310 104 104 (tienen que morir)
```
