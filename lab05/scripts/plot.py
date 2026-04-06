# Как в lab04: графики по .dat из data/task3_*
import matplotlib.pyplot as plt
import numpy as np
import os


def plot_task3_1():
    mu_values = [1, 10, 100, 1000]
    for name, ylabel, title_sfx in [
        ("theta", "Θ", "Θ(n)"),
        ("T", "T", "T(n)"),
    ]:
        plt.figure(figsize=(12, 8))
        for mu in mu_values:
            filename = f"data/task3_1/{name}_mu_{mu}.dat"
            if os.path.exists(filename):
                data = np.loadtxt(filename)
                plt.plot(data[:, 0], data[:, 1], linewidth=2, marker="o", markersize=3, label=f"μ={mu}")
        plt.title(f"Зависимость {title_sfx} (λ=10⁻⁶, m=1), различные μ", fontsize=14)
        plt.xlabel("n", fontsize=12)
        plt.ylabel(ylabel, fontsize=12)
        plt.grid(True, linestyle="--", alpha=0.7)
        if name == "theta":
            plt.yscale("log")
        plt.legend()
        plt.tight_layout()
        plt.savefig(f"graphs/task3_1/{name}.png", dpi=150)
        plt.close()


def plot_task3_2():
    lambda_values = [1e-7, 1e-6, 1e-5]
    for name, ylabel, title_sfx in [
        ("theta", "Θ", "Θ(n)"),
        ("T", "T", "T(n)"),
    ]:
        plt.figure(figsize=(12, 8))
        for lam in lambda_values:
            lam_str = f"{lam:.0e}".replace("+", "")
            filename = f"data/task3_2/{name}_lambda_{lam_str}.dat"
            if os.path.exists(filename):
                data = np.loadtxt(filename)
                plt.plot(
                    data[:, 0],
                    data[:, 1],
                    linewidth=2,
                    marker="o",
                    markersize=3,
                    label=f"λ={lam:.0e}",
                )
        plt.title(f"Зависимость {title_sfx} (μ=1, m=1), различные λ", fontsize=14)
        plt.xlabel("n", fontsize=12)
        plt.ylabel(ylabel, fontsize=12)
        plt.grid(True, linestyle="--", alpha=0.7)
        plt.yscale("log")
        plt.legend()
        plt.tight_layout()
        plt.savefig(f"graphs/task3_2/{name}.png", dpi=150)
        plt.close()


def plot_task3_3():
    m_values = [1, 2, 3]
    for name, ylabel, title_sfx in [
        ("theta", "Θ", "Θ(n)"),
        ("T", "T", "T(n)"),
    ]:
        plt.figure(figsize=(12, 8))
        for m in m_values:
            filename = f"data/task3_3/{name}_m_{m}.dat"
            if os.path.exists(filename):
                data = np.loadtxt(filename)
                plt.plot(data[:, 0], data[:, 1], linewidth=2, marker="o", markersize=3, label=f"m={m}")
        plt.title(f"Зависимость {title_sfx} (λ=10⁻⁶, μ=1), различные m", fontsize=14)
        plt.xlabel("n", fontsize=12)
        plt.ylabel(ylabel, fontsize=12)
        plt.grid(True, linestyle="--", alpha=0.7)
        if name == "theta":
            plt.yscale("log")
        plt.legend()
        plt.tight_layout()
        plt.savefig(f"graphs/task3_3/{name}.png", dpi=150)
        plt.close()


if __name__ == "__main__":
    for d in ["graphs/task3_1", "graphs/task3_2", "graphs/task3_3"]:
        os.makedirs(d, exist_ok=True)
    plot_task3_1()
    plot_task3_2()
    plot_task3_3()
    print("Графики: graphs/task3_*/theta.png и T.png")
