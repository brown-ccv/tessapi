# Dependencies

gcc >= 4.8.2
tesseract >= 3.04
eigen >= 3.2.1

# Build instructions for CCV

module load gcc/4.8.2 tesseract/3.04 eigen/3.2.1
export CPATH="/gpfs/runtime/opt/eigen/3.2.1/include/eigen3:$CPATH"
python setup.py clean --all
python setup.py build_ext --rpath $LD_RUN_PATH
python setup.py install
