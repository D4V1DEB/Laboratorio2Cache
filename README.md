# Ejecución

```bash
cmake -S . -B build
cmake --build build --target laboratorio -j2
kcachegrind perfiles/cachegrind_clasica.out perfiles/cachegrind_bloques.out
```
