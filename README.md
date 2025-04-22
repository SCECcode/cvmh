# CVM-H

Southern California Velocity Model developed by Harvard Structural Geology Group
with optional geotechnical layer

## Installation

This package is intended to be installed as part of the UCVM framework,
version 19.4.0 or higher.

## Contact the authors

If you would like to contact the authors regarding this software,
please e-mail software@scec.org. Note this e-mail address should
be used for questions regarding the software itself (e.g. how
do I link the library properly?). Questions regarding the model's
science (e.g. on what paper is the CVMH based?) should be directed
to the model's authors, located in the AUTHORS file.


CVM-H 15.1.0 README

To install this package on your computer, please run the following commands:

libtoolize
aclocal
automake --add-missing -f
autoconf
./configure --prefix=folder/to/install/to
cd model; ./make_data_files.py -d cvmh1511 -u uid
make
make install

For documentation, please see http://scec.usc.edu/scecpedia/CVM-H.

If you have questions, please contact software@scec.org and we will be happy to assist
you in installing this software.

