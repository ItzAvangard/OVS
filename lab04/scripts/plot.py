# scripts/plot.py
import matplotlib.pyplot as plt
import numpy as np
import os

# Задание 2.1: Θ(n) для различных μ
def plot_task2_1():
    mu_values = [1, 10, 100, 1000]
    plt.figure(figsize=(12, 8))
    
    for mu in mu_values:
        filename = f"data/task2_1/theta_mu_{mu}.dat"
        if os.path.exists(filename):
            data = np.loadtxt(filename)
            plt.plot(data[:, 0], data[:, 1], linewidth=2, label=f"μ={mu}")
    
    plt.title("Зависимость Θ(n) для различных значений μ", fontsize=14)
    plt.xlabel("n", fontsize=12)
    plt.ylabel("Θ", fontsize=12)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.yscale('log')
    plt.legend()
    plt.tight_layout()
    plt.savefig("graphs/task2_1/theta.png", dpi=150)
    plt.close()

# Задание 2.2: Θ(n) для различных λ
def plot_task2_2():
    lambda_values = [1e-5, 1e-6, 1e-7, 1e-8, 1e-9]
    plt.figure(figsize=(12, 8))
    
    for lam in lambda_values:
        lam_str = f"{lam:.0e}".replace('+', '')
        filename = f"data/task2_2/theta_lambda_{lam_str}.dat"
        if os.path.exists(filename):
            data = np.loadtxt(filename)
            plt.plot(data[:, 0], data[:, 1], linewidth=2, label=f"λ={lam:.0e}")
    
    plt.title("Зависимость Θ(n) для различных значений λ", fontsize=14)
    plt.xlabel("n", fontsize=12)
    plt.ylabel("Θ", fontsize=12)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.yscale('log')
    plt.legend()
    plt.tight_layout()
    plt.savefig("graphs/task2_2/theta.png", dpi=150)
    plt.close()

# Задание 2.3: Θ(n) для различных m
def plot_task2_3():
    m_values = [1, 2, 3, 4]
    plt.figure(figsize=(12, 8))
    
    for m in m_values:
        filename = f"data/task2_3/theta_m_{m}.dat"
        if os.path.exists(filename):
            data = np.loadtxt(filename)
            plt.plot(data[:, 0], data[:, 1], linewidth=2, label=f"m={m}")
    
    plt.title("Зависимость Θ(n) для различных значений m", fontsize=14)
    plt.xlabel("n", fontsize=12)
    plt.ylabel("Θ", fontsize=12)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.yscale('log')
    plt.legend()
    plt.tight_layout()
    plt.savefig("graphs/task2_3/theta.png", dpi=150)
    plt.close()

# Задание 3.1: T(n) для различных μ
def plot_task3_1():
    mu_values = [1, 2, 4, 6]
    plt.figure(figsize=(12, 8))
    
    for mu in mu_values:
        filename = f"data/task3_1/T_mu_{mu}.dat"
        if os.path.exists(filename):
            data = np.loadtxt(filename)
            plt.plot(data[:, 0], data[:, 1], linewidth=2, marker='o', markersize=4, label=f"μ={mu}")
    
    plt.title("Зависимость T(n) для различных значений μ", fontsize=14)
    plt.xlabel("n", fontsize=12)
    plt.ylabel("T", fontsize=12)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend()
    plt.tight_layout()
    plt.savefig("graphs/task3_1/T.png", dpi=150)
    plt.close()

# Задание 3.2: T(n) для различных λ
def plot_task3_2():
    lambda_values = [1e-5, 1e-6, 1e-7, 1e-8, 1e-9]
    plt.figure(figsize=(12, 8))
    
    for lam in lambda_values:
        lam_str = f"{lam:.0e}".replace('+', '')
        filename = f"data/task3_2/T_lambda_{lam_str}.dat"
        if os.path.exists(filename):
            data = np.loadtxt(filename)
            plt.plot(data[:, 0], data[:, 1], linewidth=2, marker='o', markersize=4, label=f"λ={lam:.0e}")
    
    plt.title("Зависимость T(n) для различных значений λ", fontsize=14)
    plt.xlabel("n", fontsize=12)
    plt.ylabel("T", fontsize=12)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.yscale('log')
    plt.legend()
    plt.tight_layout()
    plt.savefig("graphs/task3_2/T.png", dpi=150)
    plt.close()

# Задание 3.3: T(n) для различных m
def plot_task3_3():
    m_values = [1, 2, 3, 4]
    plt.figure(figsize=(12, 8))
    
    for m in m_values:
        filename = f"data/task3_3/T_m_{m}.dat"
        if os.path.exists(filename):
            data = np.loadtxt(filename)
            plt.plot(data[:, 0], data[:, 1], linewidth=2, marker='o', markersize=4, label=f"m={m}")
    
    plt.title("Зависимость T(n) для различных значений m", fontsize=14)
    plt.xlabel("n", fontsize=12)
    plt.ylabel("T", fontsize=12)
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend()
    plt.tight_layout()
    plt.savefig("graphs/task3_3/T.png", dpi=150)
    plt.close()

if __name__ == "__main__":
    os.makedirs("graphs/task2_1", exist_ok=True)
    os.makedirs("graphs/task2_2", exist_ok=True)
    os.makedirs("graphs/task2_3", exist_ok=True)
    os.makedirs("graphs/task3_1", exist_ok=True)
    os.makedirs("graphs/task3_2", exist_ok=True)
    os.makedirs("graphs/task3_3", exist_ok=True)
    
    plot_task2_1()
    plot_task2_2()
    plot_task2_3()
    plot_task3_1()
    plot_task3_2()
    plot_task3_3()
    
    print("Graphs generated successfully")