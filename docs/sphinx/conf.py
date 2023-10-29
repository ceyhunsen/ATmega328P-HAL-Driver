# Configuration file for Read The Docs.

import subprocess

project = "ATmega328P HAL Driver"
copyright = "2023, Ceyhun Şen"
author = "Ceyhun Şen"

html_extra_path = ["../build/html"]
html_path = ["../build/html"]

subprocess.call("cd ..; doxygen Doxyfile", shell = True)
