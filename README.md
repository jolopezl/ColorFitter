[![Codacy Badge](https://api.codacy.com/project/badge/Grade/7198b51fe96c4c16a4d2b6a51d3e5cb5)](https://www.codacy.com?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=jolopezl/ColorFitter&amp;utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/jolopezl/colorfitter/badge)](https://www.codefactor.io/repository/github/jolopezl/colorfitter)

# ColorFitter
## Authors
William Brooks (<william.brooks@usm.cl>) and Jorge López (<jorge.lopez@physi.uni-heidelberg.de>)

## Requirements
Root and Boost.

## Building
Compile using `make`. The binary is then found in the folder `bin`. The Makefile may require some tweaking for your system, but changes should be minimal.

## Notes
To run ColorFitter, go to `run/test_*/` and call the fitter as `../../ifit.exe`. Note that you need to have the input data in that folder; the format is described in `source/ifit.cc`.

Look at the functions defined in `source/main.cc`, there `runColorFitter()` and `runColorFitterVariant()` are the most useful. The former one helps to set a complete fit configuring everything, and the latter runs defined fits.

The legacy analysis code, based on the HERMES data results, is available here: https://github.com/jolopezl/ColorFitter-AnalysisTools.
