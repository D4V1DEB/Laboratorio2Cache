import pandas as pd
import matplotlib.pyplot as plt

clasica = pd.read_csv("tiempospart2.csv")
bloques = pd.read_csv("tiempospart3.csv")
strassen = pd.read_csv("tiempospart4.csv")

bloque32 = bloques[bloques["Bloque"] == 32]

plt.plot(clasica["N"], clasica["Tiempo"], marker="o", label="Clásica")
plt.plot(bloque32["N"], bloque32["Tiempo"], marker="o", label="Bloques 32")
plt.plot(strassen["N"], strassen["Tiempo"], marker="o", label="Strassen")

plt.xlabel("Tamaño de matriz N")
plt.ylabel("Tiempo (segundos)")
plt.title("Multiplicación clásica vs. por bloques vs. Strassen")

plt.legend()
plt.grid()

plt.show()
