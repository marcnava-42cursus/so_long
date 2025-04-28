#!/usr/bin/env python3
import os
import sys

def get_project_files(project_dir):
    """
    Recorre la carpeta project_dir y devuelve un conjunto con
    el nombre de todos los archivos encontrados.
    """
    project_files = set()
    for root, dirs, files in os.walk(project_dir):
        for f in files:
            project_files.add(f)
    return project_files

def process_file(input_file, project_files):
    """
    Procesa el archivo de Valgrind, asumiendo que cada bloque de error
    es seguido inmediatamente por su bloque de supresión (entre llaves).
    Si el bloque de error contiene el nombre de algún archivo del proyecto,
    se descarta la supresión; si no, se añade al resultado.
    Además, imprime mensajes de debug.
    """
    suppressions = []
    current_error_block = []
    current_supp_block = []
    state = "error"  # Comienza leyendo el bloque de error
    suppression_counter = 0

    with open(input_file, "r") as f:
        for line in f:
            # Si estamos en el bloque de error
            if state == "error":
                # Detectamos el comienzo de un bloque de supresión: línea que, al quitarle espacios, empieza con "{"
                if line.strip().startswith("{"):
                    state = "supp"
                    current_supp_block.append(line)
                else:
                    current_error_block.append(line)
            elif state == "supp":
                current_supp_block.append(line)
                # Si detectamos el cierre del bloque de supresión
                if "}" in line:
                    # Convertir bloques a texto
                    error_text = "".join(current_error_block)
                    supp_text = "".join(current_supp_block)
                    # Comprobar si el bloque de error contiene nombre de algún archivo del proyecto
                    if any(proj_file in error_text for proj_file in project_files):
                        print("Bloque descartado porque contiene un archivo del proyecto.")
                    else:
                        suppression_counter += 1
                        print("Supresión #{} añadida.".format(suppression_counter))
                        suppressions.append(supp_text)
                    # Reiniciar para el próximo par
                    current_error_block = []
                    current_supp_block = []
                    state = "error"

    print("Total de supresiones añadidas: {}".format(suppression_counter))
    return suppressions

def main():
    if len(sys.argv) < 2:
        print("Uso: {} archivo_input [archivo_output]".format(sys.argv[0]))
        sys.exit(1)
    input_file = sys.argv[1]
    output_file = sys.argv[2] if len(sys.argv) > 2 else None

    # Directorio donde se encuentran los archivos del proyecto.
    project_dir = "./_bonus/src/"
    project_files = get_project_files(project_dir)

    # Imprime la lista de archivos encontrados (ordenada alfabéticamente)
    print("Archivos encontrados en '{}':".format(project_dir))
    for f in sorted(project_files):
        print(" -", f)

    # Procesa el archivo de entrada y obtiene las supresiones correspondientes.
    suppressions = process_file(input_file, project_files)
    result = "\n\n".join(suppressions)

    if output_file:
        with open(output_file, "w") as f:
            f.write(result)
        print("Supresiones guardadas en '{}'".format(output_file))
    else:
        print("Contenido final de supresiones:")
        print(result)

if __name__ == '__main__':
    main()
