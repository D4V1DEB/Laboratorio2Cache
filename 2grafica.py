import pandas as pd
import matplotlib.pyplot as plt

datos = pd.read_csv("tiempospart2.csv")
datos.columns = datos.columns.str.strip()

plt.plot(datos["N"],datos["Tiempo"],marker="o")

plt.xlabel("Tamaño de la matriz N")
plt.ylabel("Tiempo (segundos)")
plt.title("Multiplicación clásica de matrices")

plt.grid()
plt.tight_layout()
plt.savefig("graficas/multiplicacion_clasica.png", dpi=180)
