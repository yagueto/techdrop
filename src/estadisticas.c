// #include "estadisticas.h"
// #include "estructuras/estructuras.h"
// #include "bd.h"
// #include "utils.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
//
// //Funciones para las estadisticas de negocio
// void calcularPedidosPorDia(sqlite3 *db, const char *fecha){
//     if (!fecha || strlen(fecha) != 10) {
//         printf("\nFormato de fecha inválido. Usar YYYY-MM-DD\n");
//         return;
//     }
//     int total = obtenerTotalPedidosPorDia(db, fecha);
//     if (total >= 0)
//     {
//         printf("\nPedidos del dia %s: %d\n", fecha, total);
//     }else
//     {
//         printf("\nError al obtener datos\n");
//     }
// }
//
// void calcularZonasPopulares(sqlite3 *db)
// {
//     char zonas[5][100]; //maximo 5 zonas para mostrar por pantalla
//     int contadores[5] = {0};
//     int total = obtenerZonasPopulares(db, zonas, contadores, 5);
//     printf("\n");
//     if (total>0)
//     {
//         printf("Zonas mas populares:\n\n");
//         for (int i = 0; i < total; i++)
//         {
//             printf("%d. %s: %d pedidos\n", i + 1, zonas[i], contadores[i]);
//         }
//     }else
//     {
//         printf("No hay datos de zonas\n");
//     }
// }
//
// void calcularHoraPico(sqlite3 *db)
// {
//    int hora = obtenerHoraPico(db);
//     if (hora >= 0)
//     {
//         printf("\nHora pico: %d:00\n", hora);
//     }else
//     {
//         printf("No hay datos de horas");
//     }
// }
// void calcularPlatosMasVendidos(sqlite3 *db)
// {
//     int ids[5];
//     int cantidades[5];
//     int total = obtenerPlatosMasVendidos(db,ids,cantidades,5);
//
//     if (total> 0)
//     {
//         printf("\nPlatos mas vendidos:\n");
//         for (int i = 0; i < total; i++)
//         {
//             printf("%d. Plato ID %d: %d unidades\n", i + 1, ids[i], cantidades[i]);
//         }
//     }else
//     {
//         printf("No hay datos de platos\n");
//     }
// }
// void calcularClientesRecurrentes(sqlite3 *db)
// {
//     int ids_usuarios[5];
//     int total_pedidos[5];
//     int total = obtenerClientesRecurrentes(db, ids_usuarios, total_pedidos, 5);
//
//     if (total > 0)
//     {
//         printf("\nClientes recurrentes:\n");
//         for (int i = 0; i < total; i++)
//         {
//             printf("%d. Usuario %d: %d pedidos\n", i+1, ids_usuarios[i], total_pedidos[i]);
//         }
//     }else
//     {
//         printf("No hay datos de clientes recurrentes.");
//     }
// }
// void calcularValorMedioPedido(sqlite3 *db)
// {
//     double valor_medio = obtenerValorMedioPedido(db);
//     if (valor_medio >= 0) {
//         printf("\nValor medio de pedido: %.2f€\n", valor_medio);
//     } else {
//         printf("No hay datos para calcular el valor medio\n");
//     }
// }
//
// //Funciones para las estadisticas de robots
// void calcularPedidosPorRobot(sqlite3 *db)
// {
//     int ids_robots[5];
//     int total_pedidos[5];
//     int total = obtenerPedidosPorRobot(db, ids_robots, total_pedidos, 5);
//
//     if (total > 0) {
//         printf("\nPedidos por robot:\n");
//         for (int i = 0; i < total; i++) {
//             printf("%d. Robot %d: %d pedidos\n", i + 1, ids_robots[i], total_pedidos[i]);
//         }
//     } else {
//         printf("No hay datos de pedidos por robot\n");
//     }
// }
// void calcularRobotsActivos(sqlite3 *db)
// {
//     int total_robots;
//     Robot *robots = cargarRobots(db, &total_robots);
//
//     if (!robots || total_robots == 0) {
//         printf("No hay robots.\n");
//         return;
//     }
//
//     int disponibles = 0;
//     for (int i = 0; i < total_robots; i++) {
//         if (robots[i].estado == 2) { // 2 -> Disponible
//             disponibles++;
//         }
//     }
//     printf("\nRobots activos: %d de %d\n", disponibles, total_robots);
//     free(robots);
// }