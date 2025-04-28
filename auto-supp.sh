#!/bin/bash
# Paso 1: Ejecutar Valgrind para generar el log (memcheck.log)
echo "Ejecutando Valgrind para generar memcheck.log..."
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --log-fd=42 --gen-suppressions=all -s ./so_long maps/sample.ber 42>>memcheck.log

# Paso 2: Ejecutar el script Python para filtrar y generar el archivo de supresiones.
# Asegúrate de tener el script 'filtra_sups_debug.py' en el mismo directorio o ajusta la ruta.
echo "Ejecutando el script Python para filtrar supresiones..."
python3 gen_suppressions.py memcheck.log valgrind.supp

# Paso 3: Eliminar el log temporal memcheck.log
echo "Eliminando memcheck.log..."
rm memcheck.log

# Paso 4: Ejecutar Valgrind utilizando el archivo de supresiones generado.
echo "Ejecutando Valgrind usando valgrind.supp..."
valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --suppressions=valgrind.supp -s --log-file=valgrind.log ./so_long maps/sample.ber
