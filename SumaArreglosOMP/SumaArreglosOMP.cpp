#include <iostream>
#include <vector>
#include <omp.h>

#define N 500000      //100,000
#define chunk 100    //Tamaño 
#define mostrar 15    //primeros 15

void imprimeArreglo(const std::vector<float>& d);

int main()
{
    std::cout << "Arreglos en Paralelo\n";
    std::cout << "N = " << N << ", chunk = " << chunk << ", mostrar = " << mostrar << "\n\n";

    //arreglos dinamicos
    std::vector<float> a(N), b(N), c(N);

    //arreglos a y b
    for (int i = 0; i < N; i++)
    {
        a[i] = i * 10.0f;
        b[i] = (i + 3) * 3.7f;
    }

    //cantidad maxima de hilos disponibles
    int maxHilos = omp_get_max_threads();
    std::cout << "Max threads disponibles = " << maxHilos << "\n";

    //tiempo paralelo
    double start = omp_get_wtime();

    int hilosUsados = 0;

#pragma omp parallel
    {
#pragma omp single
        {
            hilosUsados = omp_get_num_threads();
        }

#pragma omp for schedule(static, chunk)
        for (int i = 0; i < N; i++)
        {
            c[i] = a[i] + b[i];
        }
    }

    double end = omp_get_wtime();

    std::cout << "Threads usados en la ejecucion = " << hilosUsados << "\n";
    std::cout << "Tiempo paralelo: " << (end - start) << " segundos\n\n";

    // Arreglos para sus primeros valores
    std::cout << "Arreglo A (primeros " << mostrar << "):\n";
    imprimeArreglo(a);

    std::cout << "Arreglo B (primeros " << mostrar << "):\n";
    imprimeArreglo(b);

    std::cout << "Arreglo C = A+B (primeros " << mostrar << "):\n";
    imprimeArreglo(c);

    return 0;
}

void imprimeArreglo(const std::vector<float>& d)
{
    for (int i = 0; i < mostrar; i++)
        std::cout << d[i] << " - ";

    std::cout << "\n\n";
}
