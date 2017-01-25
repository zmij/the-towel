# The Towel
## Accompanying code for "Hitchhiker's Guide to C++ Metaprogramming"

Sergei Fedorov, "Hitchhiker's Guide to C++ Metaprogramming", *ISBN 978-1-78712-891-0* will be published in 2017 Q2

### Namespace for the code

All code will be wrapped in `hgcm` namespace which stands for the name of the course.

### Building the Code

To build the code you'll need `cmake` and [Google Test library](https://github.com/google/googletest)

```bash
# Clone the code
git clone git@github.com:zmij/the-towel.git
# Or https variant
git clone https://github.com/zmij/cpp-meta-book.git

# Building with GCC 5.* example
mkdir -p build/gcc5
cd build/gcc5
cmake ../.. -DCMAKE_CXX_COMPILER=g++-5 -DCMAKE_CC_COMPILER=gcc-5
make && make test

```
