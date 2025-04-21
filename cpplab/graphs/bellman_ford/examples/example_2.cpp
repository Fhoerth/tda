// ┌──┐        ┌──┐       ┌──┐
// │A ├────────┤B ├───────┤C │
// └─┬┘    10  └─┬┘   10  └┬─┘
//   │           │         │
//   │           │         │
//   │           │         │
// 2 │           │         │
//   │           │         │
//   │           │         │
// ┌─┴┐     2    │         │
// │  ├──────────┘         │
// │D │     2              │
// │  │────────────────────┘
// └──┘

// Esta versión sirve para debuggear:
// No alcanza con solo actualizar parents para reconstruir el camino mas corto
// Ya que como se observa, la fila anterior siempre tiene los mejores valores
// para llegar con k aristas a un nodo especifico.
// dp[j - 1][u] + w < dp[j][v] en la mayoria de los casos eso va a dar true
// Ya q lo mas probable (y por como funciona el algoritmo), dp[j][v] sea inf
// (A menos que dos nodos, en el mismo nivel apunten a "v").
// Al ser casi siempre true, nos podría pasar que al actualizar parents[v] lo estemos actualizando
// No con el mejor valor posible. En el ejemplo 3 se usa una estructura auxiliar para resolver este
// problema.

#include <iostream>

#include "../../../print_utils.h"

class Solution
{
  public:
    std::vector<int> bellman_ford(std::vector<int> &vertex,
                                  std::vector<std::tuple<int, int, int>> &edges, int origin,
                                  int destination)
    {
        std::vector<std::vector<int>> dp(vertex.size(), std::vector<int>(vertex.size(), 1e9));
        std::vector<int> parents(vertex.size(), -1);

        dp[0][origin] = 0;

        for (int j = 1; j < vertex.size(); j += 1)
        {
            for (const auto &[u, v, w] : edges)
                if (dp[j - 1][u] + w < dp[j][v])
                {
                    std::cout << "Tengo q comparar dp[" << j - 1 << "][" << u << "] + " << w
                              << std::endl;
                    std::cout << "con dp[" << j << "][" << v << "]" << std::endl;
                    std::cout << "Tengo que comparar: " << dp[j - 1][u] + w << "<" << dp[j][v]
                              << std::endl;
                    std::cout << "Llegué al nodo: ( " << v << "), desde (" << u << ") usando " << j
                              << " aristas" << std::endl;
                    std::cout << "El valor para llegar era: " << dp[j][v]
                              << "; y ahora es: " << dp[j - 1][u] + w << std::endl;
                    std::cout << "Settendo dp[" << j << "][" << v << "]" << std::endl;

                    dp[j][v] = dp[j - 1][u] + w;
                    parents[v] = u;

                    print_int_vector(parents);

                    std::cout << '\n' << std::endl;
                }
        }

        print_int_vector(parents);
        print_int_matrix(dp);

        std::vector<int> path;
        int current = destination;

        while (current != origin)
        {
            path.push_back(current);
            current = parents[current];
        }
        path.push_back(origin);
        std::reverse(path.begin(), path.end());

        return path;
    }
};

int main()
{
    Solution solution;
    std::vector<int> vertex_1 = {0, 1, 2, 3};
    std::vector<std::tuple<int, int, int>> edges_1 = {
        {0, 1, 10}, {1, 2, 10}, {0, 3, 2}, {3, 1, 2}, {3, 2, 2}};
    int origin_1 = 0;      // A
    int destination_1 = 2; // C
    std::vector<int> path_1 = solution.bellman_ford(vertex_1, edges_1, origin_1, destination_1);

    std::cout << "El camino más barato (ERRONEO) para llegar de A a C es:" << std::endl;
    print_path(path_1);
}