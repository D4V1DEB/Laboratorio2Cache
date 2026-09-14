import pandas as pd
import matplotlib.pyplot as plt

datos = pd.read_csv("tiempospart1.csv")
datos.columns = datos.columns.str.strip()

plt.plot(datos["N"],datos["Tiempo1"],marker="o",label="Recorrido por filas")
plt.plot(datos["N"],datos["Tiempo2"],marker="o",label="Recorrido por columnas")

plt.xlabel("Tamaño N")
plt.ylabel("Tiempo (segundos)")
plt.title("Comparación de bucles anidados")
plt.legend()
plt.grid()

plt.tight_layout()
plt.savefig("graficas/bucles_anidados.png", dpi=180)
