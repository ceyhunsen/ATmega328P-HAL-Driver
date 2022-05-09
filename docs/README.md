# Documentation

Documentation is available online at [http://atmega328p-hal-driver.rtfd.io/](http://atmega328p-hal-driver.rtfd.io/). Also can be created offline.

## Creating Documents Offline

This project uses Doxygen and Sphinx to create documents. So, prerequisites are:

* Doxygen
* Python 3
* Python 3 pip
* Make

Install absent programs and run these commands in this directory to create documents:

```bash
pip3 install -r requirements.txt
make html
```

Then navigate `build/html/` and open `index.html` file with your favorite browser.
