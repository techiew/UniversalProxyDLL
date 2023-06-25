import sys
import os
import subprocess
import pefile

if len(sys.argv) != 2:
    print("Argument error")
    print("Usage: python create_export_ordinals.py <num_ordinals_to_export>")
    sys.exit(1)

num_columns = 50
num_ordinals_to_export = sys.argv[1]
with open("export_ordinals.txt", "w") as file:
    for i in range(1, int(num_ordinals_to_export) + 1):
        file.write("ExportOrdinal(" + str(i) + ") ")
        if i % num_columns == 0:
            file.write("\n")

