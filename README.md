# T0 C++ IIC2233 (2019-2)
Versión en C++ de la T0 del ramo [IIC2233](https://github.com/iic2233) para el semestre 2019 - 2. 

## Estructura de Directorios

La estructura de directorios del proyecto es la siguiente:

```
T0-CPP-IIC2233-2019-2/
├── src/                # Código fuente del proyecto
│   ├── main.cpp        # Archivo principal
│   └── ...
├── include/            # Archivos de cabecera
│   └── ...
├── build/              # Archivos generados durante la compilación
├── python/             # Solución en Python de la Tarea
├── lib/                # Librerías externas (en desuso)
├── Enunciado.pdf       # Enunciado de la Tarea
├── Makefile            # Archivo Makefile para la compilación
└── README.md           # Documentación principal del proyecto
```

## Compilación y Ejecución

Para buildear

```bash
# Ir al directorio
cd T0-CPP-IIC2233-2019-2

# Buildear el proyecto
make
```

Los archivos generados se encontrarán en la carpeta `build`, para ejecutar simplemente
correr el binario `main`.

```bash
cd build

# En windows
./main.exe

# En linux
./main
```