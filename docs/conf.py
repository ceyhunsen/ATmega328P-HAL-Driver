# Configuration file for Read The Docs.

import subprocess

project = "ATmega328P HAL Driver"
copyright = "2022, Ceyhun Şen"
author = "Ceyhun Şen"
html_extra_path = ["build/html"]

subprocess.call("doxygen Doxyfile", shell = True)
