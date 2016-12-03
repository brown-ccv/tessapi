# tessapi

## Introduction

**tessapi** provides python bindings to the
[C++ API](https://github.com/tesseract-ocr/tesseract/wiki/APIExample)
for the
[Tesseract OCR](https://github.com/tesseract-ocr/tesseract)
engine. It has been developed by the
[CIS Data Science Practice](https://brown.edu/cis/data-science)
at Brown University, primarily to support
[georeg](https://bitbucket.org/brown-data-science/georeg),
a research prototype for extracting addresses and other business information
from historical registries.

## License

**tessapi** is freely available for non-commercial use. Please see the included
file `LICENSE.txt` for more details.

## Dependencies

* gcc >= 4.8.2
* tesseract >= 3.04
* eigen >= 3.2.1

## Build instructions for Oscar at CCV

    module load gcc/4.8.2 tesseract/3.04 eigen/3.2.1
    export CPATH="/gpfs/runtime/opt/eigen/3.2.1/include/eigen3:$CPATH"
    python setup.py clean --all
    python setup.py build_ext --rpath $LD_RUN_PATH
    python setup.py install
