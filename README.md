# CVM-H

[![License](https://img.shields.io/badge/License-BSD_3--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
![GitHub repo size](https://img.shields.io/github/repo-size/sceccode/cvmh)
[![cvmh-ucvm-ci Actions Status](https://github.com/SCECcode/cvmh/workflows/cvmh-ucvm-ci/badge.svg)](https://github.com/SCECcode/cvmh/actions)


Southern California Velocity Model developed by Harvard Structural Geology Group
with optional geotechnical layer

The SCEC CVM-H velocity model describes seismic P- and S-wave velocities and densities,
and is comprised of basin structures embedded in tomographic and teleseismic crust and 
upper mantle models. This latest release of the CVM-H (15.1.1) represents the integration 
of various model components, including fully 3D waveform tomographic results.

## Installation

This package is intended to be installed as part of the UCVM framework,
version 25.x or higher.

## Contact the authors

If you would like to contact the authors regarding this software,
please e-mail software@scec.org. Note this e-mail address should
be used for questions regarding the software itself (e.g. how
do I link the library properly?). Questions regarding the model's
science (e.g. on what paper is the CVMH based?) should be directed
to the model's authors, located in the AUTHORS file.

## To build in standalone mode

To install this package on your computer, please run the following commands:

<pre>
  aclocal -I m4
  autoconf
  automake --add-missing -f
  ./configure --prefix=folder/to/install/to
  cd model; ./make_data_files.py -d cvmh1511 -u uid
  make
  make install
</pre>

For documentation, please see http://scec.usc.edu/scecpedia/CVM-H.

