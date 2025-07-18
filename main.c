/**
 * ============================================================================
 * SIMULADOR DE LOTERÍA LOTO
 * Proyecto Final - Desarrollo Lógico y Algoritmico
 * ============================================================================
 * 
 * Descripción: Simulador completo de lotería que permite ingresar números
 * ganadores, registrar boletos de jugadores y calcular premios automáticamente.
 * 
 * Funcionalidades principales:
 * - Ingreso de números ganadores (6 números del 1 al 38)
 * - Registro de boletos de jugadores (máximo 10 boletos)
 * - Cálculo automático de aciertos y premios
 * - Interfaz gráfica con colores y sonidos
 * - Validación completa de entrada de datos
 * - Resumen estadístico de resultados
 * 
 * Autor: Diogo Pinzon - 8-1035-2187, Joseph Ibarguen 8-1040-1107 y Valentín Sáez 3-757-2165
 * Fecha: 07/18/2025
 * Versión: 1.0
 * Plataforma: Windows (usa librerías específicas de Windows)
 * ============================================================================
 */

// ============================================================================
// INCLUSIÓN DE LIBRERÍAS
// ============================================================================

#include <stdio.h>      // Funciones estándar de entrada/salida (printf, scanf)
#include <stdlib.h>     // Funciones de utilidad general (system, srand, rand)
#include <conio.h>      // Funciones de consola específicas de Windows
#include <time.h>       // Funciones de tiempo (time, para semilla aleatoria)
#include <windows.h>    // API de Windows (colores, títulos, configuración)
#include <mmsystem.h>   // Sistema multimedia de Windows (sonidos Beep)

// ============================================================================
// DEFINICIÓN DE CONSTANTES DEL SISTEMA
// ============================================================================

#define MAX_BOLETOS 10          // Máximo número de boletos que se pueden registrar
#define NUMEROS_POR_BOLETO 6    // Cantidad de números por boleto
#define NUMERO_MIN 1            // Número mínimo válido
#define NUMERO_MAX 38           // Número máximo válido

// ============================================================================
// CÓDIGOS DE COLORES PARA LA CONSOLA DE WINDOWS
// ============================================================================

#define COLOR_ROJO 12           // Rojo - Para errores y advertencias
#define COLOR_VERDE 10          // Verde - Para éxito y confirmaciones
#define COLOR_AMARILLO 14       // Amarillo - Para títulos y destacados
#define COLOR_AZUL 9            // Azul - Para información general
#define COLOR_MAGENTA 13        // Magenta - Para marcos y decoraciones
#define COLOR_BLANCO 15         // Blanco - Color por defecto

// ============================================================================
// VARIABLES GLOBALES
// ============================================================================

/**
 * Array que almacena los 6 números ganadores del sorteo
 * Ejemplo: {5, 12, 18, 25, 31, 37}
 */
int numerosGanadores[NUMEROS_POR_BOLETO];

/**
 * Array bidimensional que almacena todos los boletos ingresados
 * Primer índice: número de boleto (0-9)
 * Segundo índice: número dentro del boleto (0-5)
 * Ejemplo: boletos[0][0] = primer número del primer boleto
 */
int boletos[MAX_BOLETOS][NUMEROS_POR_BOLETO];

/**
 * Array que almacena la cantidad de aciertos por boleto
 * aciertos[i] = cantidad de números correctos en el boleto i
 */
int aciertos[MAX_BOLETOS];

/**
 * Array que almacena el premio ganado por cada boleto
 * premios[i] = dinero ganado por el boleto i
 */
double premios[MAX_BOLETOS];

/**
 * Contador de boletos ingresados actualmente
 * Rango: 0 a MAX_BOLETOS
 */
int cantidadBoletos = 0;

/**
 * Flag que indica si ya se ingresaron los números ganadores
 * 0 = No ingresados, 1 = Ya ingresados
 */
int ganadoresIngresados = 0;

// ============================================================================
// TABLA DE PREMIOS
// ============================================================================

/**
 * Array que mapea la cantidad de aciertos con el premio correspondiente
 * Índice 0: 0 aciertos = $0.00
 * Índice 1: 1 acierto = $0.00
 * Índice 2: 2 aciertos = $0.00
 * Índice 3: 3 aciertos = $5.00
 * Índice 4: 4 aciertos = $50.00
 * Índice 5: 5 aciertos = $1,500.00
 * Índice 6: 6 aciertos = $500,000.00 (Premio Mayor)
 */
double tablaPremios[7] = {0.00, 0.00, 0.00, 5.00, 50.00, 1500.00, 500000.00};

// ============================================================================
// PROTOTIPOS DE FUNCIONES
// ============================================================================

void configurarConsola();                    // Configura título y tamaño de ventana
void cambiarColor(int color);                // Cambia el color del texto en consola
void mostrarBanner();                        // Muestra el banner principal con ASCII art
void mostrarMenu();                          // Muestra el menú principal de opciones
void mostrarReglas();                        // Muestra las reglas del juego
void pausarPantalla();                       // Pausa la ejecución esperando tecla
void ingresarGanadores();                    // Permite ingresar los números ganadores
void ingresarBoletos();                      // Permite ingresar boletos de jugadores
void mostrarResumen();                       // Muestra resumen de resultados
void reproducirSonido(int tipo);             // Reproduce diferentes tipos de sonidos
void mostrarNumeros(int nums[], int cantidad); // Muestra números con formato especial

// ============================================================================
// FUNCIÓN PRINCIPAL
// ============================================================================

/**
 * Función principal del programa
 * Controla el flujo general y el menú principal
 * 
 * @return 0 si la ejecución fue exitosa
 */
int main() {
    // Configurar codificación UTF-8 para caracteres especiales
    // Redirige la salida a nul para no mostrar mensaje de confirmación
    system("chcp 65001 > nul");
    
    // Configurar apariencia de la consola
    configurarConsola();
    
    // Inicializar generador de números aleatorios con la hora actual
    srand(time(NULL));
    
    int opcion; // Variable para almacenar la opción seleccionada
    
    // Bucle principal del programa
    do {
        // Limpiar pantalla
        system("cls");
        
        // Mostrar interfaz principal
        mostrarBanner();
        mostrarMenu();
        
        // Solicitar opción al usuario
        printf("\n  Seleccione una opción: ");
        
        // Validar entrada numérica
        if (scanf("%d", &opcion) != 1) {
            printf("  Error: Ingrese un número válido\n");
            // Limpiar buffer de entrada para evitar bucles infinitos
            while(getchar() != '\n');
            continue;
        }
        
        // Limpiar buffer después de scanf
        while(getchar() != '\n');
        
        // Procesar la opción seleccionada
        switch(opcion) {
            case 1: 
                ingresarGanadores();
                break;
            case 2: 
                ingresarBoletos();
                break;
            case 3: 
                mostrarResumen();
                break;
            case 4: 
                mostrarReglas();
                break;
            case 5: 
                // Despedida del programa
                mostrarBanner();
                printf("\n  Gracias por usar el simulador. ¡Buena suerte!\n");
                reproducirSonido(4); // Sonido de despedida
                return 0;
            default: 
                printf("  Opción no válida\n");
                reproducirSonido(2); // Sonido de error
        }
        
        // Pausa para que el usuario pueda leer el resultado
        pausarPantalla();
        
    } while(1); // Bucle infinito hasta que el usuario seleccione salir
    
    return 0;
}

// ============================================================================
// FUNCIONES DE CONFIGURACIÓN Y UTILIDAD
// ============================================================================

/**
 * Configura la apariencia inicial de la consola
 * Establece el título de la ventana y sus dimensiones
 */
void configurarConsola() {
    // Establecer título de la ventana
    SetConsoleTitle("SIMULADOR DE LOTERIA LOTO");
    
    // Configurar tamaño de la ventana: 80 columnas x 30 filas
    system("mode con: cols=80 lines=30");
}

/**
 * Cambia el color del texto en la consola
 * Utiliza la API de Windows para modificar atributos del texto
 * 
 * @param color Código de color (definido en las constantes)
 */
void cambiarColor(int color) {
    // Obtener handle de la consola y cambiar atributos de texto
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ============================================================================
// FUNCIONES DE INTERFAZ DE USUARIO
// ============================================================================

/**
 * Muestra el banner principal del programa
 * Incluye ASCII art y títulos con colores
 */

  
void mostrarBanner() {
    // Cambiar a color magenta para el ASCII art
    cambiarColor(COLOR_MAGENTA);
    printf("\n");
    printf("  ██╗░░░░░░█████╗░  ██╗░░░░░░█████╗░████████╗████████╗░█████╗░\n");
    printf("  ██║░░░░░██╔══██╗  ██║░░░░░██╔══██╗╚══██╔══╝╚══██╔══╝██╔══██╗\n");
    printf("  ██║░░░░░███████║  ██║░░░░░██║░░██║░░░██║░░░░░░██║░░░██║░░██║\n");
    printf("  ██║░░░░░██╔══██║  ██║░░░░░██║░░██║░░░██║░░░░░░██║░░░██║░░██║\n");
    printf("  ███████╗██║░░██║  ███████╗╚█████╔╝░░░██║░░░░░░██║░░░╚█████╔╝\n");
    printf("  ╚══════╝╚═╝░░╚═╝  ╚══════╝░╚════╝░░░░╚═╝░░░░░░╚═╝░░░░╚════╝░\n");
    
    // Cambiar a color amarillo para los títulos
    cambiarColor(COLOR_AMARILLO);
    printf("\n  ===== SIMULADOR DE LOTERIA LOTO =====\n");
    printf("  ===== PROYECTO FINAL - DESARROLLO LOGICO =====\n");
    
    // Volver al color blanco por defecto
    cambiarColor(COLOR_BLANCO);
}

/**
 * Muestra el menú principal de opciones
 * Utiliza marcos decorativos y colores para mejorar la presentación
 */
void mostrarMenu() {
    cambiarColor(COLOR_MAGENTA);
    printf("\n  ╔══════════════════════════════════════════════╗\n");
    printf("  ║                                              ║\n");
    printf("  ║               ");
    cambiarColor(COLOR_AZUL);
    printf("MENÚ PRINCIPAL");
    cambiarColor(COLOR_MAGENTA);
    printf("                 ║\n");
    printf("  ║                                              ║\n");
    printf("  ╠══════════════════════════════════════════════╣\n");
    printf("  ║  ");
cambiarColor(COLOR_VERDE);
    printf("    1. Ingresar números ganadores");
cambiarColor(COLOR_MAGENTA);
    printf("           ║\n");
    printf("  ║  ");
cambiarColor(COLOR_VERDE);
    printf("    2. Ingresar boletos                 ");
    cambiarColor(COLOR_MAGENTA);
    printf("    ║\n");
    printf("  ║  ");
cambiarColor(COLOR_VERDE);
    printf("    3. Mostrar resumen                   ");
    cambiarColor(COLOR_MAGENTA);
    printf("   ║\n");
    printf("  ║  ");
cambiarColor(COLOR_VERDE);
    printf("    4. Reglas del juego                 ");
    cambiarColor(COLOR_MAGENTA);
    printf("    ║\n");
    printf("  ║  ");
cambiarColor(COLOR_ROJO);
    printf("    5. Salir                            ");
    cambiarColor(COLOR_MAGENTA);
    printf("    ║\n");
    printf("  ║                                              ║\n");
    printf("  ╚══════════════════════════════════════════════╝\n");
    cambiarColor(COLOR_BLANCO);
}

/**
 * Pausa la ejecución del programa esperando que el usuario presione una tecla
 * Muestra el mensaje en color gris para diferenciarlo del contenido principal
 */
void pausarPantalla() {
    printf("\n  ");
    cambiarColor(8); // Color gris
    system("pause"); // Comando de Windows para pausar
    cambiarColor(COLOR_BLANCO);
}

// ============================================================================
// FUNCIONES DE LÓGICA DE NEGOCIO
// ============================================================================

/**
 * Permite al usuario ingresar los 6 números ganadores del sorteo
 * Incluye validación completa: rango, duplicados, entrada válida
 */
void ingresarGanadores() {
    // Limpiar pantalla y mostrar header
    system("cls");
    mostrarBanner();
    
    // Mostrar título de la sección
    cambiarColor(COLOR_MAGENTA);
    printf("\n  ╔══════════════════════════════════════════════╗\n");
    printf("  ║           INGRESO DE NUMEROS GANADORES       ║\n");
    printf("  ╚══════════════════════════════════════════════╝\n");
    cambiarColor(COLOR_BLANCO);
    
    // Bucle para ingresar cada número
    for(int i = 0; i < NUMEROS_POR_BOLETO; i++) {
        int valido = 0; // Flag para validar entrada
        
        // Repetir hasta obtener un número válido
        while(!valido) {
            printf("  Ingrese número %d/%d: ", i+1, NUMEROS_POR_BOLETO);
            
            // Validar que la entrada sea un número
            if(scanf("%d", &numerosGanadores[i]) != 1) {
                printf("  Error: Ingrese un número válido\n");
                // Limpiar buffer de entrada
                while(getchar() != '\n');
                continue;
            }
            
            // Validar rango (1-38)
            if(numerosGanadores[i] < NUMERO_MIN || numerosGanadores[i] > NUMERO_MAX) {
                printf("  Número fuera de rango (1-38)\n");
                continue;
            }
            
            // Verificar duplicados con números ya ingresados
            int duplicado = 0;
            for(int j = 0; j < i; j++) {
                if(numerosGanadores[j] == numerosGanadores[i]) {
                    duplicado = 1;
                    break;
                }
            }
            
            if(duplicado) {
                printf("  Número duplicado\n");
                continue;
            }
            
            // Número válido: confirmar y continuar
            valido = 1;
            cambiarColor(COLOR_VERDE);
            printf("  Número %d recibido correctamente ✔\n", numerosGanadores[i]);
            cambiarColor(COLOR_BLANCO);
            reproducirSonido(1); // Sonido de éxito
        }
    }
    
    // Marcar que los números ganadores ya fueron ingresados
    ganadoresIngresados = 1;
    
    // Mensaje de confirmación final
    cambiarColor(COLOR_VERDE);
    printf("\n  ¡Números ganadores registrados con éxito!\n");
    cambiarColor(COLOR_BLANCO);
    reproducirSonido(3); // Sonido de ganador
}

/**
 * Permite ingresar boletos de jugadores y calcula automáticamente
 * los aciertos y premios correspondientes
 */
void ingresarBoletos() {
    // Limpiar pantalla y mostrar header
    system("cls");
    mostrarBanner();
    
    // Verificar que se hayan ingresado los números ganadores
    if(!ganadoresIngresados) {
        cambiarColor(COLOR_ROJO);
        printf("\n  ¡Primero ingrese los números ganadores!\n");
        cambiarColor(COLOR_BLANCO);
        reproducirSonido(2); // Sonido de error
        return;
    }
    
    // Verificar que no se haya alcanzado el límite de boletos
    if(cantidadBoletos >= MAX_BOLETOS) {
        cambiarColor(COLOR_ROJO);
        printf("\n  ¡Límite de boletos alcanzado (%d)!\n", MAX_BOLETOS);
        cambiarColor(COLOR_BLANCO);
        reproducirSonido(2); // Sonido de error
        return;
    }
    
    // Preguntar cuántos boletos desea ingresar
    int cantidad;
    cambiarColor(COLOR_AZUL);
    printf("\n  ¿Cuántos boletos desea ingresar? (1-%d): ", MAX_BOLETOS - cantidadBoletos);
    cambiarColor(COLOR_BLANCO);
    scanf("%d", &cantidad);
    
    // Validar cantidad
    if(cantidad < 1 || cantidad > (MAX_BOLETOS - cantidadBoletos)) {
        cambiarColor(COLOR_ROJO);
        printf("  Cantidad no válida\n");
        cambiarColor(COLOR_BLANCO);
        return;
    }
    
    // Bucle para ingresar cada boleto
    for(int b = 0; b < cantidad; b++) {
        // Mostrar progreso
        system("cls");
        mostrarBanner();
        
        cambiarColor(COLOR_MAGENTA);
        printf("\n  ╔══════════════════════════════════════════════╗\n");
        printf("  ║               INGRESO DE BOLETOS             ║\n");
        printf("  ╚══════════════════════════════════════════════╝\n");
        cambiarColor(COLOR_BLANCO);
        
        printf("  Boleto %d/%d\n", cantidadBoletos + 1, MAX_BOLETOS);
        
        // Ingresar los 6 números del boleto
        for(int i = 0; i < NUMEROS_POR_BOLETO; i++) {
            int valido = 0;
            
            while(!valido) {
                printf("  Número %d/%d: ", i+1, NUMEROS_POR_BOLETO);
                
                // Validar entrada numérica
                if(scanf("%d", &boletos[cantidadBoletos][i]) != 1) {
                    printf("  Error: Ingrese un número válido\n");
                    while(getchar() != '\n');
                    continue;
                }
                
                // Validar rango
                if(boletos[cantidadBoletos][i] < NUMERO_MIN || 
                   boletos[cantidadBoletos][i] > NUMERO_MAX) {
                    printf("  Número fuera de rango (1-38)\n");
                    continue;
                }
                
                // Verificar duplicados en este boleto
                int duplicado = 0;
                for(int j = 0; j < i; j++) {
                    if(boletos[cantidadBoletos][j] == boletos[cantidadBoletos][i]) {
                        duplicado = 1;
                        break;
                    }
                }
                
                if(duplicado) {
                    printf("  Número duplicado en este boleto\n");
                    continue;
                }
                
                // Número válido
                valido = 1;
                cambiarColor(COLOR_VERDE);
                printf("  Número %d recibido correctamente ✔\n", boletos[cantidadBoletos][i]);
                cambiarColor(COLOR_BLANCO);
                reproducirSonido(1);
            }
        }
        
        // CÁLCULO DE ACIERTOS
        // Contar cuántos números del boleto coinciden con los ganadores
        aciertos[cantidadBoletos] = 0;
        for(int i = 0; i < NUMEROS_POR_BOLETO; i++) {
            for(int j = 0; j < NUMEROS_POR_BOLETO; j++) {
                if(boletos[cantidadBoletos][i] == numerosGanadores[j]) {
                    aciertos[cantidadBoletos]++;
                    break; // Salir del bucle interno al encontrar coincidencia
                }
            }
        }
        
        // ASIGNACIÓN DE PREMIO
        // Usar la tabla de premios basada en el número de aciertos
        premios[cantidadBoletos] = tablaPremios[aciertos[cantidadBoletos]];
        
        // MOSTRAR RESULTADO DEL BOLETO
        printf("\n  Números ingresados: ");
        mostrarNumeros(boletos[cantidadBoletos], NUMEROS_POR_BOLETO);
        
        printf("\n  Aciertos: %d - Premio: $%.2f\n", 
               aciertos[cantidadBoletos], premios[cantidadBoletos]);
        
        // Mostrar mensaje especial para ganadores
        if(aciertos[cantidadBoletos] >= 3) {
            cambiarColor(COLOR_VERDE);
            printf("  ¡FELICIDADES! Has ganado un premio\n");
            cambiarColor(COLOR_BLANCO);
            reproducirSonido(3);
            
            // Mensaje especial para el premio mayor
            if(aciertos[cantidadBoletos] == 6) {
                cambiarColor(COLOR_ROJO);
                printf("  ¡¡¡PREMIO MAYOR!!!\n");
                cambiarColor(COLOR_BLANCO);
                reproducirSonido(5); // Sonido especial para premio mayor
            }
        }
        
        // Incrementar contador de boletos
        cantidadBoletos++;
        
        // Preguntar si desea continuar (solo si no es el último boleto)
        if(b < cantidad - 1) {
            char respuesta;
            printf("\n  ¿Desea continuar ingresando boletos? (s/n): ");
            scanf(" %c", &respuesta); // Espacio antes de %c para ignorar whitespace
            if(respuesta != 's' && respuesta != 'S') {
                break;
            }
        }
    }
}

/**
 * Muestra un resumen completo de todos los resultados
 * Incluye estadísticas generales y detalles de cada boleto
 */
void mostrarResumen() {
    // Limpiar pantalla y mostrar header
    system("cls");
    mostrarBanner();
    
    // Verificar prerrequisitos
    if(!ganadoresIngresados) {
        cambiarColor(COLOR_ROJO);
        printf("\n  ¡Primero ingrese los números ganadores!\n");
        cambiarColor(COLOR_BLANCO);
        reproducirSonido(2);
        return;
    }
    
    // Título de la sección
    cambiarColor(COLOR_MAGENTA);
    printf("\n  ╔══════════════════════════════════════════════╗\n");
    printf("  ║               RESUMEN DE RESULTADOS          ║\n");
    printf("  ╚══════════════════════════════════════════════╝\n");
    cambiarColor(COLOR_BLANCO);
    
    // Mostrar números ganadores
    printf("  Números ganadores: ");
    mostrarNumeros(numerosGanadores, NUMEROS_POR_BOLETO);
    printf("\n\n");
    
    // Verificar si hay boletos registrados
    if(cantidadBoletos == 0) {
        printf("  No hay boletos registrados\n");
        return;
    }
    
    // Variables para estadísticas
    double totalPremios = 0;
    int ganadores = 0;
    
    // Mostrar detalles de cada boleto
    for(int i = 0; i < cantidadBoletos; i++) {
        printf("  Boleto %d: ", i+1);
        mostrarNumeros(boletos[i], NUMEROS_POR_BOLETO);
        
        printf(" - Aciertos: %d - Premio: $%.2f", aciertos[i], premios[i]);
        
        // Marcar ganadores
        if(premios[i] > 0) {
            ganadores++;
            totalPremios += premios[i];
            cambiarColor(COLOR_VERDE);
            printf(" (GANADOR)");
            cambiarColor(COLOR_BLANCO);
        }
        printf("\n");
    }
    
    // MOSTRAR ESTADÍSTICAS GENERALES
    printf("\n  ESTADÍSTICAS:\n");
    printf("  - Boletos jugados: %d\n", cantidadBoletos);
    printf("  - Boletos ganadores: %d\n", ganadores);
    printf("  - Total en premios: $%.2f\n", totalPremios);
}

/**
 * Muestra las reglas del juego y la tabla de premios
 */
void mostrarReglas() {
    // Limpiar pantalla y mostrar header
    system("cls");
    mostrarBanner();
    
    // Título de la sección
    cambiarColor(COLOR_MAGENTA);
    printf("\n  ╔══════════════════════════════════════════════╗\n");
    printf("  ║               REGLAS DEL JUEGO               ║\n");
    printf("  ╚══════════════════════════════════════════════╝\n");
    cambiarColor(COLOR_BLANCO);
    
    // Reglas básicas
    printf("  - Seleccione 6 números diferentes (1-38)\n");
    printf("  - No se permiten números repetidos\n");
    printf("  - Premios por 3, 4, 5 o 6 aciertos\n\n");
    
    // Tabla de premios
    printf("  TABLA DE PREMIOS:\n");
    printf("  3 aciertos: $5.00\n");
    printf("  4 aciertos: $50.00\n");
    printf("  5 aciertos: $1,500.00\n");
    
    // Destacar premio mayor
    cambiarColor(COLOR_ROJO);
    printf("  6 aciertos: $500,000.00 (PREMIO MAYOR)\n");
    cambiarColor(COLOR_BLANCO);
}

// ============================================================================
// FUNCIONES DE MULTIMEDIA Y PRESENTACIÓN
// ============================================================================

/**
 * Reproduce diferentes tipos de sonidos según el evento
 * Utiliza la función Beep de Windows para generar tonos
 * 
 * @param tipo Tipo de sonido a reproducir (1-5)
 */
void reproducirSonido(int tipo) {
    switch(tipo) {
        case 1: // Sonido de éxito (confirmación)
            Beep(784, 150);   // Sol - 150ms
            Beep(880, 150);   // La - 150ms
            Beep(1047, 200);  // Do - 200ms
            break;
            
        case 2: // Sonido de error
            Beep(300, 200);   // Tono bajo - 200ms
            Beep(250, 200);   // Tono más bajo - 200ms
            Beep(200, 300);   // Tono muy bajo - 300ms
            break;
            
        case 3: // Sonido de ganador
            Beep(659, 150);   // Mi - 150ms
            Beep(784, 150);   // Sol - 150ms
            Beep(880, 150);   // La - 150ms
            Beep(1047, 300);  // Do - 300ms
            Beep(880, 150);   // La - 150ms
            Beep(1047, 300);  // Do - 300ms
            break;
            
        case 4: // Sonido de despedida
            Beep(523, 200);   // Do - 200ms
            Beep(659, 200);   // Mi - 200ms
            Beep(784, 200);   // Sol - 200ms
            Beep(1047, 200);  // Do octava - 200ms
            Beep(784, 200);   // Sol - 200ms
            Beep(659, 200);   // Mi - 200ms
            Beep(523, 400);   // Do - 400ms
            break;
            
        case 5: // Sonido de premio mayor (fanfarria)
            // Repetir secuencia 3 veces
            for(int i = 0; i < 3; i++) {
                Beep(1047, 200);  // Do - 200ms
                Beep(1319, 200);  // Mi - 200ms
                Beep(1568, 200);  // Sol - 200ms
                Beep(2093, 300);  // Do octava - 300ms
            }
            break;
    }
}

/**
 * Muestra un array de números con formato especial
 * Los números se muestran entre corchetes, separados por guiones
 * y con formato de dos dígitos (ejemplo: [01-05-12-25-31-38])
 * 
 * @param nums Array de números a mostrar
 * @param cantidad Cantidad de números en el array
 */
void mostrarNumeros(int nums[], int cantidad) {
    // Cambiar a color azul para destacar los números
    cambiarColor(COLOR_AZUL);
    printf("[");
    
    // Mostrar cada número
    for(int i = 0; i < cantidad; i++) {
        printf("%02d", nums[i]); // Formato de dos dígitos
        if(i < cantidad - 1) {   // Si no es el último número
            printf("-");         // Agregar separador
        }
    }
    
    printf("]");
    // Restaurar color original
    cambiarColor(COLOR_BLANCO);
}
