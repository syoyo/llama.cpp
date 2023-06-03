syoyo's modification to CUEW.

Currently tested on Ubuntu 20.04 x86-64 and Windows 10 64bit.

## Changes compared to original version

* Support CUDA 12.1
  * cuGetProcAddress is not supported.
* Support CUDNN 8.0.3

## Supported API

* [x] cuda.h
* [x] cudnn.h
* [x] nvrtc.h
* [x] cudaGL.h
  * [ ] Use cuda_gl_interop.h instead

## Experimental

See `experimental/cudart`.

* [x] cudart(CUDA runtime API)
* [x] cuBLAS
* [x] cuFFT
* [ ] cuRAND
  * [x] Host API
  * [ ] Device API
* [x] cuSparse
* [x] cuSolver
* [ ] nvJPEG

* [ ] ROCm HIP
  * `sandbox/hip/`

## Buld tests

### Linux

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

### Windows

```
> vcsetup-2019.bat
```

Then open .sln file in `build` folder.

## Add cuew to your project

Simply copy `include/cuew.h` and `src/cuew.c` to your project.

## Generate cuew(for developer)

You need python3.
Install pycparser.

```
$ python -m pip install pycparser
```

```
$ cd auto
# Edit header path in cuew_ge.py if required
$ ./cuew_gen.sh
```

### GL header

If you encounter the parse error on GL header, there is a work around.

Copy `cudaGL.h` to `mycudaGL.h` and remove `<GL/gl.h>` include line. and use `mycudaGL.h` as an input .h file.
Content of `<gl.h>` is not used when generating cuew header/source.

## Known issues

* Combining with Address Sanitizer(`-fsanitizer=address`) won't work
  * calling CUDA API results in undefined behavior or seg faults
  * https://github.com/google/sanitizers/issues/629
* CUEW does not report warning when using deprecated CUDA API
* `CUDA_API_PER_THREAD_DEFAULT_STREAM` is not supported.

## TODO

* [ ] Test on MSVC.
  * [x] `clang-cl` works
* [ ] Test CUDA-GL interop API
* [ ] Test cuDNN API call.
* [ ] Find a way to co-exist with Address Sanitizer
* [ ] `CUDA_API_PER_THREAD_DEFAULT_STREAM` support

=================

The CUDA Extension Wrangler Library (CUEW) is a cross-platform open-source
C/C++ extension loading library. CUEW provides efficient run-time mechanisms
for determining which CUDA functions and extensions extensions are supported
on the target platform.

CUDA core and extension functionality is exposed in a single header file.
CUEW has been tested on a variety of operating systems, including Windows,
Linux, Mac OS X.

LICENSE

CUEW library is released under the Apache 2.0 license.

