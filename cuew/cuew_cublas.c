

#ifdef _MSC_VER
#  if _MSC_VER < 1900
#    define snprintf _snprintf
#  endif
#  define popen _popen
#  define pclose _pclose
#  define _CRT_SECURE_NO_WARNINGS
#endif
#include "cuew.h"
#include "cuew_cublas.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>


#ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  define VC_EXTRALEAN
#  include <windows.h>


/* Utility macros. */

typedef HMODULE DynamicLibrary;

#  define dynamic_library_open(path)         LoadLibraryA(path)
#  define dynamic_library_close(lib)         FreeLibrary(lib)
#  define dynamic_library_find(lib, symbol)  GetProcAddress(lib, symbol)
#else
#  include <dlfcn.h>

typedef void* DynamicLibrary;

#  define dynamic_library_open(path)         dlopen(path, RTLD_NOW)
#  define dynamic_library_close(lib)         dlclose(lib)
#  define dynamic_library_find(lib, symbol)  dlsym(lib, symbol)
#endif

/*
#define CUEW_IMPL_LIBRARY_FIND_CHECKED(lib, name)         name = (t##name *)dynamic_library_find(lib, #name);         assert(name);
*/

#define CUEW_IMPL_LIBRARY_FIND(lib, name)         name = (t##name *)dynamic_library_find(lib, #name);


static DynamicLibrary dynamic_library_open_find(const char **paths) {
  int i = 0;
  while (paths[i] != NULL) {
      DynamicLibrary lib = dynamic_library_open(paths[i]);
      if (lib != NULL) {
        return lib;
      }
      ++i;
  }
  return NULL;
}

/*#define CUBLAS_LIBRARY_FIND_CHECKED(name) CUEW_IMPL_LIBRARY_FIND_CHECKED(cublas_lib, name)*/
#define CUBLAS_LIBRARY_FIND(name) CUEW_IMPL_LIBRARY_FIND(cublas_lib, name)
static DynamicLibrary cublas_lib;

static void cuewExitCUBLAS(void) {
  if (cublas_lib != NULL) {
    /* ignore errors */
    dynamic_library_close(cublas_lib);
    cublas_lib = NULL;
  }
}

tcublasCreate_v2 *cublasCreate_v2;
tcublasDestroy_v2 *cublasDestroy_v2;
tcublasGetVersion_v2 *cublasGetVersion_v2;
tcublasGetProperty *cublasGetProperty;
tcublasGetCudartVersion *cublasGetCudartVersion;
tcublasSetWorkspace_v2 *cublasSetWorkspace_v2;
tcublasSetStream_v2 *cublasSetStream_v2;
tcublasGetStream_v2 *cublasGetStream_v2;
tcublasGetPointerMode_v2 *cublasGetPointerMode_v2;
tcublasSetPointerMode_v2 *cublasSetPointerMode_v2;
tcublasGetAtomicsMode *cublasGetAtomicsMode;
tcublasSetAtomicsMode *cublasSetAtomicsMode;
tcublasGetMathMode *cublasGetMathMode;
tcublasSetMathMode *cublasSetMathMode;
tcublasGetSmCountTarget *cublasGetSmCountTarget;
tcublasSetSmCountTarget *cublasSetSmCountTarget;
tcublasGetStatusName *cublasGetStatusName;
tcublasGetStatusString *cublasGetStatusString;
tcublasLoggerConfigure *cublasLoggerConfigure;
tcublasSetLoggerCallback *cublasSetLoggerCallback;
tcublasGetLoggerCallback *cublasGetLoggerCallback;
tcublasSetVector *cublasSetVector;
tcublasSetVector_64 *cublasSetVector_64;
tcublasGetVector *cublasGetVector;
tcublasGetVector_64 *cublasGetVector_64;
tcublasSetMatrix *cublasSetMatrix;
tcublasSetMatrix_64 *cublasSetMatrix_64;
tcublasGetMatrix *cublasGetMatrix;
tcublasGetMatrix_64 *cublasGetMatrix_64;
tcublasSetVectorAsync *cublasSetVectorAsync;
tcublasSetVectorAsync_64 *cublasSetVectorAsync_64;
tcublasGetVectorAsync *cublasGetVectorAsync;
tcublasGetVectorAsync_64 *cublasGetVectorAsync_64;
tcublasSetMatrixAsync *cublasSetMatrixAsync;
tcublasSetMatrixAsync_64 *cublasSetMatrixAsync_64;
tcublasGetMatrixAsync *cublasGetMatrixAsync;
tcublasGetMatrixAsync_64 *cublasGetMatrixAsync_64;
tcublasXerbla *cublasXerbla;
tcublasNrm2Ex *cublasNrm2Ex;
tcublasNrm2Ex_64 *cublasNrm2Ex_64;
tcublasSnrm2_v2 *cublasSnrm2_v2;
tcublasSnrm2_v2_64 *cublasSnrm2_v2_64;
tcublasDnrm2_v2 *cublasDnrm2_v2;
tcublasDnrm2_v2_64 *cublasDnrm2_v2_64;
tcublasScnrm2_v2 *cublasScnrm2_v2;
tcublasScnrm2_v2_64 *cublasScnrm2_v2_64;
tcublasDznrm2_v2 *cublasDznrm2_v2;
tcublasDznrm2_v2_64 *cublasDznrm2_v2_64;
tcublasDotEx *cublasDotEx;
tcublasDotEx_64 *cublasDotEx_64;
tcublasDotcEx *cublasDotcEx;
tcublasDotcEx_64 *cublasDotcEx_64;
tcublasSdot_v2 *cublasSdot_v2;
tcublasSdot_v2_64 *cublasSdot_v2_64;
tcublasDdot_v2 *cublasDdot_v2;
tcublasDdot_v2_64 *cublasDdot_v2_64;
tcublasCdotu_v2 *cublasCdotu_v2;
tcublasCdotu_v2_64 *cublasCdotu_v2_64;
tcublasCdotc_v2 *cublasCdotc_v2;
tcublasCdotc_v2_64 *cublasCdotc_v2_64;
tcublasZdotu_v2 *cublasZdotu_v2;
tcublasZdotu_v2_64 *cublasZdotu_v2_64;
tcublasZdotc_v2 *cublasZdotc_v2;
tcublasZdotc_v2_64 *cublasZdotc_v2_64;
tcublasScalEx *cublasScalEx;
tcublasScalEx_64 *cublasScalEx_64;
tcublasSscal_v2 *cublasSscal_v2;
tcublasSscal_v2_64 *cublasSscal_v2_64;
tcublasDscal_v2 *cublasDscal_v2;
tcublasDscal_v2_64 *cublasDscal_v2_64;
tcublasCscal_v2 *cublasCscal_v2;
tcublasCscal_v2_64 *cublasCscal_v2_64;
tcublasCsscal_v2 *cublasCsscal_v2;
tcublasCsscal_v2_64 *cublasCsscal_v2_64;
tcublasZscal_v2 *cublasZscal_v2;
tcublasZscal_v2_64 *cublasZscal_v2_64;
tcublasZdscal_v2 *cublasZdscal_v2;
tcublasZdscal_v2_64 *cublasZdscal_v2_64;
tcublasAxpyEx *cublasAxpyEx;
tcublasAxpyEx_64 *cublasAxpyEx_64;
tcublasSaxpy_v2 *cublasSaxpy_v2;
tcublasSaxpy_v2_64 *cublasSaxpy_v2_64;
tcublasDaxpy_v2 *cublasDaxpy_v2;
tcublasDaxpy_v2_64 *cublasDaxpy_v2_64;
tcublasCaxpy_v2 *cublasCaxpy_v2;
tcublasCaxpy_v2_64 *cublasCaxpy_v2_64;
tcublasZaxpy_v2 *cublasZaxpy_v2;
tcublasZaxpy_v2_64 *cublasZaxpy_v2_64;
tcublasCopyEx *cublasCopyEx;
tcublasCopyEx_64 *cublasCopyEx_64;
tcublasScopy_v2 *cublasScopy_v2;
tcublasScopy_v2_64 *cublasScopy_v2_64;
tcublasDcopy_v2 *cublasDcopy_v2;
tcublasDcopy_v2_64 *cublasDcopy_v2_64;
tcublasCcopy_v2 *cublasCcopy_v2;
tcublasCcopy_v2_64 *cublasCcopy_v2_64;
tcublasZcopy_v2 *cublasZcopy_v2;
tcublasZcopy_v2_64 *cublasZcopy_v2_64;
tcublasSswap_v2 *cublasSswap_v2;
tcublasSswap_v2_64 *cublasSswap_v2_64;
tcublasDswap_v2 *cublasDswap_v2;
tcublasDswap_v2_64 *cublasDswap_v2_64;
tcublasCswap_v2 *cublasCswap_v2;
tcublasCswap_v2_64 *cublasCswap_v2_64;
tcublasZswap_v2 *cublasZswap_v2;
tcublasZswap_v2_64 *cublasZswap_v2_64;
tcublasSwapEx *cublasSwapEx;
tcublasSwapEx_64 *cublasSwapEx_64;
tcublasIsamax_v2 *cublasIsamax_v2;
tcublasIsamax_v2_64 *cublasIsamax_v2_64;
tcublasIdamax_v2 *cublasIdamax_v2;
tcublasIdamax_v2_64 *cublasIdamax_v2_64;
tcublasIcamax_v2 *cublasIcamax_v2;
tcublasIcamax_v2_64 *cublasIcamax_v2_64;
tcublasIzamax_v2 *cublasIzamax_v2;
tcublasIzamax_v2_64 *cublasIzamax_v2_64;
tcublasIamaxEx *cublasIamaxEx;
tcublasIamaxEx_64 *cublasIamaxEx_64;
tcublasIsamin_v2 *cublasIsamin_v2;
tcublasIsamin_v2_64 *cublasIsamin_v2_64;
tcublasIdamin_v2 *cublasIdamin_v2;
tcublasIdamin_v2_64 *cublasIdamin_v2_64;
tcublasIcamin_v2 *cublasIcamin_v2;
tcublasIcamin_v2_64 *cublasIcamin_v2_64;
tcublasIzamin_v2 *cublasIzamin_v2;
tcublasIzamin_v2_64 *cublasIzamin_v2_64;
tcublasIaminEx *cublasIaminEx;
tcublasIaminEx_64 *cublasIaminEx_64;
tcublasAsumEx *cublasAsumEx;
tcublasAsumEx_64 *cublasAsumEx_64;
tcublasSasum_v2 *cublasSasum_v2;
tcublasSasum_v2_64 *cublasSasum_v2_64;
tcublasDasum_v2 *cublasDasum_v2;
tcublasDasum_v2_64 *cublasDasum_v2_64;
tcublasScasum_v2 *cublasScasum_v2;
tcublasScasum_v2_64 *cublasScasum_v2_64;
tcublasDzasum_v2 *cublasDzasum_v2;
tcublasDzasum_v2_64 *cublasDzasum_v2_64;
tcublasSrot_v2 *cublasSrot_v2;
tcublasSrot_v2_64 *cublasSrot_v2_64;
tcublasDrot_v2 *cublasDrot_v2;
tcublasDrot_v2_64 *cublasDrot_v2_64;
tcublasCrot_v2 *cublasCrot_v2;
tcublasCrot_v2_64 *cublasCrot_v2_64;
tcublasCsrot_v2 *cublasCsrot_v2;
tcublasCsrot_v2_64 *cublasCsrot_v2_64;
tcublasZrot_v2 *cublasZrot_v2;
tcublasZrot_v2_64 *cublasZrot_v2_64;
tcublasZdrot_v2 *cublasZdrot_v2;
tcublasZdrot_v2_64 *cublasZdrot_v2_64;
tcublasRotEx *cublasRotEx;
tcublasRotEx_64 *cublasRotEx_64;
tcublasSrotg_v2 *cublasSrotg_v2;
tcublasDrotg_v2 *cublasDrotg_v2;
tcublasCrotg_v2 *cublasCrotg_v2;
tcublasZrotg_v2 *cublasZrotg_v2;
tcublasRotgEx *cublasRotgEx;
tcublasSrotm_v2 *cublasSrotm_v2;
tcublasSrotm_v2_64 *cublasSrotm_v2_64;
tcublasDrotm_v2 *cublasDrotm_v2;
tcublasDrotm_v2_64 *cublasDrotm_v2_64;
tcublasRotmEx *cublasRotmEx;
tcublasRotmEx_64 *cublasRotmEx_64;
tcublasSrotmg_v2 *cublasSrotmg_v2;
tcublasDrotmg_v2 *cublasDrotmg_v2;
tcublasRotmgEx *cublasRotmgEx;
tcublasSgemv_v2 *cublasSgemv_v2;
tcublasSgemv_v2_64 *cublasSgemv_v2_64;
tcublasDgemv_v2 *cublasDgemv_v2;
tcublasDgemv_v2_64 *cublasDgemv_v2_64;
tcublasCgemv_v2 *cublasCgemv_v2;
tcublasCgemv_v2_64 *cublasCgemv_v2_64;
tcublasZgemv_v2 *cublasZgemv_v2;
tcublasZgemv_v2_64 *cublasZgemv_v2_64;
tcublasSgbmv_v2 *cublasSgbmv_v2;
tcublasSgbmv_v2_64 *cublasSgbmv_v2_64;
tcublasDgbmv_v2 *cublasDgbmv_v2;
tcublasDgbmv_v2_64 *cublasDgbmv_v2_64;
tcublasCgbmv_v2 *cublasCgbmv_v2;
tcublasCgbmv_v2_64 *cublasCgbmv_v2_64;
tcublasZgbmv_v2 *cublasZgbmv_v2;
tcublasZgbmv_v2_64 *cublasZgbmv_v2_64;
tcublasStrmv_v2 *cublasStrmv_v2;
tcublasStrmv_v2_64 *cublasStrmv_v2_64;
tcublasDtrmv_v2 *cublasDtrmv_v2;
tcublasDtrmv_v2_64 *cublasDtrmv_v2_64;
tcublasCtrmv_v2 *cublasCtrmv_v2;
tcublasCtrmv_v2_64 *cublasCtrmv_v2_64;
tcublasZtrmv_v2 *cublasZtrmv_v2;
tcublasZtrmv_v2_64 *cublasZtrmv_v2_64;
tcublasStbmv_v2 *cublasStbmv_v2;
tcublasStbmv_v2_64 *cublasStbmv_v2_64;
tcublasDtbmv_v2 *cublasDtbmv_v2;
tcublasDtbmv_v2_64 *cublasDtbmv_v2_64;
tcublasCtbmv_v2 *cublasCtbmv_v2;
tcublasCtbmv_v2_64 *cublasCtbmv_v2_64;
tcublasZtbmv_v2 *cublasZtbmv_v2;
tcublasZtbmv_v2_64 *cublasZtbmv_v2_64;
tcublasStpmv_v2 *cublasStpmv_v2;
tcublasStpmv_v2_64 *cublasStpmv_v2_64;
tcublasDtpmv_v2 *cublasDtpmv_v2;
tcublasDtpmv_v2_64 *cublasDtpmv_v2_64;
tcublasCtpmv_v2 *cublasCtpmv_v2;
tcublasCtpmv_v2_64 *cublasCtpmv_v2_64;
tcublasZtpmv_v2 *cublasZtpmv_v2;
tcublasZtpmv_v2_64 *cublasZtpmv_v2_64;
tcublasStrsv_v2 *cublasStrsv_v2;
tcublasStrsv_v2_64 *cublasStrsv_v2_64;
tcublasDtrsv_v2 *cublasDtrsv_v2;
tcublasDtrsv_v2_64 *cublasDtrsv_v2_64;
tcublasCtrsv_v2 *cublasCtrsv_v2;
tcublasCtrsv_v2_64 *cublasCtrsv_v2_64;
tcublasZtrsv_v2 *cublasZtrsv_v2;
tcublasZtrsv_v2_64 *cublasZtrsv_v2_64;
tcublasStpsv_v2 *cublasStpsv_v2;
tcublasStpsv_v2_64 *cublasStpsv_v2_64;
tcublasDtpsv_v2 *cublasDtpsv_v2;
tcublasDtpsv_v2_64 *cublasDtpsv_v2_64;
tcublasCtpsv_v2 *cublasCtpsv_v2;
tcublasCtpsv_v2_64 *cublasCtpsv_v2_64;
tcublasZtpsv_v2 *cublasZtpsv_v2;
tcublasZtpsv_v2_64 *cublasZtpsv_v2_64;
tcublasStbsv_v2 *cublasStbsv_v2;
tcublasStbsv_v2_64 *cublasStbsv_v2_64;
tcublasDtbsv_v2 *cublasDtbsv_v2;
tcublasDtbsv_v2_64 *cublasDtbsv_v2_64;
tcublasCtbsv_v2 *cublasCtbsv_v2;
tcublasCtbsv_v2_64 *cublasCtbsv_v2_64;
tcublasZtbsv_v2 *cublasZtbsv_v2;
tcublasZtbsv_v2_64 *cublasZtbsv_v2_64;
tcublasSsymv_v2 *cublasSsymv_v2;
tcublasSsymv_v2_64 *cublasSsymv_v2_64;
tcublasDsymv_v2 *cublasDsymv_v2;
tcublasDsymv_v2_64 *cublasDsymv_v2_64;
tcublasCsymv_v2 *cublasCsymv_v2;
tcublasCsymv_v2_64 *cublasCsymv_v2_64;
tcublasZsymv_v2 *cublasZsymv_v2;
tcublasZsymv_v2_64 *cublasZsymv_v2_64;
tcublasChemv_v2 *cublasChemv_v2;
tcublasChemv_v2_64 *cublasChemv_v2_64;
tcublasZhemv_v2 *cublasZhemv_v2;
tcublasZhemv_v2_64 *cublasZhemv_v2_64;
tcublasSsbmv_v2 *cublasSsbmv_v2;
tcublasSsbmv_v2_64 *cublasSsbmv_v2_64;
tcublasDsbmv_v2 *cublasDsbmv_v2;
tcublasDsbmv_v2_64 *cublasDsbmv_v2_64;
tcublasChbmv_v2 *cublasChbmv_v2;
tcublasChbmv_v2_64 *cublasChbmv_v2_64;
tcublasZhbmv_v2 *cublasZhbmv_v2;
tcublasZhbmv_v2_64 *cublasZhbmv_v2_64;
tcublasSspmv_v2 *cublasSspmv_v2;
tcublasSspmv_v2_64 *cublasSspmv_v2_64;
tcublasDspmv_v2 *cublasDspmv_v2;
tcublasDspmv_v2_64 *cublasDspmv_v2_64;
tcublasChpmv_v2 *cublasChpmv_v2;
tcublasChpmv_v2_64 *cublasChpmv_v2_64;
tcublasZhpmv_v2 *cublasZhpmv_v2;
tcublasZhpmv_v2_64 *cublasZhpmv_v2_64;
tcublasSger_v2 *cublasSger_v2;
tcublasSger_v2_64 *cublasSger_v2_64;
tcublasDger_v2 *cublasDger_v2;
tcublasDger_v2_64 *cublasDger_v2_64;
tcublasCgeru_v2 *cublasCgeru_v2;
tcublasCgeru_v2_64 *cublasCgeru_v2_64;
tcublasCgerc_v2 *cublasCgerc_v2;
tcublasCgerc_v2_64 *cublasCgerc_v2_64;
tcublasZgeru_v2 *cublasZgeru_v2;
tcublasZgeru_v2_64 *cublasZgeru_v2_64;
tcublasZgerc_v2 *cublasZgerc_v2;
tcublasZgerc_v2_64 *cublasZgerc_v2_64;
tcublasSsyr_v2 *cublasSsyr_v2;
tcublasSsyr_v2_64 *cublasSsyr_v2_64;
tcublasDsyr_v2 *cublasDsyr_v2;
tcublasDsyr_v2_64 *cublasDsyr_v2_64;
tcublasCsyr_v2 *cublasCsyr_v2;
tcublasCsyr_v2_64 *cublasCsyr_v2_64;
tcublasZsyr_v2 *cublasZsyr_v2;
tcublasZsyr_v2_64 *cublasZsyr_v2_64;
tcublasCher_v2 *cublasCher_v2;
tcublasCher_v2_64 *cublasCher_v2_64;
tcublasZher_v2 *cublasZher_v2;
tcublasZher_v2_64 *cublasZher_v2_64;
tcublasSspr_v2 *cublasSspr_v2;
tcublasSspr_v2_64 *cublasSspr_v2_64;
tcublasDspr_v2 *cublasDspr_v2;
tcublasDspr_v2_64 *cublasDspr_v2_64;
tcublasChpr_v2 *cublasChpr_v2;
tcublasChpr_v2_64 *cublasChpr_v2_64;
tcublasZhpr_v2 *cublasZhpr_v2;
tcublasZhpr_v2_64 *cublasZhpr_v2_64;
tcublasSsyr2_v2 *cublasSsyr2_v2;
tcublasSsyr2_v2_64 *cublasSsyr2_v2_64;
tcublasDsyr2_v2 *cublasDsyr2_v2;
tcublasDsyr2_v2_64 *cublasDsyr2_v2_64;
tcublasCsyr2_v2 *cublasCsyr2_v2;
tcublasCsyr2_v2_64 *cublasCsyr2_v2_64;
tcublasZsyr2_v2 *cublasZsyr2_v2;
tcublasZsyr2_v2_64 *cublasZsyr2_v2_64;
tcublasCher2_v2 *cublasCher2_v2;
tcublasCher2_v2_64 *cublasCher2_v2_64;
tcublasZher2_v2 *cublasZher2_v2;
tcublasZher2_v2_64 *cublasZher2_v2_64;
tcublasSspr2_v2 *cublasSspr2_v2;
tcublasSspr2_v2_64 *cublasSspr2_v2_64;
tcublasDspr2_v2 *cublasDspr2_v2;
tcublasDspr2_v2_64 *cublasDspr2_v2_64;
tcublasChpr2_v2 *cublasChpr2_v2;
tcublasChpr2_v2_64 *cublasChpr2_v2_64;
tcublasZhpr2_v2 *cublasZhpr2_v2;
tcublasZhpr2_v2_64 *cublasZhpr2_v2_64;
tcublasSgemvBatched *cublasSgemvBatched;
tcublasSgemvBatched_64 *cublasSgemvBatched_64;
tcublasDgemvBatched *cublasDgemvBatched;
tcublasDgemvBatched_64 *cublasDgemvBatched_64;
tcublasCgemvBatched *cublasCgemvBatched;
tcublasCgemvBatched_64 *cublasCgemvBatched_64;
tcublasZgemvBatched *cublasZgemvBatched;
tcublasZgemvBatched_64 *cublasZgemvBatched_64;
tcublasSgemvStridedBatched *cublasSgemvStridedBatched;
tcublasSgemvStridedBatched_64 *cublasSgemvStridedBatched_64;
tcublasDgemvStridedBatched *cublasDgemvStridedBatched;
tcublasDgemvStridedBatched_64 *cublasDgemvStridedBatched_64;
tcublasCgemvStridedBatched *cublasCgemvStridedBatched;
tcublasCgemvStridedBatched_64 *cublasCgemvStridedBatched_64;
tcublasZgemvStridedBatched *cublasZgemvStridedBatched;
tcublasZgemvStridedBatched_64 *cublasZgemvStridedBatched_64;
tcublasSgemm_v2 *cublasSgemm_v2;
tcublasSgemm_v2_64 *cublasSgemm_v2_64;
tcublasDgemm_v2 *cublasDgemm_v2;
tcublasDgemm_v2_64 *cublasDgemm_v2_64;
tcublasCgemm_v2 *cublasCgemm_v2;
tcublasCgemm_v2_64 *cublasCgemm_v2_64;
tcublasCgemm3m *cublasCgemm3m;
tcublasCgemm3m_64 *cublasCgemm3m_64;
tcublasCgemm3mEx *cublasCgemm3mEx;
tcublasCgemm3mEx_64 *cublasCgemm3mEx_64;
tcublasZgemm_v2 *cublasZgemm_v2;
tcublasZgemm_v2_64 *cublasZgemm_v2_64;
tcublasZgemm3m *cublasZgemm3m;
tcublasZgemm3m_64 *cublasZgemm3m_64;
tcublasSgemmEx *cublasSgemmEx;
tcublasSgemmEx_64 *cublasSgemmEx_64;
tcublasGemmEx *cublasGemmEx;
tcublasGemmEx_64 *cublasGemmEx_64;
tcublasCgemmEx *cublasCgemmEx;
tcublasCgemmEx_64 *cublasCgemmEx_64;
tcublasSsyrk_v2 *cublasSsyrk_v2;
tcublasSsyrk_v2_64 *cublasSsyrk_v2_64;
tcublasDsyrk_v2 *cublasDsyrk_v2;
tcublasDsyrk_v2_64 *cublasDsyrk_v2_64;
tcublasCsyrk_v2 *cublasCsyrk_v2;
tcublasCsyrk_v2_64 *cublasCsyrk_v2_64;
tcublasZsyrk_v2 *cublasZsyrk_v2;
tcublasZsyrk_v2_64 *cublasZsyrk_v2_64;
tcublasCsyrkEx *cublasCsyrkEx;
tcublasCsyrkEx_64 *cublasCsyrkEx_64;
tcublasCsyrk3mEx *cublasCsyrk3mEx;
tcublasCsyrk3mEx_64 *cublasCsyrk3mEx_64;
tcublasCherk_v2 *cublasCherk_v2;
tcublasCherk_v2_64 *cublasCherk_v2_64;
tcublasZherk_v2 *cublasZherk_v2;
tcublasZherk_v2_64 *cublasZherk_v2_64;
tcublasCherkEx *cublasCherkEx;
tcublasCherkEx_64 *cublasCherkEx_64;
tcublasCherk3mEx *cublasCherk3mEx;
tcublasCherk3mEx_64 *cublasCherk3mEx_64;
tcublasSsyr2k_v2 *cublasSsyr2k_v2;
tcublasSsyr2k_v2_64 *cublasSsyr2k_v2_64;
tcublasDsyr2k_v2 *cublasDsyr2k_v2;
tcublasDsyr2k_v2_64 *cublasDsyr2k_v2_64;
tcublasCsyr2k_v2 *cublasCsyr2k_v2;
tcublasCsyr2k_v2_64 *cublasCsyr2k_v2_64;
tcublasZsyr2k_v2 *cublasZsyr2k_v2;
tcublasZsyr2k_v2_64 *cublasZsyr2k_v2_64;
tcublasCher2k_v2 *cublasCher2k_v2;
tcublasCher2k_v2_64 *cublasCher2k_v2_64;
tcublasZher2k_v2 *cublasZher2k_v2;
tcublasZher2k_v2_64 *cublasZher2k_v2_64;
tcublasSsyrkx *cublasSsyrkx;
tcublasSsyrkx_64 *cublasSsyrkx_64;
tcublasDsyrkx *cublasDsyrkx;
tcublasDsyrkx_64 *cublasDsyrkx_64;
tcublasCsyrkx *cublasCsyrkx;
tcublasCsyrkx_64 *cublasCsyrkx_64;
tcublasZsyrkx *cublasZsyrkx;
tcublasZsyrkx_64 *cublasZsyrkx_64;
tcublasCherkx *cublasCherkx;
tcublasCherkx_64 *cublasCherkx_64;
tcublasZherkx *cublasZherkx;
tcublasZherkx_64 *cublasZherkx_64;
tcublasSsymm_v2 *cublasSsymm_v2;
tcublasSsymm_v2_64 *cublasSsymm_v2_64;
tcublasDsymm_v2 *cublasDsymm_v2;
tcublasDsymm_v2_64 *cublasDsymm_v2_64;
tcublasCsymm_v2 *cublasCsymm_v2;
tcublasCsymm_v2_64 *cublasCsymm_v2_64;
tcublasZsymm_v2 *cublasZsymm_v2;
tcublasZsymm_v2_64 *cublasZsymm_v2_64;
tcublasChemm_v2 *cublasChemm_v2;
tcublasChemm_v2_64 *cublasChemm_v2_64;
tcublasZhemm_v2 *cublasZhemm_v2;
tcublasZhemm_v2_64 *cublasZhemm_v2_64;
tcublasStrsm_v2 *cublasStrsm_v2;
tcublasStrsm_v2_64 *cublasStrsm_v2_64;
tcublasDtrsm_v2 *cublasDtrsm_v2;
tcublasDtrsm_v2_64 *cublasDtrsm_v2_64;
tcublasCtrsm_v2 *cublasCtrsm_v2;
tcublasCtrsm_v2_64 *cublasCtrsm_v2_64;
tcublasZtrsm_v2 *cublasZtrsm_v2;
tcublasZtrsm_v2_64 *cublasZtrsm_v2_64;
tcublasStrmm_v2 *cublasStrmm_v2;
tcublasStrmm_v2_64 *cublasStrmm_v2_64;
tcublasDtrmm_v2 *cublasDtrmm_v2;
tcublasDtrmm_v2_64 *cublasDtrmm_v2_64;
tcublasCtrmm_v2 *cublasCtrmm_v2;
tcublasCtrmm_v2_64 *cublasCtrmm_v2_64;
tcublasZtrmm_v2 *cublasZtrmm_v2;
tcublasZtrmm_v2_64 *cublasZtrmm_v2_64;
tcublasSgemmBatched *cublasSgemmBatched;
tcublasSgemmBatched_64 *cublasSgemmBatched_64;
tcublasDgemmBatched *cublasDgemmBatched;
tcublasDgemmBatched_64 *cublasDgemmBatched_64;
tcublasCgemmBatched *cublasCgemmBatched;
tcublasCgemmBatched_64 *cublasCgemmBatched_64;
tcublasCgemm3mBatched *cublasCgemm3mBatched;
tcublasCgemm3mBatched_64 *cublasCgemm3mBatched_64;
tcublasZgemmBatched *cublasZgemmBatched;
tcublasZgemmBatched_64 *cublasZgemmBatched_64;
tcublasSgemmStridedBatched *cublasSgemmStridedBatched;
tcublasSgemmStridedBatched_64 *cublasSgemmStridedBatched_64;
tcublasDgemmStridedBatched *cublasDgemmStridedBatched;
tcublasDgemmStridedBatched_64 *cublasDgemmStridedBatched_64;
tcublasCgemmStridedBatched *cublasCgemmStridedBatched;
tcublasCgemmStridedBatched_64 *cublasCgemmStridedBatched_64;
tcublasCgemm3mStridedBatched *cublasCgemm3mStridedBatched;
tcublasCgemm3mStridedBatched_64 *cublasCgemm3mStridedBatched_64;
tcublasZgemmStridedBatched *cublasZgemmStridedBatched;
tcublasZgemmStridedBatched_64 *cublasZgemmStridedBatched_64;
tcublasGemmBatchedEx *cublasGemmBatchedEx;
tcublasGemmBatchedEx_64 *cublasGemmBatchedEx_64;
tcublasGemmStridedBatchedEx *cublasGemmStridedBatchedEx;
tcublasGemmStridedBatchedEx_64 *cublasGemmStridedBatchedEx_64;
tcublasSgeam *cublasSgeam;
tcublasSgeam_64 *cublasSgeam_64;
tcublasDgeam *cublasDgeam;
tcublasDgeam_64 *cublasDgeam_64;
tcublasCgeam *cublasCgeam;
tcublasCgeam_64 *cublasCgeam_64;
tcublasZgeam *cublasZgeam;
tcublasZgeam_64 *cublasZgeam_64;
tcublasStrsmBatched *cublasStrsmBatched;
tcublasStrsmBatched_64 *cublasStrsmBatched_64;
tcublasDtrsmBatched *cublasDtrsmBatched;
tcublasDtrsmBatched_64 *cublasDtrsmBatched_64;
tcublasCtrsmBatched *cublasCtrsmBatched;
tcublasCtrsmBatched_64 *cublasCtrsmBatched_64;
tcublasZtrsmBatched *cublasZtrsmBatched;
tcublasZtrsmBatched_64 *cublasZtrsmBatched_64;
tcublasSdgmm *cublasSdgmm;
tcublasSdgmm_64 *cublasSdgmm_64;
tcublasDdgmm *cublasDdgmm;
tcublasDdgmm_64 *cublasDdgmm_64;
tcublasCdgmm *cublasCdgmm;
tcublasCdgmm_64 *cublasCdgmm_64;
tcublasZdgmm *cublasZdgmm;
tcublasZdgmm_64 *cublasZdgmm_64;
tcublasSmatinvBatched *cublasSmatinvBatched;
tcublasDmatinvBatched *cublasDmatinvBatched;
tcublasCmatinvBatched *cublasCmatinvBatched;
tcublasZmatinvBatched *cublasZmatinvBatched;
tcublasSgeqrfBatched *cublasSgeqrfBatched;
tcublasDgeqrfBatched *cublasDgeqrfBatched;
tcublasCgeqrfBatched *cublasCgeqrfBatched;
tcublasZgeqrfBatched *cublasZgeqrfBatched;
tcublasSgelsBatched *cublasSgelsBatched;
tcublasDgelsBatched *cublasDgelsBatched;
tcublasCgelsBatched *cublasCgelsBatched;
tcublasZgelsBatched *cublasZgelsBatched;
tcublasStpttr *cublasStpttr;
tcublasDtpttr *cublasDtpttr;
tcublasCtpttr *cublasCtpttr;
tcublasZtpttr *cublasZtpttr;
tcublasStrttp *cublasStrttp;
tcublasDtrttp *cublasDtrttp;
tcublasCtrttp *cublasCtrttp;
tcublasZtrttp *cublasZtrttp;
tcublasSgetrfBatched *cublasSgetrfBatched;
tcublasDgetrfBatched *cublasDgetrfBatched;
tcublasCgetrfBatched *cublasCgetrfBatched;
tcublasZgetrfBatched *cublasZgetrfBatched;
tcublasSgetriBatched *cublasSgetriBatched;
tcublasDgetriBatched *cublasDgetriBatched;
tcublasCgetriBatched *cublasCgetriBatched;
tcublasZgetriBatched *cublasZgetriBatched;
tcublasSgetrsBatched *cublasSgetrsBatched;
tcublasDgetrsBatched *cublasDgetrsBatched;
tcublasCgetrsBatched *cublasCgetrsBatched;
tcublasZgetrsBatched *cublasZgetrsBatched;
tcublasUint8gemmBias *cublasUint8gemmBias;

int cuewInitCUBLAS(const char **extra_dll_search_paths) {

#ifdef _WIN32
  const char *paths[] = {   "cublas.dll",
NULL};
#else /* linux */
  const char *paths[] = {   "libcublas.so",
   "/usr/local/cuda/lib64/libcublas.so",
NULL};
#endif


  static int initialized = 0;
  static int result = 0;
  int error;

  if (initialized) {
    return result;
  }

  initialized = 1;
  error = atexit(cuewExitCUBLAS);

  if (error) {
    result = -2;
    return result;
  }
  cublas_lib = dynamic_library_open_find(paths);
  if (cublas_lib == NULL) { 
    if (extra_dll_search_paths) { 
      cublas_lib = dynamic_library_open_find(extra_dll_search_paths);
    }
  }
  if (cublas_lib == NULL) { result = -1; return result; }

  CUBLAS_LIBRARY_FIND(cublasCreate_v2)
  CUBLAS_LIBRARY_FIND(cublasDestroy_v2)
  CUBLAS_LIBRARY_FIND(cublasGetVersion_v2)
  CUBLAS_LIBRARY_FIND(cublasGetProperty)
  CUBLAS_LIBRARY_FIND(cublasGetCudartVersion)
  CUBLAS_LIBRARY_FIND(cublasSetWorkspace_v2)
  CUBLAS_LIBRARY_FIND(cublasSetStream_v2)
  CUBLAS_LIBRARY_FIND(cublasGetStream_v2)
  CUBLAS_LIBRARY_FIND(cublasGetPointerMode_v2)
  CUBLAS_LIBRARY_FIND(cublasSetPointerMode_v2)
  CUBLAS_LIBRARY_FIND(cublasGetAtomicsMode)
  CUBLAS_LIBRARY_FIND(cublasSetAtomicsMode)
  CUBLAS_LIBRARY_FIND(cublasGetMathMode)
  CUBLAS_LIBRARY_FIND(cublasSetMathMode)
  CUBLAS_LIBRARY_FIND(cublasGetSmCountTarget)
  CUBLAS_LIBRARY_FIND(cublasSetSmCountTarget)
  CUBLAS_LIBRARY_FIND(cublasGetStatusName)
  CUBLAS_LIBRARY_FIND(cublasGetStatusString)
  CUBLAS_LIBRARY_FIND(cublasLoggerConfigure)
  CUBLAS_LIBRARY_FIND(cublasSetLoggerCallback)
  CUBLAS_LIBRARY_FIND(cublasGetLoggerCallback)
  CUBLAS_LIBRARY_FIND(cublasSetVector)
  CUBLAS_LIBRARY_FIND(cublasSetVector_64)
  CUBLAS_LIBRARY_FIND(cublasGetVector)
  CUBLAS_LIBRARY_FIND(cublasGetVector_64)
  CUBLAS_LIBRARY_FIND(cublasSetMatrix)
  CUBLAS_LIBRARY_FIND(cublasSetMatrix_64)
  CUBLAS_LIBRARY_FIND(cublasGetMatrix)
  CUBLAS_LIBRARY_FIND(cublasGetMatrix_64)
  CUBLAS_LIBRARY_FIND(cublasSetVectorAsync)
  CUBLAS_LIBRARY_FIND(cublasSetVectorAsync_64)
  CUBLAS_LIBRARY_FIND(cublasGetVectorAsync)
  CUBLAS_LIBRARY_FIND(cublasGetVectorAsync_64)
  CUBLAS_LIBRARY_FIND(cublasSetMatrixAsync)
  CUBLAS_LIBRARY_FIND(cublasSetMatrixAsync_64)
  CUBLAS_LIBRARY_FIND(cublasGetMatrixAsync)
  CUBLAS_LIBRARY_FIND(cublasGetMatrixAsync_64)
  CUBLAS_LIBRARY_FIND(cublasXerbla)
  CUBLAS_LIBRARY_FIND(cublasNrm2Ex)
  CUBLAS_LIBRARY_FIND(cublasNrm2Ex_64)
  CUBLAS_LIBRARY_FIND(cublasSnrm2_v2)
  CUBLAS_LIBRARY_FIND(cublasSnrm2_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDnrm2_v2)
  CUBLAS_LIBRARY_FIND(cublasDnrm2_v2_64)
  CUBLAS_LIBRARY_FIND(cublasScnrm2_v2)
  CUBLAS_LIBRARY_FIND(cublasScnrm2_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDznrm2_v2)
  CUBLAS_LIBRARY_FIND(cublasDznrm2_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDotEx)
  CUBLAS_LIBRARY_FIND(cublasDotEx_64)
  CUBLAS_LIBRARY_FIND(cublasDotcEx)
  CUBLAS_LIBRARY_FIND(cublasDotcEx_64)
  CUBLAS_LIBRARY_FIND(cublasSdot_v2)
  CUBLAS_LIBRARY_FIND(cublasSdot_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDdot_v2)
  CUBLAS_LIBRARY_FIND(cublasDdot_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCdotu_v2)
  CUBLAS_LIBRARY_FIND(cublasCdotu_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCdotc_v2)
  CUBLAS_LIBRARY_FIND(cublasCdotc_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZdotu_v2)
  CUBLAS_LIBRARY_FIND(cublasZdotu_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZdotc_v2)
  CUBLAS_LIBRARY_FIND(cublasZdotc_v2_64)
  CUBLAS_LIBRARY_FIND(cublasScalEx)
  CUBLAS_LIBRARY_FIND(cublasScalEx_64)
  CUBLAS_LIBRARY_FIND(cublasSscal_v2)
  CUBLAS_LIBRARY_FIND(cublasSscal_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDscal_v2)
  CUBLAS_LIBRARY_FIND(cublasDscal_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCscal_v2)
  CUBLAS_LIBRARY_FIND(cublasCscal_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCsscal_v2)
  CUBLAS_LIBRARY_FIND(cublasCsscal_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZscal_v2)
  CUBLAS_LIBRARY_FIND(cublasZscal_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZdscal_v2)
  CUBLAS_LIBRARY_FIND(cublasZdscal_v2_64)
  CUBLAS_LIBRARY_FIND(cublasAxpyEx)
  CUBLAS_LIBRARY_FIND(cublasAxpyEx_64)
  CUBLAS_LIBRARY_FIND(cublasSaxpy_v2)
  CUBLAS_LIBRARY_FIND(cublasSaxpy_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDaxpy_v2)
  CUBLAS_LIBRARY_FIND(cublasDaxpy_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCaxpy_v2)
  CUBLAS_LIBRARY_FIND(cublasCaxpy_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZaxpy_v2)
  CUBLAS_LIBRARY_FIND(cublasZaxpy_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCopyEx)
  CUBLAS_LIBRARY_FIND(cublasCopyEx_64)
  CUBLAS_LIBRARY_FIND(cublasScopy_v2)
  CUBLAS_LIBRARY_FIND(cublasScopy_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDcopy_v2)
  CUBLAS_LIBRARY_FIND(cublasDcopy_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCcopy_v2)
  CUBLAS_LIBRARY_FIND(cublasCcopy_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZcopy_v2)
  CUBLAS_LIBRARY_FIND(cublasZcopy_v2_64)
  CUBLAS_LIBRARY_FIND(cublasSswap_v2)
  CUBLAS_LIBRARY_FIND(cublasSswap_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDswap_v2)
  CUBLAS_LIBRARY_FIND(cublasDswap_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCswap_v2)
  CUBLAS_LIBRARY_FIND(cublasCswap_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZswap_v2)
  CUBLAS_LIBRARY_FIND(cublasZswap_v2_64)
  CUBLAS_LIBRARY_FIND(cublasSwapEx)
  CUBLAS_LIBRARY_FIND(cublasSwapEx_64)
  CUBLAS_LIBRARY_FIND(cublasIsamax_v2)
  CUBLAS_LIBRARY_FIND(cublasIsamax_v2_64)
  CUBLAS_LIBRARY_FIND(cublasIdamax_v2)
  CUBLAS_LIBRARY_FIND(cublasIdamax_v2_64)
  CUBLAS_LIBRARY_FIND(cublasIcamax_v2)
  CUBLAS_LIBRARY_FIND(cublasIcamax_v2_64)
  CUBLAS_LIBRARY_FIND(cublasIzamax_v2)
  CUBLAS_LIBRARY_FIND(cublasIzamax_v2_64)
  CUBLAS_LIBRARY_FIND(cublasIamaxEx)
  CUBLAS_LIBRARY_FIND(cublasIamaxEx_64)
  CUBLAS_LIBRARY_FIND(cublasIsamin_v2)
  CUBLAS_LIBRARY_FIND(cublasIsamin_v2_64)
  CUBLAS_LIBRARY_FIND(cublasIdamin_v2)
  CUBLAS_LIBRARY_FIND(cublasIdamin_v2_64)
  CUBLAS_LIBRARY_FIND(cublasIcamin_v2)
  CUBLAS_LIBRARY_FIND(cublasIcamin_v2_64)
  CUBLAS_LIBRARY_FIND(cublasIzamin_v2)
  CUBLAS_LIBRARY_FIND(cublasIzamin_v2_64)
  CUBLAS_LIBRARY_FIND(cublasIaminEx)
  CUBLAS_LIBRARY_FIND(cublasIaminEx_64)
  CUBLAS_LIBRARY_FIND(cublasAsumEx)
  CUBLAS_LIBRARY_FIND(cublasAsumEx_64)
  CUBLAS_LIBRARY_FIND(cublasSasum_v2)
  CUBLAS_LIBRARY_FIND(cublasSasum_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDasum_v2)
  CUBLAS_LIBRARY_FIND(cublasDasum_v2_64)
  CUBLAS_LIBRARY_FIND(cublasScasum_v2)
  CUBLAS_LIBRARY_FIND(cublasScasum_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDzasum_v2)
  CUBLAS_LIBRARY_FIND(cublasDzasum_v2_64)
  CUBLAS_LIBRARY_FIND(cublasSrot_v2)
  CUBLAS_LIBRARY_FIND(cublasSrot_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDrot_v2)
  CUBLAS_LIBRARY_FIND(cublasDrot_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCrot_v2)
  CUBLAS_LIBRARY_FIND(cublasCrot_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCsrot_v2)
  CUBLAS_LIBRARY_FIND(cublasCsrot_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZrot_v2)
  CUBLAS_LIBRARY_FIND(cublasZrot_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZdrot_v2)
  CUBLAS_LIBRARY_FIND(cublasZdrot_v2_64)
  CUBLAS_LIBRARY_FIND(cublasRotEx)
  CUBLAS_LIBRARY_FIND(cublasRotEx_64)
  CUBLAS_LIBRARY_FIND(cublasSrotg_v2)
  CUBLAS_LIBRARY_FIND(cublasDrotg_v2)
  CUBLAS_LIBRARY_FIND(cublasCrotg_v2)
  CUBLAS_LIBRARY_FIND(cublasZrotg_v2)
  CUBLAS_LIBRARY_FIND(cublasRotgEx)
  CUBLAS_LIBRARY_FIND(cublasSrotm_v2)
  CUBLAS_LIBRARY_FIND(cublasSrotm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDrotm_v2)
  CUBLAS_LIBRARY_FIND(cublasDrotm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasRotmEx)
  CUBLAS_LIBRARY_FIND(cublasRotmEx_64)
  CUBLAS_LIBRARY_FIND(cublasSrotmg_v2)
  CUBLAS_LIBRARY_FIND(cublasDrotmg_v2)
  CUBLAS_LIBRARY_FIND(cublasRotmgEx)
  CUBLAS_LIBRARY_FIND(cublasSgemv_v2)
  CUBLAS_LIBRARY_FIND(cublasSgemv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDgemv_v2)
  CUBLAS_LIBRARY_FIND(cublasDgemv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCgemv_v2)
  CUBLAS_LIBRARY_FIND(cublasCgemv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZgemv_v2)
  CUBLAS_LIBRARY_FIND(cublasZgemv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasSgbmv_v2)
  CUBLAS_LIBRARY_FIND(cublasSgbmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDgbmv_v2)
  CUBLAS_LIBRARY_FIND(cublasDgbmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCgbmv_v2)
  CUBLAS_LIBRARY_FIND(cublasCgbmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZgbmv_v2)
  CUBLAS_LIBRARY_FIND(cublasZgbmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasStrmv_v2)
  CUBLAS_LIBRARY_FIND(cublasStrmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDtrmv_v2)
  CUBLAS_LIBRARY_FIND(cublasDtrmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCtrmv_v2)
  CUBLAS_LIBRARY_FIND(cublasCtrmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZtrmv_v2)
  CUBLAS_LIBRARY_FIND(cublasZtrmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasStbmv_v2)
  CUBLAS_LIBRARY_FIND(cublasStbmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDtbmv_v2)
  CUBLAS_LIBRARY_FIND(cublasDtbmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCtbmv_v2)
  CUBLAS_LIBRARY_FIND(cublasCtbmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZtbmv_v2)
  CUBLAS_LIBRARY_FIND(cublasZtbmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasStpmv_v2)
  CUBLAS_LIBRARY_FIND(cublasStpmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDtpmv_v2)
  CUBLAS_LIBRARY_FIND(cublasDtpmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCtpmv_v2)
  CUBLAS_LIBRARY_FIND(cublasCtpmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZtpmv_v2)
  CUBLAS_LIBRARY_FIND(cublasZtpmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasStrsv_v2)
  CUBLAS_LIBRARY_FIND(cublasStrsv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDtrsv_v2)
  CUBLAS_LIBRARY_FIND(cublasDtrsv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCtrsv_v2)
  CUBLAS_LIBRARY_FIND(cublasCtrsv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZtrsv_v2)
  CUBLAS_LIBRARY_FIND(cublasZtrsv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasStpsv_v2)
  CUBLAS_LIBRARY_FIND(cublasStpsv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDtpsv_v2)
  CUBLAS_LIBRARY_FIND(cublasDtpsv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCtpsv_v2)
  CUBLAS_LIBRARY_FIND(cublasCtpsv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZtpsv_v2)
  CUBLAS_LIBRARY_FIND(cublasZtpsv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasStbsv_v2)
  CUBLAS_LIBRARY_FIND(cublasStbsv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDtbsv_v2)
  CUBLAS_LIBRARY_FIND(cublasDtbsv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCtbsv_v2)
  CUBLAS_LIBRARY_FIND(cublasCtbsv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZtbsv_v2)
  CUBLAS_LIBRARY_FIND(cublasZtbsv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasSsymv_v2)
  CUBLAS_LIBRARY_FIND(cublasSsymv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDsymv_v2)
  CUBLAS_LIBRARY_FIND(cublasDsymv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCsymv_v2)
  CUBLAS_LIBRARY_FIND(cublasCsymv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZsymv_v2)
  CUBLAS_LIBRARY_FIND(cublasZsymv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasChemv_v2)
  CUBLAS_LIBRARY_FIND(cublasChemv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZhemv_v2)
  CUBLAS_LIBRARY_FIND(cublasZhemv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasSsbmv_v2)
  CUBLAS_LIBRARY_FIND(cublasSsbmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDsbmv_v2)
  CUBLAS_LIBRARY_FIND(cublasDsbmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasChbmv_v2)
  CUBLAS_LIBRARY_FIND(cublasChbmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZhbmv_v2)
  CUBLAS_LIBRARY_FIND(cublasZhbmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasSspmv_v2)
  CUBLAS_LIBRARY_FIND(cublasSspmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDspmv_v2)
  CUBLAS_LIBRARY_FIND(cublasDspmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasChpmv_v2)
  CUBLAS_LIBRARY_FIND(cublasChpmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZhpmv_v2)
  CUBLAS_LIBRARY_FIND(cublasZhpmv_v2_64)
  CUBLAS_LIBRARY_FIND(cublasSger_v2)
  CUBLAS_LIBRARY_FIND(cublasSger_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDger_v2)
  CUBLAS_LIBRARY_FIND(cublasDger_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCgeru_v2)
  CUBLAS_LIBRARY_FIND(cublasCgeru_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCgerc_v2)
  CUBLAS_LIBRARY_FIND(cublasCgerc_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZgeru_v2)
  CUBLAS_LIBRARY_FIND(cublasZgeru_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZgerc_v2)
  CUBLAS_LIBRARY_FIND(cublasZgerc_v2_64)
  CUBLAS_LIBRARY_FIND(cublasSsyr_v2)
  CUBLAS_LIBRARY_FIND(cublasSsyr_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDsyr_v2)
  CUBLAS_LIBRARY_FIND(cublasDsyr_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCsyr_v2)
  CUBLAS_LIBRARY_FIND(cublasCsyr_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZsyr_v2)
  CUBLAS_LIBRARY_FIND(cublasZsyr_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCher_v2)
  CUBLAS_LIBRARY_FIND(cublasCher_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZher_v2)
  CUBLAS_LIBRARY_FIND(cublasZher_v2_64)
  CUBLAS_LIBRARY_FIND(cublasSspr_v2)
  CUBLAS_LIBRARY_FIND(cublasSspr_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDspr_v2)
  CUBLAS_LIBRARY_FIND(cublasDspr_v2_64)
  CUBLAS_LIBRARY_FIND(cublasChpr_v2)
  CUBLAS_LIBRARY_FIND(cublasChpr_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZhpr_v2)
  CUBLAS_LIBRARY_FIND(cublasZhpr_v2_64)
  CUBLAS_LIBRARY_FIND(cublasSsyr2_v2)
  CUBLAS_LIBRARY_FIND(cublasSsyr2_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDsyr2_v2)
  CUBLAS_LIBRARY_FIND(cublasDsyr2_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCsyr2_v2)
  CUBLAS_LIBRARY_FIND(cublasCsyr2_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZsyr2_v2)
  CUBLAS_LIBRARY_FIND(cublasZsyr2_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCher2_v2)
  CUBLAS_LIBRARY_FIND(cublasCher2_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZher2_v2)
  CUBLAS_LIBRARY_FIND(cublasZher2_v2_64)
  CUBLAS_LIBRARY_FIND(cublasSspr2_v2)
  CUBLAS_LIBRARY_FIND(cublasSspr2_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDspr2_v2)
  CUBLAS_LIBRARY_FIND(cublasDspr2_v2_64)
  CUBLAS_LIBRARY_FIND(cublasChpr2_v2)
  CUBLAS_LIBRARY_FIND(cublasChpr2_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZhpr2_v2)
  CUBLAS_LIBRARY_FIND(cublasZhpr2_v2_64)
  CUBLAS_LIBRARY_FIND(cublasSgemvBatched)
  CUBLAS_LIBRARY_FIND(cublasSgemvBatched_64)
  CUBLAS_LIBRARY_FIND(cublasDgemvBatched)
  CUBLAS_LIBRARY_FIND(cublasDgemvBatched_64)
  CUBLAS_LIBRARY_FIND(cublasCgemvBatched)
  CUBLAS_LIBRARY_FIND(cublasCgemvBatched_64)
  CUBLAS_LIBRARY_FIND(cublasZgemvBatched)
  CUBLAS_LIBRARY_FIND(cublasZgemvBatched_64)
  CUBLAS_LIBRARY_FIND(cublasSgemvStridedBatched)
  CUBLAS_LIBRARY_FIND(cublasSgemvStridedBatched_64)
  CUBLAS_LIBRARY_FIND(cublasDgemvStridedBatched)
  CUBLAS_LIBRARY_FIND(cublasDgemvStridedBatched_64)
  CUBLAS_LIBRARY_FIND(cublasCgemvStridedBatched)
  CUBLAS_LIBRARY_FIND(cublasCgemvStridedBatched_64)
  CUBLAS_LIBRARY_FIND(cublasZgemvStridedBatched)
  CUBLAS_LIBRARY_FIND(cublasZgemvStridedBatched_64)
  CUBLAS_LIBRARY_FIND(cublasSgemm_v2)
  CUBLAS_LIBRARY_FIND(cublasSgemm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDgemm_v2)
  CUBLAS_LIBRARY_FIND(cublasDgemm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCgemm_v2)
  CUBLAS_LIBRARY_FIND(cublasCgemm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCgemm3m)
  CUBLAS_LIBRARY_FIND(cublasCgemm3m_64)
  CUBLAS_LIBRARY_FIND(cublasCgemm3mEx)
  CUBLAS_LIBRARY_FIND(cublasCgemm3mEx_64)
  CUBLAS_LIBRARY_FIND(cublasZgemm_v2)
  CUBLAS_LIBRARY_FIND(cublasZgemm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZgemm3m)
  CUBLAS_LIBRARY_FIND(cublasZgemm3m_64)
  CUBLAS_LIBRARY_FIND(cublasSgemmEx)
  CUBLAS_LIBRARY_FIND(cublasSgemmEx_64)
  CUBLAS_LIBRARY_FIND(cublasGemmEx)
  CUBLAS_LIBRARY_FIND(cublasGemmEx_64)
  CUBLAS_LIBRARY_FIND(cublasCgemmEx)
  CUBLAS_LIBRARY_FIND(cublasCgemmEx_64)
  CUBLAS_LIBRARY_FIND(cublasSsyrk_v2)
  CUBLAS_LIBRARY_FIND(cublasSsyrk_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDsyrk_v2)
  CUBLAS_LIBRARY_FIND(cublasDsyrk_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCsyrk_v2)
  CUBLAS_LIBRARY_FIND(cublasCsyrk_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZsyrk_v2)
  CUBLAS_LIBRARY_FIND(cublasZsyrk_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCsyrkEx)
  CUBLAS_LIBRARY_FIND(cublasCsyrkEx_64)
  CUBLAS_LIBRARY_FIND(cublasCsyrk3mEx)
  CUBLAS_LIBRARY_FIND(cublasCsyrk3mEx_64)
  CUBLAS_LIBRARY_FIND(cublasCherk_v2)
  CUBLAS_LIBRARY_FIND(cublasCherk_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZherk_v2)
  CUBLAS_LIBRARY_FIND(cublasZherk_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCherkEx)
  CUBLAS_LIBRARY_FIND(cublasCherkEx_64)
  CUBLAS_LIBRARY_FIND(cublasCherk3mEx)
  CUBLAS_LIBRARY_FIND(cublasCherk3mEx_64)
  CUBLAS_LIBRARY_FIND(cublasSsyr2k_v2)
  CUBLAS_LIBRARY_FIND(cublasSsyr2k_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDsyr2k_v2)
  CUBLAS_LIBRARY_FIND(cublasDsyr2k_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCsyr2k_v2)
  CUBLAS_LIBRARY_FIND(cublasCsyr2k_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZsyr2k_v2)
  CUBLAS_LIBRARY_FIND(cublasZsyr2k_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCher2k_v2)
  CUBLAS_LIBRARY_FIND(cublasCher2k_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZher2k_v2)
  CUBLAS_LIBRARY_FIND(cublasZher2k_v2_64)
  CUBLAS_LIBRARY_FIND(cublasSsyrkx)
  CUBLAS_LIBRARY_FIND(cublasSsyrkx_64)
  CUBLAS_LIBRARY_FIND(cublasDsyrkx)
  CUBLAS_LIBRARY_FIND(cublasDsyrkx_64)
  CUBLAS_LIBRARY_FIND(cublasCsyrkx)
  CUBLAS_LIBRARY_FIND(cublasCsyrkx_64)
  CUBLAS_LIBRARY_FIND(cublasZsyrkx)
  CUBLAS_LIBRARY_FIND(cublasZsyrkx_64)
  CUBLAS_LIBRARY_FIND(cublasCherkx)
  CUBLAS_LIBRARY_FIND(cublasCherkx_64)
  CUBLAS_LIBRARY_FIND(cublasZherkx)
  CUBLAS_LIBRARY_FIND(cublasZherkx_64)
  CUBLAS_LIBRARY_FIND(cublasSsymm_v2)
  CUBLAS_LIBRARY_FIND(cublasSsymm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDsymm_v2)
  CUBLAS_LIBRARY_FIND(cublasDsymm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCsymm_v2)
  CUBLAS_LIBRARY_FIND(cublasCsymm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZsymm_v2)
  CUBLAS_LIBRARY_FIND(cublasZsymm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasChemm_v2)
  CUBLAS_LIBRARY_FIND(cublasChemm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZhemm_v2)
  CUBLAS_LIBRARY_FIND(cublasZhemm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasStrsm_v2)
  CUBLAS_LIBRARY_FIND(cublasStrsm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDtrsm_v2)
  CUBLAS_LIBRARY_FIND(cublasDtrsm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCtrsm_v2)
  CUBLAS_LIBRARY_FIND(cublasCtrsm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZtrsm_v2)
  CUBLAS_LIBRARY_FIND(cublasZtrsm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasStrmm_v2)
  CUBLAS_LIBRARY_FIND(cublasStrmm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasDtrmm_v2)
  CUBLAS_LIBRARY_FIND(cublasDtrmm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasCtrmm_v2)
  CUBLAS_LIBRARY_FIND(cublasCtrmm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasZtrmm_v2)
  CUBLAS_LIBRARY_FIND(cublasZtrmm_v2_64)
  CUBLAS_LIBRARY_FIND(cublasSgemmBatched)
  CUBLAS_LIBRARY_FIND(cublasSgemmBatched_64)
  CUBLAS_LIBRARY_FIND(cublasDgemmBatched)
  CUBLAS_LIBRARY_FIND(cublasDgemmBatched_64)
  CUBLAS_LIBRARY_FIND(cublasCgemmBatched)
  CUBLAS_LIBRARY_FIND(cublasCgemmBatched_64)
  CUBLAS_LIBRARY_FIND(cublasCgemm3mBatched)
  CUBLAS_LIBRARY_FIND(cublasCgemm3mBatched_64)
  CUBLAS_LIBRARY_FIND(cublasZgemmBatched)
  CUBLAS_LIBRARY_FIND(cublasZgemmBatched_64)
  CUBLAS_LIBRARY_FIND(cublasSgemmStridedBatched)
  CUBLAS_LIBRARY_FIND(cublasSgemmStridedBatched_64)
  CUBLAS_LIBRARY_FIND(cublasDgemmStridedBatched)
  CUBLAS_LIBRARY_FIND(cublasDgemmStridedBatched_64)
  CUBLAS_LIBRARY_FIND(cublasCgemmStridedBatched)
  CUBLAS_LIBRARY_FIND(cublasCgemmStridedBatched_64)
  CUBLAS_LIBRARY_FIND(cublasCgemm3mStridedBatched)
  CUBLAS_LIBRARY_FIND(cublasCgemm3mStridedBatched_64)
  CUBLAS_LIBRARY_FIND(cublasZgemmStridedBatched)
  CUBLAS_LIBRARY_FIND(cublasZgemmStridedBatched_64)
  CUBLAS_LIBRARY_FIND(cublasGemmBatchedEx)
  CUBLAS_LIBRARY_FIND(cublasGemmBatchedEx_64)
  CUBLAS_LIBRARY_FIND(cublasGemmStridedBatchedEx)
  CUBLAS_LIBRARY_FIND(cublasGemmStridedBatchedEx_64)
  CUBLAS_LIBRARY_FIND(cublasSgeam)
  CUBLAS_LIBRARY_FIND(cublasSgeam_64)
  CUBLAS_LIBRARY_FIND(cublasDgeam)
  CUBLAS_LIBRARY_FIND(cublasDgeam_64)
  CUBLAS_LIBRARY_FIND(cublasCgeam)
  CUBLAS_LIBRARY_FIND(cublasCgeam_64)
  CUBLAS_LIBRARY_FIND(cublasZgeam)
  CUBLAS_LIBRARY_FIND(cublasZgeam_64)
  CUBLAS_LIBRARY_FIND(cublasStrsmBatched)
  CUBLAS_LIBRARY_FIND(cublasStrsmBatched_64)
  CUBLAS_LIBRARY_FIND(cublasDtrsmBatched)
  CUBLAS_LIBRARY_FIND(cublasDtrsmBatched_64)
  CUBLAS_LIBRARY_FIND(cublasCtrsmBatched)
  CUBLAS_LIBRARY_FIND(cublasCtrsmBatched_64)
  CUBLAS_LIBRARY_FIND(cublasZtrsmBatched)
  CUBLAS_LIBRARY_FIND(cublasZtrsmBatched_64)
  CUBLAS_LIBRARY_FIND(cublasSdgmm)
  CUBLAS_LIBRARY_FIND(cublasSdgmm_64)
  CUBLAS_LIBRARY_FIND(cublasDdgmm)
  CUBLAS_LIBRARY_FIND(cublasDdgmm_64)
  CUBLAS_LIBRARY_FIND(cublasCdgmm)
  CUBLAS_LIBRARY_FIND(cublasCdgmm_64)
  CUBLAS_LIBRARY_FIND(cublasZdgmm)
  CUBLAS_LIBRARY_FIND(cublasZdgmm_64)
  CUBLAS_LIBRARY_FIND(cublasSmatinvBatched)
  CUBLAS_LIBRARY_FIND(cublasDmatinvBatched)
  CUBLAS_LIBRARY_FIND(cublasCmatinvBatched)
  CUBLAS_LIBRARY_FIND(cublasZmatinvBatched)
  CUBLAS_LIBRARY_FIND(cublasSgeqrfBatched)
  CUBLAS_LIBRARY_FIND(cublasDgeqrfBatched)
  CUBLAS_LIBRARY_FIND(cublasCgeqrfBatched)
  CUBLAS_LIBRARY_FIND(cublasZgeqrfBatched)
  CUBLAS_LIBRARY_FIND(cublasSgelsBatched)
  CUBLAS_LIBRARY_FIND(cublasDgelsBatched)
  CUBLAS_LIBRARY_FIND(cublasCgelsBatched)
  CUBLAS_LIBRARY_FIND(cublasZgelsBatched)
  CUBLAS_LIBRARY_FIND(cublasStpttr)
  CUBLAS_LIBRARY_FIND(cublasDtpttr)
  CUBLAS_LIBRARY_FIND(cublasCtpttr)
  CUBLAS_LIBRARY_FIND(cublasZtpttr)
  CUBLAS_LIBRARY_FIND(cublasStrttp)
  CUBLAS_LIBRARY_FIND(cublasDtrttp)
  CUBLAS_LIBRARY_FIND(cublasCtrttp)
  CUBLAS_LIBRARY_FIND(cublasZtrttp)
  CUBLAS_LIBRARY_FIND(cublasSgetrfBatched)
  CUBLAS_LIBRARY_FIND(cublasDgetrfBatched)
  CUBLAS_LIBRARY_FIND(cublasCgetrfBatched)
  CUBLAS_LIBRARY_FIND(cublasZgetrfBatched)
  CUBLAS_LIBRARY_FIND(cublasSgetriBatched)
  CUBLAS_LIBRARY_FIND(cublasDgetriBatched)
  CUBLAS_LIBRARY_FIND(cublasCgetriBatched)
  CUBLAS_LIBRARY_FIND(cublasZgetriBatched)
  CUBLAS_LIBRARY_FIND(cublasSgetrsBatched)
  CUBLAS_LIBRARY_FIND(cublasDgetrsBatched)
  CUBLAS_LIBRARY_FIND(cublasCgetrsBatched)
  CUBLAS_LIBRARY_FIND(cublasZgetrsBatched)
  CUBLAS_LIBRARY_FIND(cublasUint8gemmBias)
  result = 0; // success
  return result;
}
