import pandas as pd
import matplotlib.pyplot as plt

clasica = pd.read_csv("tiempospart2.csv")
bloques = pd.read_csv("tiempospart3.csv")
clasica.columns = clasica.columns.str.strip()
bloques.columns = bloques.columns.str.strip()

plt.plot(clasica["N"], clasica["Tiempo"], marker="o", label="Clásica"
)

for bloque, datos_bloque in bloques.groupby("Bloque"):
    plt.plot(datos_bloque["N"], datos_bloque["Tiempo"], marker="o",
             label=f"Bloques {bloque}")

plt.xlabel("Tamaño de matriz N")
plt.ylabel("Tiempo (segundos)")
plt.title("Multiplicación clásica vs. por bloques")

plt.legend()
plt.grid()

plt.tight_layout()
plt.savefig("graficas/clasica_vs_bloques.png", dpi=180)
