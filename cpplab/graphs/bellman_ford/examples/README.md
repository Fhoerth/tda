# 🧠 Intuición detrás del Algoritmo de Bellman-Ford

## ✅ Explicación informal

El algoritmo de **Bellman-Ford** puede interpretarse como una especie de **BFS por capas** o niveles, donde cada iteración intenta expandir caminos con una cantidad fija de aristas (`j`).

La estructura más natural es usar una **matriz `dp[j][v]`**, donde:

- `j` indica la cantidad de aristas utilizadas.
- `v` es el nodo de llegada.
- `dp[j][v]` representa la distancia mínima para llegar al nodo `v` usando exactamente `j` aristas.

## 💡 ¿Se puede usar un solo vector?

Sí. Aunque usamos una matriz `dp[j][v]`, en realidad **sólo usamos `j` y `j - 1` en cada paso**, por lo tanto se pueden optimizar los recursos usando **2 vectores**:

- Uno para los valores actuales
- Otro para los anteriores

Pero, incluso más allá: si se **actualiza todo en una sola pasada** y con cuidado, se puede usar **un solo vector** (`dist[v]`), sin romper el algoritmo.

Esto es válido porque **las relajaciones sólo mejoran los valores**. Sin embargo, **hay que tener mucho cuidado**, porque si accidentalmente se usa el mismo vector para leer y escribir en la misma iteración, podrías usar un valor ya modificado y eso rompe la lógica.

---

## 🤔 ¿Por qué `dp[j][v] = min(dp[j][v], dp[j - 1][u] + w)`?

La duda surge porque, inicialmente, la matriz está llena de infinitos (`1e9`). Entonces, uno pensaría:

> ¿Por qué no simplemente hacer `dp[j][v] = dp[j - 1][u] + w`?

La razón por la que **sí necesitamos** el `min(...)` es que **un mismo nodo `v` puede ser alcanzado desde diferentes nodos `u` en la misma iteración**. Y, por tanto, `dp[j][v]` **ya no vale infinito** después de la primera relajación.

El `min` nos asegura que, si un camino mejor aparece desde otro nodo `u`, lo consideramos también.

## 🤔 ¿Por qué sirve mirar `dp[j - 1][u] + w`?

La respuesta es que, siempre miramos todas las aristas `(u,v)`, con lo
cuál nuestro estado (ya sea en forma de matriz / vector), siempre tiene
la mejor forma de llegar a `v` con `j` aristas. Pero si yo se que desde `u` llego a `w`, me interesa saber cuánto cuesta llegar a `u` con `j-1` aristas.

---

## 🧮 Complejidad

- Tiempo: `O(V * E)`
- Espacio: `O(V)` con un solo vector, `O(V * L)` con matriz si querés guardar más estados.
  - Donde `L` es la cantidad máxima de aristas permitidas (útil para problemas tipo "K flights").

---

## ✅ Conclusión

- Usar **una matriz `dp[j][v]`** te permite **trazar y visualizar cómo se propaga la información** por niveles.
- Usar **dos vectores** (`prev` y `curr`) mejora el uso de memoria sin perder claridad.
- Usar **un solo vector** es el más eficiente, pero requiere más cuidado en la implementación.

---

## ✨ Bonus: Aplicaciones típicas

- Encontrar caminos más baratos (no necesariamente más cortos).
- Funciona con **pesos negativos**, a diferencia de Dijkstra.
- Detecta ciclos negativos: Si después de `V - 1` iteraciones, podés seguir relajando, hay un ciclo negativo.

```
for (int i = 0; i < V - 1; ++i)
    for (auto &[u, v, w] : edges)
        if (dist[u] + w < dist[v])
            dist[v] = dist[u] + w;
```

Y para detectar ciclos negativos:

```
for (auto &[u, v, w] : edges)
    if (dist[u] + w < dist[v])
        return true; // hay ciclo negativo
```

---
