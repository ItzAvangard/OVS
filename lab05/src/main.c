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

/* Как в lab04: преобразование λ в строку для имён файлов */
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

double mu_l(int l, int N, int m, double mu)
{
    if (N - m <= l) {
        return (N - l) * mu;
    }
    return m * mu;
}

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

/* Частотный метод; O(n) — иначе при n ~ 65536 невозможно */
double calc_T(int N, int n, double lambda, double mu, int m)
{
    if (n == 1) {
        return 1.0 / mu_l(0, N, m, mu);
    }

    double *a = calloc((size_t)n, sizeof(double));
    double *P = calloc((size_t)(n + 1), sizeof(double));
    if (!a || !P) {
        free(a);
        free(P);
        return NAN;
    }

    for (int l = 1; l <= n - 1; l++) {
        a[l] = (l * lambda) / mu_l(l, N, m, mu);
    }
    P[n] = 1.0;
    for (int j = n - 1; j >= 1; j--) {
        P[j] = a[j] * P[j + 1];
    }

    double T0 = (1.0 / mu_l(0, N, m, mu)) * P[1];
    double sum = 0.0;
    for (int j = 1; j <= n - 1; j++) {
        sum += P[j] / (j * lambda);
    }
    free(a);
    free(P);
    return T0 + sum;
}

#define LAB_N 65536
#define LAB_N_MIN 65527
#define LAB_N_MAX 65536

static void write_series_theta_T(int N, int n_min, int n_max, double lambda, double mu, int m,
                                 const char *path_theta, const char *path_T)
{
    FILE *ft = fopen(path_theta, "w");
    FILE *fT = fopen(path_T, "w");
    if (!ft || !fT) {
        if (ft) {
            fclose(ft);
        }
        if (fT) {
            fclose(fT);
        }
        return;
    }
    for (int n = n_min; n <= n_max; n++) {
        fprintf(ft, "%d %.16e\n", n, calc_Theta(N, n, lambda, mu, m));
        fprintf(fT, "%d %.16e\n", n, calc_T(N, n, lambda, mu, m));
    }
    fclose(ft);
    fclose(fT);
}

/* λ=10^-6, m=1; μ ∈ {1,10,100,1000} */
void task3_1(void)
{
    int N = LAB_N;
    double lambda = 1e-6;
    int m = 1;
    double mu_values[] = {1, 10, 100, 1000};

    for (int i = 0; i < 4; i++) {
        double mu = mu_values[i];
        char path_theta[320];
        char path_T[320];
        snprintf(path_theta, sizeof(path_theta), "data/task3_1/theta_mu_%.0f.dat", mu);
        snprintf(path_T, sizeof(path_T), "data/task3_1/T_mu_%.0f.dat", mu);
        write_series_theta_T(N, LAB_N_MIN, LAB_N_MAX, lambda, mu, m, path_theta, path_T);
    }
}

/* μ=1, m=1; λ ∈ {10^-7, 10^-6, 10^-5} */
void task3_2(void)
{
    int N = LAB_N;
    double mu = 1;
    int m = 1;
    double lambda_values[] = {1e-7, 1e-6, 1e-5};

    for (int i = 0; i < 3; i++) {
        double lambda = lambda_values[i];
        char lam_str[32];
        char path_theta[320];
        char path_T[320];
        to_scientific_string(lambda, lam_str, sizeof(lam_str));
        snprintf(path_theta, sizeof(path_theta), "data/task3_2/theta_lambda_%s.dat", lam_str);
        snprintf(path_T, sizeof(path_T), "data/task3_2/T_lambda_%s.dat", lam_str);
        write_series_theta_T(N, LAB_N_MIN, LAB_N_MAX, lambda, mu, m, path_theta, path_T);
    }
}

/* λ=10^-6, μ=1; m ∈ {1,2,3} */
void task3_3(void)
{
    int N = LAB_N;
    double mu = 1;
    double lambda = 1e-6;
    int m_values[] = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        int m = m_values[i];
        char path_theta[320];
        char path_T[320];
        snprintf(path_theta, sizeof(path_theta), "data/task3_3/theta_m_%d.dat", m);
        snprintf(path_T, sizeof(path_T), "data/task3_3/T_m_%d.dat", m);
        write_series_theta_T(N, LAB_N_MIN, LAB_N_MAX, lambda, mu, m, path_theta, path_T);
    }
}

/* Таблица: №, λ, μ, m, n, θ, T */
void write_table(void)
{
    int N = LAB_N;
    double lambda_values[] = {1e-7, 1e-6, 1e-5};
    double mu_values[] = {1, 10, 100, 1000};
    int m_values[] = {1, 2, 3};

    FILE *f = fopen("data/table.csv", "w");
    if (!f) {
        return;
    }
    fprintf(f, "\xEF\xBB\xBF");
    fprintf(f, "No,lambda,mu,m,n,theta,T\n");

    int no = 1;
    for (int li = 0; li < 3; li++) {
        double lambda = lambda_values[li];
        for (int mi = 0; mi < 4; mi++) {
            double mu = mu_values[mi];
            for (int mj = 0; mj < 3; mj++) {
                int m = m_values[mj];
                for (int n = LAB_N_MIN; n <= LAB_N_MAX; n++) {
                    double th = calc_Theta(N, n, lambda, mu, m);
                    double T = calc_T(N, n, lambda, mu, m);
                    fprintf(f, "%d,%.16e,%.16e,%d,%d,%.16e,%.16e\n",
                            no, lambda, mu, m, n, th, T);
                    no++;
                }
            }
        }
    }
    fclose(f);
}

int main(void)
{
    CREATE_DIR("data");
    CREATE_DIR("data/task3_1");
    CREATE_DIR("data/task3_2");
    CREATE_DIR("data/task3_3");
    CREATE_DIR("graphs");
    CREATE_DIR("graphs/task3_1");
    CREATE_DIR("graphs/task3_2");
    CREATE_DIR("graphs/task3_3");

    task3_1();
    task3_2();
    task3_3();
    write_table();

    printf("OK: data/table.csv, data/task3_*/\n");
    return 0;
}
