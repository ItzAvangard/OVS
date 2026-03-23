#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifdef _WIN32
    #include <direct.h>
    #define CREATE_DIR(path) _mkdir(path)
#else
    #include <sys/stat.h>
    #define CREATE_DIR(path) mkdir(path, 0755)
#endif

// Преобразование числа в научный формат без знака +
void to_scientific_string(double value, char *buffer, size_t size)
{
    snprintf(buffer, size, "%.0e", value);
    for (char *p = buffer; *p; p++) {
        if (*p == '+') {
            memmove(p, p + 1, strlen(p + 1) + 1);
            break;
        }
    }
}

// Интенсивность восстановления при l отказавших ЭМ
double mu_l(int l, int N, int m, double mu)
{
    if (N - m <= l) {
        return (N - l) * mu;
    }
    return m * mu;
}

// Среднее время наработки до отказа
double calc_Theta(int N, int n, double lambda, double mu, int m)
{
    double sum = 0.0;
    for (int j = n + 1; j <= N; j++) {
        double mul = 1.0;
        for (int l = n; l <= j - 1; l++) {
            mul *= mu_l(l, N, m, mu) / (l * lambda);
        }
        sum += mul / (j * lambda);
    }
    return sum + 1.0 / (n * lambda);
}

// Среднее время восстановления
double calc_T(int N, int n, double lambda, double mu, int m)
{
    double T = 1.0 / mu_l(0, N, m, mu);
    if (n == 1) {
        return T;
    }
    
    double mul = 1.0;
    for (int l = 1; l <= n - 1; l++) {
        mul *= l * lambda / mu_l(l, N, m, mu);
    }
    T *= mul;
    
    double sum = 0.0;
    for (int j = 1; j <= n - 1; j++) {
        mul = 1.0;
        for (int l = j; l <= n - 1; l++) {
            mul *= l * lambda / mu_l(l, N, m, mu);
        }
        sum += mul / (j * lambda);
    }
    return T + sum;
}

// Задание 2.1: Θ(n) для различных μ
void task2_1()
{
    int N = 65536;
    double lambda = 1e-5;
    int m = 1;
    double mu_values[] = {1, 10, 100, 1000};
    
    for (int i = 0; i < 4; i++) {
        double mu = mu_values[i];
        char filename[256];
        snprintf(filename, sizeof(filename), "data/task2_1/theta_mu_%.0f.dat", mu);
        FILE *f = fopen(filename, "w");
        if (!f) continue;
        
        for (int n = 65527; n <= 65536; n++) {
            fprintf(f, "%d %.16e\n", n, calc_Theta(N, n, lambda, mu, m));
        }
        fclose(f);
    }
}

// Задание 2.2: Θ(n) для различных λ
void task2_2()
{
    int N = 65536;
    double mu = 1;
    int m = 1;
    double lambda_values[] = {1e-5, 1e-6, 1e-7, 1e-8, 1e-9};
    
    for (int i = 0; i < 5; i++) {
        double lambda = lambda_values[i];
        char filename[256];
        char lam_str[32];
        to_scientific_string(lambda, lam_str, sizeof(lam_str));
        snprintf(filename, sizeof(filename), "data/task2_2/theta_lambda_%s.dat", lam_str);
        FILE *f = fopen(filename, "w");
        if (!f) continue;
        
        for (int n = 65527; n <= 65536; n++) {
            fprintf(f, "%d %.16e\n", n, calc_Theta(N, n, lambda, mu, m));
        }
        fclose(f);
    }
}

// Задание 2.3: Θ(n) для различных m
void task2_3()
{
    int N = 65536;
    double mu = 1;
    double lambda = 1e-5;
    int m_values[] = {1, 2, 3, 4};
    
    for (int i = 0; i < 4; i++) {
        int m = m_values[i];
        char filename[256];
        snprintf(filename, sizeof(filename), "data/task2_3/theta_m_%d.dat", m);
        FILE *f = fopen(filename, "w");
        if (!f) continue;
        
        for (int n = 65527; n <= 65536; n++) {
            fprintf(f, "%d %.16e\n", n, calc_Theta(N, n, lambda, mu, m));
        }
        fclose(f);
    }
}

// Задание 3.1: T(n) для различных μ
void task3_1()
{
    int N = 1000;
    double lambda = 1e-3;
    int m = 1;
    double mu_values[] = {1, 2, 4, 6};
    
    for (int i = 0; i < 4; i++) {
        double mu = mu_values[i];
        char filename[256];
        snprintf(filename, sizeof(filename), "data/task3_1/T_mu_%.0f.dat", mu);
        FILE *f = fopen(filename, "w");
        if (!f) continue;
        
        for (int n = 900; n <= 1000; n += 10) {
            fprintf(f, "%d %.16e\n", n, calc_T(N, n, lambda, mu, m));
        }
        fclose(f);
    }
}

// Задание 3.2: T(n) для различных λ
void task3_2()
{
    int N = 8192;
    double mu = 1;
    int m = 1;
    double lambda_values[] = {1e-5, 1e-6, 1e-7, 1e-8, 1e-9};
    
    for (int i = 0; i < 5; i++) {
        double lambda = lambda_values[i];
        char filename[256];
        char lam_str[32];
        to_scientific_string(lambda, lam_str, sizeof(lam_str));
        snprintf(filename, sizeof(filename), "data/task3_2/T_lambda_%s.dat", lam_str);
        FILE *f = fopen(filename, "w");
        if (!f) continue;
        
        for (int n = 8092; n <= 8192; n += 10) {
            fprintf(f, "%d %.16e\n", n, calc_T(N, n, lambda, mu, m));
        }
        fclose(f);
    }
}

// Задание 3.3: T(n) для различных m
void task3_3()
{
    int N = 8192;
    double mu = 1;
    double lambda = 1e-5;
    int m_values[] = {1, 2, 3, 4};
    
    for (int i = 0; i < 4; i++) {
        int m = m_values[i];
        char filename[256];
        snprintf(filename, sizeof(filename), "data/task3_3/T_m_%d.dat", m);
        FILE *f = fopen(filename, "w");
        if (!f) continue;
        
        for (int n = 8092; n <= 8192; n += 10) {
            fprintf(f, "%d %.16e\n", n, calc_T(N, n, lambda, mu, m));
        }
        fclose(f);
    }
}

int main()
{
    CREATE_DIR("data");
    CREATE_DIR("data/task2_1");
    CREATE_DIR("data/task2_2");
    CREATE_DIR("data/task2_3");
    CREATE_DIR("data/task3_1");
    CREATE_DIR("data/task3_2");
    CREATE_DIR("data/task3_3");
    CREATE_DIR("graphs");
    CREATE_DIR("graphs/task2_1");
    CREATE_DIR("graphs/task2_2");
    CREATE_DIR("graphs/task2_3");
    CREATE_DIR("graphs/task3_1");
    CREATE_DIR("graphs/task3_2");
    CREATE_DIR("graphs/task3_3");
    
    task2_1();
    task2_2();
    task2_3();
    task3_1();
    task3_2();
    task3_3();
    
    printf("Data generated successfully\n");
    return 0;
}