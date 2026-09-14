import pandas as pd
import matplotlib.pyplot as plt

clasica = pd.read_csv("tiempospart2.csv")
bloques = pd.read_csv("tiempospart3.csv")
strassen = pd.read_csv("tiempospart4.csv")
winograd = pd.read_csv("tiempospart5.csv")
clasica.columns = clasica.columns.str.strip()
bloques.columns = bloques.columns.str.strip()
strassen.columns = strassen.columns.str.strip()
winograd.columns = winograd.columns.str.strip()

plt.plot(clasica["N"], clasica["Tiempo"], marker="o", label="Clásica")
for bloque, datos_bloque in bloques.groupby("Bloque"):
    plt.plot(datos_bloque["N"], datos_bloque["Tiempo"], marker="o",
             label=f"Bloques {bloque}")
plt.plot(strassen["N"], strassen["Tiempo"], marker="o", label="Strassen")
plt.plot(winograd["N"], winograd["Tiempo"], marker="o", label="Winograd")

plt.xlabel("Tamaño de matriz N")
plt.ylabel("Tiempo (segundos)")
plt.title("Comparación de algoritmos de multiplicación")

plt.legend()
plt.grid()

plt.tight_layout()
plt.savefig("graficas/comparacion_algoritmos.png", dpi=180)
