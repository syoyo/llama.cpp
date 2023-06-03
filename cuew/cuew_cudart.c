

#ifdef _MSC_VER
#  if _MSC_VER < 1900
#    define snprintf _snprintf
#  endif
#  define popen _popen
#  define pclose _pclose
#  define _CRT_SECURE_NO_WARNINGS
#endif
#include "cuew.h"
#include "cuew_cudart.h"
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

/*#define CUDART_LIBRARY_FIND_CHECKED(name) CUEW_IMPL_LIBRARY_FIND_CHECKED(cudart_lib, name)*/
#define CUDART_LIBRARY_FIND(name) CUEW_IMPL_LIBRARY_FIND(cudart_lib, name)
static DynamicLibrary cudart_lib;

static void cuewExitCUDART(void) {
  if (cudart_lib != NULL) {
    /* ignore errors */
    dynamic_library_close(cudart_lib);
    cudart_lib = NULL;
  }
}

tcudaDeviceReset *cudaDeviceReset;
tcudaDeviceSynchronize *cudaDeviceSynchronize;
tcudaDeviceSetLimit *cudaDeviceSetLimit;
tcudaDeviceGetLimit *cudaDeviceGetLimit;
tcudaDeviceGetTexture1DLinearMaxWidth *cudaDeviceGetTexture1DLinearMaxWidth;
tcudaDeviceGetCacheConfig *cudaDeviceGetCacheConfig;
tcudaDeviceGetStreamPriorityRange *cudaDeviceGetStreamPriorityRange;
tcudaDeviceSetCacheConfig *cudaDeviceSetCacheConfig;
tcudaDeviceGetSharedMemConfig *cudaDeviceGetSharedMemConfig;
tcudaDeviceSetSharedMemConfig *cudaDeviceSetSharedMemConfig;
tcudaDeviceGetByPCIBusId *cudaDeviceGetByPCIBusId;
tcudaDeviceGetPCIBusId *cudaDeviceGetPCIBusId;
tcudaIpcGetEventHandle *cudaIpcGetEventHandle;
tcudaIpcOpenEventHandle *cudaIpcOpenEventHandle;
tcudaIpcGetMemHandle *cudaIpcGetMemHandle;
tcudaIpcOpenMemHandle *cudaIpcOpenMemHandle;
tcudaIpcCloseMemHandle *cudaIpcCloseMemHandle;
tcudaDeviceFlushGPUDirectRDMAWrites *cudaDeviceFlushGPUDirectRDMAWrites;
tcudaThreadExit *cudaThreadExit;
tcudaThreadSynchronize *cudaThreadSynchronize;
tcudaThreadSetLimit *cudaThreadSetLimit;
tcudaThreadGetLimit *cudaThreadGetLimit;
tcudaThreadGetCacheConfig *cudaThreadGetCacheConfig;
tcudaThreadSetCacheConfig *cudaThreadSetCacheConfig;
tcudaGetLastError *cudaGetLastError;
tcudaPeekAtLastError *cudaPeekAtLastError;
tcudaGetErrorName *cudaGetErrorName;
tcudaGetErrorString *cudaGetErrorString;
tcudaGetDeviceCount *cudaGetDeviceCount;
tcudaGetDeviceProperties_v2 *cudaGetDeviceProperties_v2;
tcudaDeviceGetAttribute *cudaDeviceGetAttribute;
tcudaDeviceGetDefaultMemPool *cudaDeviceGetDefaultMemPool;
tcudaDeviceSetMemPool *cudaDeviceSetMemPool;
tcudaDeviceGetMemPool *cudaDeviceGetMemPool;
tcudaDeviceGetNvSciSyncAttributes *cudaDeviceGetNvSciSyncAttributes;
tcudaDeviceGetP2PAttribute *cudaDeviceGetP2PAttribute;
tcudaChooseDevice *cudaChooseDevice;
tcudaInitDevice *cudaInitDevice;
tcudaSetDevice *cudaSetDevice;
tcudaGetDevice *cudaGetDevice;
tcudaSetValidDevices *cudaSetValidDevices;
tcudaSetDeviceFlags *cudaSetDeviceFlags;
tcudaGetDeviceFlags *cudaGetDeviceFlags;
tcudaStreamCreate *cudaStreamCreate;
tcudaStreamCreateWithFlags *cudaStreamCreateWithFlags;
tcudaStreamCreateWithPriority *cudaStreamCreateWithPriority;
tcudaStreamGetPriority *cudaStreamGetPriority;
tcudaStreamGetFlags *cudaStreamGetFlags;
tcudaStreamGetId *cudaStreamGetId;
tcudaCtxResetPersistingL2Cache *cudaCtxResetPersistingL2Cache;
tcudaStreamCopyAttributes *cudaStreamCopyAttributes;
tcudaStreamGetAttribute *cudaStreamGetAttribute;
tcudaStreamSetAttribute *cudaStreamSetAttribute;
tcudaStreamDestroy *cudaStreamDestroy;
tcudaStreamWaitEvent *cudaStreamWaitEvent;
tcudaStreamAddCallback *cudaStreamAddCallback;
tcudaStreamSynchronize *cudaStreamSynchronize;
tcudaStreamQuery *cudaStreamQuery;
tcudaStreamAttachMemAsync *cudaStreamAttachMemAsync;
tcudaStreamBeginCapture *cudaStreamBeginCapture;
tcudaThreadExchangeStreamCaptureMode *cudaThreadExchangeStreamCaptureMode;
tcudaStreamEndCapture *cudaStreamEndCapture;
tcudaStreamIsCapturing *cudaStreamIsCapturing;
tcudaStreamGetCaptureInfo_v2 *cudaStreamGetCaptureInfo_v2;
tcudaStreamUpdateCaptureDependencies *cudaStreamUpdateCaptureDependencies;
tcudaEventCreate *cudaEventCreate;
tcudaEventCreateWithFlags *cudaEventCreateWithFlags;
tcudaEventRecord *cudaEventRecord;
tcudaEventRecordWithFlags *cudaEventRecordWithFlags;
tcudaEventQuery *cudaEventQuery;
tcudaEventSynchronize *cudaEventSynchronize;
tcudaEventDestroy *cudaEventDestroy;
tcudaEventElapsedTime *cudaEventElapsedTime;
tcudaImportExternalMemory *cudaImportExternalMemory;
tcudaExternalMemoryGetMappedBuffer *cudaExternalMemoryGetMappedBuffer;
tcudaExternalMemoryGetMappedMipmappedArray *cudaExternalMemoryGetMappedMipmappedArray;
tcudaDestroyExternalMemory *cudaDestroyExternalMemory;
tcudaImportExternalSemaphore *cudaImportExternalSemaphore;
tcudaSignalExternalSemaphoresAsync_v2 *cudaSignalExternalSemaphoresAsync_v2;
tcudaWaitExternalSemaphoresAsync_v2 *cudaWaitExternalSemaphoresAsync_v2;
tcudaDestroyExternalSemaphore *cudaDestroyExternalSemaphore;
tcudaLaunchKernel *cudaLaunchKernel;
tcudaLaunchKernelExC *cudaLaunchKernelExC;
tcudaLaunchCooperativeKernel *cudaLaunchCooperativeKernel;
tcudaLaunchCooperativeKernelMultiDevice *cudaLaunchCooperativeKernelMultiDevice;
tcudaFuncSetCacheConfig *cudaFuncSetCacheConfig;
tcudaFuncSetSharedMemConfig *cudaFuncSetSharedMemConfig;
tcudaFuncGetAttributes *cudaFuncGetAttributes;
tcudaFuncSetAttribute *cudaFuncSetAttribute;
tcudaSetDoubleForDevice *cudaSetDoubleForDevice;
tcudaSetDoubleForHost *cudaSetDoubleForHost;
tcudaLaunchHostFunc *cudaLaunchHostFunc;
tcudaOccupancyMaxActiveBlocksPerMultiprocessor *cudaOccupancyMaxActiveBlocksPerMultiprocessor;
tcudaOccupancyAvailableDynamicSMemPerBlock *cudaOccupancyAvailableDynamicSMemPerBlock;
tcudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags *cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags;
tcudaOccupancyMaxPotentialClusterSize *cudaOccupancyMaxPotentialClusterSize;
tcudaOccupancyMaxActiveClusters *cudaOccupancyMaxActiveClusters;
tcudaMallocManaged *cudaMallocManaged;
tcudaMalloc *cudaMalloc;
tcudaMallocHost *cudaMallocHost;
tcudaMallocPitch *cudaMallocPitch;
tcudaMallocArray *cudaMallocArray;
tcudaFree *cudaFree;
tcudaFreeHost *cudaFreeHost;
tcudaFreeArray *cudaFreeArray;
tcudaFreeMipmappedArray *cudaFreeMipmappedArray;
tcudaHostAlloc *cudaHostAlloc;
tcudaHostRegister *cudaHostRegister;
tcudaHostUnregister *cudaHostUnregister;
tcudaHostGetDevicePointer *cudaHostGetDevicePointer;
tcudaHostGetFlags *cudaHostGetFlags;
tcudaMalloc3D *cudaMalloc3D;
tcudaMalloc3DArray *cudaMalloc3DArray;
tcudaMallocMipmappedArray *cudaMallocMipmappedArray;
tcudaGetMipmappedArrayLevel *cudaGetMipmappedArrayLevel;
tcudaMemcpy3D *cudaMemcpy3D;
tcudaMemcpy3DPeer *cudaMemcpy3DPeer;
tcudaMemcpy3DAsync *cudaMemcpy3DAsync;
tcudaMemcpy3DPeerAsync *cudaMemcpy3DPeerAsync;
tcudaMemGetInfo *cudaMemGetInfo;
tcudaArrayGetInfo *cudaArrayGetInfo;
tcudaArrayGetPlane *cudaArrayGetPlane;
tcudaArrayGetMemoryRequirements *cudaArrayGetMemoryRequirements;
tcudaMipmappedArrayGetMemoryRequirements *cudaMipmappedArrayGetMemoryRequirements;
tcudaArrayGetSparseProperties *cudaArrayGetSparseProperties;
tcudaMipmappedArrayGetSparseProperties *cudaMipmappedArrayGetSparseProperties;
tcudaMemcpy *cudaMemcpy;
tcudaMemcpyPeer *cudaMemcpyPeer;
tcudaMemcpy2D *cudaMemcpy2D;
tcudaMemcpy2DToArray *cudaMemcpy2DToArray;
tcudaMemcpy2DFromArray *cudaMemcpy2DFromArray;
tcudaMemcpy2DArrayToArray *cudaMemcpy2DArrayToArray;
tcudaMemcpyToSymbol *cudaMemcpyToSymbol;
tcudaMemcpyFromSymbol *cudaMemcpyFromSymbol;
tcudaMemcpyAsync *cudaMemcpyAsync;
tcudaMemcpyPeerAsync *cudaMemcpyPeerAsync;
tcudaMemcpy2DAsync *cudaMemcpy2DAsync;
tcudaMemcpy2DToArrayAsync *cudaMemcpy2DToArrayAsync;
tcudaMemcpy2DFromArrayAsync *cudaMemcpy2DFromArrayAsync;
tcudaMemcpyToSymbolAsync *cudaMemcpyToSymbolAsync;
tcudaMemcpyFromSymbolAsync *cudaMemcpyFromSymbolAsync;
tcudaMemset *cudaMemset;
tcudaMemset2D *cudaMemset2D;
tcudaMemset3D *cudaMemset3D;
tcudaMemsetAsync *cudaMemsetAsync;
tcudaMemset2DAsync *cudaMemset2DAsync;
tcudaMemset3DAsync *cudaMemset3DAsync;
tcudaGetSymbolAddress *cudaGetSymbolAddress;
tcudaGetSymbolSize *cudaGetSymbolSize;
tcudaMemPrefetchAsync *cudaMemPrefetchAsync;
tcudaMemAdvise *cudaMemAdvise;
tcudaMemRangeGetAttribute *cudaMemRangeGetAttribute;
tcudaMemRangeGetAttributes *cudaMemRangeGetAttributes;
tcudaMemcpyToArray *cudaMemcpyToArray;
tcudaMemcpyFromArray *cudaMemcpyFromArray;
tcudaMemcpyArrayToArray *cudaMemcpyArrayToArray;
tcudaMemcpyToArrayAsync *cudaMemcpyToArrayAsync;
tcudaMemcpyFromArrayAsync *cudaMemcpyFromArrayAsync;
tcudaMallocAsync *cudaMallocAsync;
tcudaFreeAsync *cudaFreeAsync;
tcudaMemPoolTrimTo *cudaMemPoolTrimTo;
tcudaMemPoolSetAttribute *cudaMemPoolSetAttribute;
tcudaMemPoolGetAttribute *cudaMemPoolGetAttribute;
tcudaMemPoolSetAccess *cudaMemPoolSetAccess;
tcudaMemPoolGetAccess *cudaMemPoolGetAccess;
tcudaMemPoolCreate *cudaMemPoolCreate;
tcudaMemPoolDestroy *cudaMemPoolDestroy;
tcudaMallocFromPoolAsync *cudaMallocFromPoolAsync;
tcudaMemPoolExportToShareableHandle *cudaMemPoolExportToShareableHandle;
tcudaMemPoolImportFromShareableHandle *cudaMemPoolImportFromShareableHandle;
tcudaMemPoolExportPointer *cudaMemPoolExportPointer;
tcudaMemPoolImportPointer *cudaMemPoolImportPointer;
tcudaPointerGetAttributes *cudaPointerGetAttributes;
tcudaDeviceCanAccessPeer *cudaDeviceCanAccessPeer;
tcudaDeviceEnablePeerAccess *cudaDeviceEnablePeerAccess;
tcudaDeviceDisablePeerAccess *cudaDeviceDisablePeerAccess;
tcudaGraphicsUnregisterResource *cudaGraphicsUnregisterResource;
tcudaGraphicsResourceSetMapFlags *cudaGraphicsResourceSetMapFlags;
tcudaGraphicsMapResources *cudaGraphicsMapResources;
tcudaGraphicsUnmapResources *cudaGraphicsUnmapResources;
tcudaGraphicsResourceGetMappedPointer *cudaGraphicsResourceGetMappedPointer;
tcudaGraphicsSubResourceGetMappedArray *cudaGraphicsSubResourceGetMappedArray;
tcudaGraphicsResourceGetMappedMipmappedArray *cudaGraphicsResourceGetMappedMipmappedArray;
tcudaGetChannelDesc *cudaGetChannelDesc;
tcudaCreateChannelDesc *cudaCreateChannelDesc;
tcudaCreateTextureObject *cudaCreateTextureObject;
tcudaDestroyTextureObject *cudaDestroyTextureObject;
tcudaGetTextureObjectResourceDesc *cudaGetTextureObjectResourceDesc;
tcudaGetTextureObjectTextureDesc *cudaGetTextureObjectTextureDesc;
tcudaGetTextureObjectResourceViewDesc *cudaGetTextureObjectResourceViewDesc;
tcudaCreateSurfaceObject *cudaCreateSurfaceObject;
tcudaDestroySurfaceObject *cudaDestroySurfaceObject;
tcudaGetSurfaceObjectResourceDesc *cudaGetSurfaceObjectResourceDesc;
tcudaDriverGetVersion *cudaDriverGetVersion;
tcudaRuntimeGetVersion *cudaRuntimeGetVersion;
tcudaGraphCreate *cudaGraphCreate;
tcudaGraphAddKernelNode *cudaGraphAddKernelNode;
tcudaGraphKernelNodeGetParams *cudaGraphKernelNodeGetParams;
tcudaGraphKernelNodeSetParams *cudaGraphKernelNodeSetParams;
tcudaGraphKernelNodeCopyAttributes *cudaGraphKernelNodeCopyAttributes;
tcudaGraphKernelNodeGetAttribute *cudaGraphKernelNodeGetAttribute;
tcudaGraphKernelNodeSetAttribute *cudaGraphKernelNodeSetAttribute;
tcudaGraphAddMemcpyNode *cudaGraphAddMemcpyNode;
tcudaGraphAddMemcpyNodeToSymbol *cudaGraphAddMemcpyNodeToSymbol;
tcudaGraphAddMemcpyNodeFromSymbol *cudaGraphAddMemcpyNodeFromSymbol;
tcudaGraphAddMemcpyNode1D *cudaGraphAddMemcpyNode1D;
tcudaGraphMemcpyNodeGetParams *cudaGraphMemcpyNodeGetParams;
tcudaGraphMemcpyNodeSetParams *cudaGraphMemcpyNodeSetParams;
tcudaGraphMemcpyNodeSetParamsToSymbol *cudaGraphMemcpyNodeSetParamsToSymbol;
tcudaGraphMemcpyNodeSetParamsFromSymbol *cudaGraphMemcpyNodeSetParamsFromSymbol;
tcudaGraphMemcpyNodeSetParams1D *cudaGraphMemcpyNodeSetParams1D;
tcudaGraphAddMemsetNode *cudaGraphAddMemsetNode;
tcudaGraphMemsetNodeGetParams *cudaGraphMemsetNodeGetParams;
tcudaGraphMemsetNodeSetParams *cudaGraphMemsetNodeSetParams;
tcudaGraphAddHostNode *cudaGraphAddHostNode;
tcudaGraphHostNodeGetParams *cudaGraphHostNodeGetParams;
tcudaGraphHostNodeSetParams *cudaGraphHostNodeSetParams;
tcudaGraphAddChildGraphNode *cudaGraphAddChildGraphNode;
tcudaGraphChildGraphNodeGetGraph *cudaGraphChildGraphNodeGetGraph;
tcudaGraphAddEmptyNode *cudaGraphAddEmptyNode;
tcudaGraphAddEventRecordNode *cudaGraphAddEventRecordNode;
tcudaGraphEventRecordNodeGetEvent *cudaGraphEventRecordNodeGetEvent;
tcudaGraphEventRecordNodeSetEvent *cudaGraphEventRecordNodeSetEvent;
tcudaGraphAddEventWaitNode *cudaGraphAddEventWaitNode;
tcudaGraphEventWaitNodeGetEvent *cudaGraphEventWaitNodeGetEvent;
tcudaGraphEventWaitNodeSetEvent *cudaGraphEventWaitNodeSetEvent;
tcudaGraphAddExternalSemaphoresSignalNode *cudaGraphAddExternalSemaphoresSignalNode;
tcudaGraphExternalSemaphoresSignalNodeGetParams *cudaGraphExternalSemaphoresSignalNodeGetParams;
tcudaGraphExternalSemaphoresSignalNodeSetParams *cudaGraphExternalSemaphoresSignalNodeSetParams;
tcudaGraphAddExternalSemaphoresWaitNode *cudaGraphAddExternalSemaphoresWaitNode;
tcudaGraphExternalSemaphoresWaitNodeGetParams *cudaGraphExternalSemaphoresWaitNodeGetParams;
tcudaGraphExternalSemaphoresWaitNodeSetParams *cudaGraphExternalSemaphoresWaitNodeSetParams;
tcudaGraphAddMemAllocNode *cudaGraphAddMemAllocNode;
tcudaGraphMemAllocNodeGetParams *cudaGraphMemAllocNodeGetParams;
tcudaGraphAddMemFreeNode *cudaGraphAddMemFreeNode;
tcudaGraphMemFreeNodeGetParams *cudaGraphMemFreeNodeGetParams;
tcudaDeviceGraphMemTrim *cudaDeviceGraphMemTrim;
tcudaDeviceGetGraphMemAttribute *cudaDeviceGetGraphMemAttribute;
tcudaDeviceSetGraphMemAttribute *cudaDeviceSetGraphMemAttribute;
tcudaGraphClone *cudaGraphClone;
tcudaGraphNodeFindInClone *cudaGraphNodeFindInClone;
tcudaGraphNodeGetType *cudaGraphNodeGetType;
tcudaGraphGetNodes *cudaGraphGetNodes;
tcudaGraphGetRootNodes *cudaGraphGetRootNodes;
tcudaGraphGetEdges *cudaGraphGetEdges;
tcudaGraphNodeGetDependencies *cudaGraphNodeGetDependencies;
tcudaGraphNodeGetDependentNodes *cudaGraphNodeGetDependentNodes;
tcudaGraphAddDependencies *cudaGraphAddDependencies;
tcudaGraphRemoveDependencies *cudaGraphRemoveDependencies;
tcudaGraphDestroyNode *cudaGraphDestroyNode;
tcudaGraphInstantiate *cudaGraphInstantiate;
tcudaGraphInstantiateWithFlags *cudaGraphInstantiateWithFlags;
tcudaGraphInstantiateWithParams *cudaGraphInstantiateWithParams;
tcudaGraphExecGetFlags *cudaGraphExecGetFlags;
tcudaGraphExecKernelNodeSetParams *cudaGraphExecKernelNodeSetParams;
tcudaGraphExecMemcpyNodeSetParams *cudaGraphExecMemcpyNodeSetParams;
tcudaGraphExecMemcpyNodeSetParamsToSymbol *cudaGraphExecMemcpyNodeSetParamsToSymbol;
tcudaGraphExecMemcpyNodeSetParamsFromSymbol *cudaGraphExecMemcpyNodeSetParamsFromSymbol;
tcudaGraphExecMemcpyNodeSetParams1D *cudaGraphExecMemcpyNodeSetParams1D;
tcudaGraphExecMemsetNodeSetParams *cudaGraphExecMemsetNodeSetParams;
tcudaGraphExecHostNodeSetParams *cudaGraphExecHostNodeSetParams;
tcudaGraphExecChildGraphNodeSetParams *cudaGraphExecChildGraphNodeSetParams;
tcudaGraphExecEventRecordNodeSetEvent *cudaGraphExecEventRecordNodeSetEvent;
tcudaGraphExecEventWaitNodeSetEvent *cudaGraphExecEventWaitNodeSetEvent;
tcudaGraphExecExternalSemaphoresSignalNodeSetParams *cudaGraphExecExternalSemaphoresSignalNodeSetParams;
tcudaGraphExecExternalSemaphoresWaitNodeSetParams *cudaGraphExecExternalSemaphoresWaitNodeSetParams;
tcudaGraphNodeSetEnabled *cudaGraphNodeSetEnabled;
tcudaGraphNodeGetEnabled *cudaGraphNodeGetEnabled;
tcudaGraphExecUpdate *cudaGraphExecUpdate;
tcudaGraphUpload *cudaGraphUpload;
tcudaGraphLaunch *cudaGraphLaunch;
tcudaGraphExecDestroy *cudaGraphExecDestroy;
tcudaGraphDestroy *cudaGraphDestroy;
tcudaGraphDebugDotPrint *cudaGraphDebugDotPrint;
tcudaUserObjectCreate *cudaUserObjectCreate;
tcudaUserObjectRetain *cudaUserObjectRetain;
tcudaUserObjectRelease *cudaUserObjectRelease;
tcudaGraphRetainUserObject *cudaGraphRetainUserObject;
tcudaGraphReleaseUserObject *cudaGraphReleaseUserObject;
tcudaGetDriverEntryPoint *cudaGetDriverEntryPoint;
tcudaGetExportTable *cudaGetExportTable;
tcudaGetFuncBySymbol *cudaGetFuncBySymbol;
tcudaGetKernel *cudaGetKernel;

int cuewInitCUDART(const char **extra_dll_search_paths) {

#ifdef _WIN32
  const char *paths[] = {   "cudart.dll",
NULL};
#else /* linux */
  const char *paths[] = {   "libcudart.so",
   "/usr/local/cuda/lib64/libcudart.so",
NULL};
#endif


  static int initialized = 0;
  static int result = 0;
  int error;

  if (initialized) {
    return result;
  }

  initialized = 1;
  error = atexit(cuewExitCUDART);

  if (error) {
    result = -2;
    return result;
  }
  cudart_lib = dynamic_library_open_find(paths);
  if (cudart_lib == NULL) { 
    if (extra_dll_search_paths) { 
      cudart_lib = dynamic_library_open_find(extra_dll_search_paths);
    }
  }
  if (cudart_lib == NULL) { result = -1; return result; }

  CUDART_LIBRARY_FIND(cudaDeviceReset)
  CUDART_LIBRARY_FIND(cudaDeviceSynchronize)
  CUDART_LIBRARY_FIND(cudaDeviceSetLimit)
  CUDART_LIBRARY_FIND(cudaDeviceGetLimit)
  CUDART_LIBRARY_FIND(cudaDeviceGetTexture1DLinearMaxWidth)
  CUDART_LIBRARY_FIND(cudaDeviceGetCacheConfig)
  CUDART_LIBRARY_FIND(cudaDeviceGetStreamPriorityRange)
  CUDART_LIBRARY_FIND(cudaDeviceSetCacheConfig)
  CUDART_LIBRARY_FIND(cudaDeviceGetSharedMemConfig)
  CUDART_LIBRARY_FIND(cudaDeviceSetSharedMemConfig)
  CUDART_LIBRARY_FIND(cudaDeviceGetByPCIBusId)
  CUDART_LIBRARY_FIND(cudaDeviceGetPCIBusId)
  CUDART_LIBRARY_FIND(cudaIpcGetEventHandle)
  CUDART_LIBRARY_FIND(cudaIpcOpenEventHandle)
  CUDART_LIBRARY_FIND(cudaIpcGetMemHandle)
  CUDART_LIBRARY_FIND(cudaIpcOpenMemHandle)
  CUDART_LIBRARY_FIND(cudaIpcCloseMemHandle)
  CUDART_LIBRARY_FIND(cudaDeviceFlushGPUDirectRDMAWrites)
  CUDART_LIBRARY_FIND(cudaThreadExit)
  CUDART_LIBRARY_FIND(cudaThreadSynchronize)
  CUDART_LIBRARY_FIND(cudaThreadSetLimit)
  CUDART_LIBRARY_FIND(cudaThreadGetLimit)
  CUDART_LIBRARY_FIND(cudaThreadGetCacheConfig)
  CUDART_LIBRARY_FIND(cudaThreadSetCacheConfig)
  CUDART_LIBRARY_FIND(cudaGetLastError)
  CUDART_LIBRARY_FIND(cudaPeekAtLastError)
  CUDART_LIBRARY_FIND(cudaGetErrorName)
  CUDART_LIBRARY_FIND(cudaGetErrorString)
  CUDART_LIBRARY_FIND(cudaGetDeviceCount)
  CUDART_LIBRARY_FIND(cudaGetDeviceProperties_v2)
  CUDART_LIBRARY_FIND(cudaDeviceGetAttribute)
  CUDART_LIBRARY_FIND(cudaDeviceGetDefaultMemPool)
  CUDART_LIBRARY_FIND(cudaDeviceSetMemPool)
  CUDART_LIBRARY_FIND(cudaDeviceGetMemPool)
  CUDART_LIBRARY_FIND(cudaDeviceGetNvSciSyncAttributes)
  CUDART_LIBRARY_FIND(cudaDeviceGetP2PAttribute)
  CUDART_LIBRARY_FIND(cudaChooseDevice)
  CUDART_LIBRARY_FIND(cudaInitDevice)
  CUDART_LIBRARY_FIND(cudaSetDevice)
  CUDART_LIBRARY_FIND(cudaGetDevice)
  CUDART_LIBRARY_FIND(cudaSetValidDevices)
  CUDART_LIBRARY_FIND(cudaSetDeviceFlags)
  CUDART_LIBRARY_FIND(cudaGetDeviceFlags)
  CUDART_LIBRARY_FIND(cudaStreamCreate)
  CUDART_LIBRARY_FIND(cudaStreamCreateWithFlags)
  CUDART_LIBRARY_FIND(cudaStreamCreateWithPriority)
  CUDART_LIBRARY_FIND(cudaStreamGetPriority)
  CUDART_LIBRARY_FIND(cudaStreamGetFlags)
  CUDART_LIBRARY_FIND(cudaStreamGetId)
  CUDART_LIBRARY_FIND(cudaCtxResetPersistingL2Cache)
  CUDART_LIBRARY_FIND(cudaStreamCopyAttributes)
  CUDART_LIBRARY_FIND(cudaStreamGetAttribute)
  CUDART_LIBRARY_FIND(cudaStreamSetAttribute)
  CUDART_LIBRARY_FIND(cudaStreamDestroy)
  CUDART_LIBRARY_FIND(cudaStreamWaitEvent)
  CUDART_LIBRARY_FIND(cudaStreamAddCallback)
  CUDART_LIBRARY_FIND(cudaStreamSynchronize)
  CUDART_LIBRARY_FIND(cudaStreamQuery)
  CUDART_LIBRARY_FIND(cudaStreamAttachMemAsync)
  CUDART_LIBRARY_FIND(cudaStreamBeginCapture)
  CUDART_LIBRARY_FIND(cudaThreadExchangeStreamCaptureMode)
  CUDART_LIBRARY_FIND(cudaStreamEndCapture)
  CUDART_LIBRARY_FIND(cudaStreamIsCapturing)
  CUDART_LIBRARY_FIND(cudaStreamGetCaptureInfo_v2)
  CUDART_LIBRARY_FIND(cudaStreamUpdateCaptureDependencies)
  CUDART_LIBRARY_FIND(cudaEventCreate)
  CUDART_LIBRARY_FIND(cudaEventCreateWithFlags)
  CUDART_LIBRARY_FIND(cudaEventRecord)
  CUDART_LIBRARY_FIND(cudaEventRecordWithFlags)
  CUDART_LIBRARY_FIND(cudaEventQuery)
  CUDART_LIBRARY_FIND(cudaEventSynchronize)
  CUDART_LIBRARY_FIND(cudaEventDestroy)
  CUDART_LIBRARY_FIND(cudaEventElapsedTime)
  CUDART_LIBRARY_FIND(cudaImportExternalMemory)
  CUDART_LIBRARY_FIND(cudaExternalMemoryGetMappedBuffer)
  CUDART_LIBRARY_FIND(cudaExternalMemoryGetMappedMipmappedArray)
  CUDART_LIBRARY_FIND(cudaDestroyExternalMemory)
  CUDART_LIBRARY_FIND(cudaImportExternalSemaphore)
  CUDART_LIBRARY_FIND(cudaSignalExternalSemaphoresAsync_v2)
  CUDART_LIBRARY_FIND(cudaWaitExternalSemaphoresAsync_v2)
  CUDART_LIBRARY_FIND(cudaDestroyExternalSemaphore)
  CUDART_LIBRARY_FIND(cudaLaunchKernel)
  CUDART_LIBRARY_FIND(cudaLaunchKernelExC)
  CUDART_LIBRARY_FIND(cudaLaunchCooperativeKernel)
  CUDART_LIBRARY_FIND(cudaLaunchCooperativeKernelMultiDevice)
  CUDART_LIBRARY_FIND(cudaFuncSetCacheConfig)
  CUDART_LIBRARY_FIND(cudaFuncSetSharedMemConfig)
  CUDART_LIBRARY_FIND(cudaFuncGetAttributes)
  CUDART_LIBRARY_FIND(cudaFuncSetAttribute)
  CUDART_LIBRARY_FIND(cudaSetDoubleForDevice)
  CUDART_LIBRARY_FIND(cudaSetDoubleForHost)
  CUDART_LIBRARY_FIND(cudaLaunchHostFunc)
  CUDART_LIBRARY_FIND(cudaOccupancyMaxActiveBlocksPerMultiprocessor)
  CUDART_LIBRARY_FIND(cudaOccupancyAvailableDynamicSMemPerBlock)
  CUDART_LIBRARY_FIND(cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags)
  CUDART_LIBRARY_FIND(cudaOccupancyMaxPotentialClusterSize)
  CUDART_LIBRARY_FIND(cudaOccupancyMaxActiveClusters)
  CUDART_LIBRARY_FIND(cudaMallocManaged)
  CUDART_LIBRARY_FIND(cudaMalloc)
  CUDART_LIBRARY_FIND(cudaMallocHost)
  CUDART_LIBRARY_FIND(cudaMallocPitch)
  CUDART_LIBRARY_FIND(cudaMallocArray)
  CUDART_LIBRARY_FIND(cudaFree)
  CUDART_LIBRARY_FIND(cudaFreeHost)
  CUDART_LIBRARY_FIND(cudaFreeArray)
  CUDART_LIBRARY_FIND(cudaFreeMipmappedArray)
  CUDART_LIBRARY_FIND(cudaHostAlloc)
  CUDART_LIBRARY_FIND(cudaHostRegister)
  CUDART_LIBRARY_FIND(cudaHostUnregister)
  CUDART_LIBRARY_FIND(cudaHostGetDevicePointer)
  CUDART_LIBRARY_FIND(cudaHostGetFlags)
  CUDART_LIBRARY_FIND(cudaMalloc3D)
  CUDART_LIBRARY_FIND(cudaMalloc3DArray)
  CUDART_LIBRARY_FIND(cudaMallocMipmappedArray)
  CUDART_LIBRARY_FIND(cudaGetMipmappedArrayLevel)
  CUDART_LIBRARY_FIND(cudaMemcpy3D)
  CUDART_LIBRARY_FIND(cudaMemcpy3DPeer)
  CUDART_LIBRARY_FIND(cudaMemcpy3DAsync)
  CUDART_LIBRARY_FIND(cudaMemcpy3DPeerAsync)
  CUDART_LIBRARY_FIND(cudaMemGetInfo)
  CUDART_LIBRARY_FIND(cudaArrayGetInfo)
  CUDART_LIBRARY_FIND(cudaArrayGetPlane)
  CUDART_LIBRARY_FIND(cudaArrayGetMemoryRequirements)
  CUDART_LIBRARY_FIND(cudaMipmappedArrayGetMemoryRequirements)
  CUDART_LIBRARY_FIND(cudaArrayGetSparseProperties)
  CUDART_LIBRARY_FIND(cudaMipmappedArrayGetSparseProperties)
  CUDART_LIBRARY_FIND(cudaMemcpy)
  CUDART_LIBRARY_FIND(cudaMemcpyPeer)
  CUDART_LIBRARY_FIND(cudaMemcpy2D)
  CUDART_LIBRARY_FIND(cudaMemcpy2DToArray)
  CUDART_LIBRARY_FIND(cudaMemcpy2DFromArray)
  CUDART_LIBRARY_FIND(cudaMemcpy2DArrayToArray)
  CUDART_LIBRARY_FIND(cudaMemcpyToSymbol)
  CUDART_LIBRARY_FIND(cudaMemcpyFromSymbol)
  CUDART_LIBRARY_FIND(cudaMemcpyAsync)
  CUDART_LIBRARY_FIND(cudaMemcpyPeerAsync)
  CUDART_LIBRARY_FIND(cudaMemcpy2DAsync)
  CUDART_LIBRARY_FIND(cudaMemcpy2DToArrayAsync)
  CUDART_LIBRARY_FIND(cudaMemcpy2DFromArrayAsync)
  CUDART_LIBRARY_FIND(cudaMemcpyToSymbolAsync)
  CUDART_LIBRARY_FIND(cudaMemcpyFromSymbolAsync)
  CUDART_LIBRARY_FIND(cudaMemset)
  CUDART_LIBRARY_FIND(cudaMemset2D)
  CUDART_LIBRARY_FIND(cudaMemset3D)
  CUDART_LIBRARY_FIND(cudaMemsetAsync)
  CUDART_LIBRARY_FIND(cudaMemset2DAsync)
  CUDART_LIBRARY_FIND(cudaMemset3DAsync)
  CUDART_LIBRARY_FIND(cudaGetSymbolAddress)
  CUDART_LIBRARY_FIND(cudaGetSymbolSize)
  CUDART_LIBRARY_FIND(cudaMemPrefetchAsync)
  CUDART_LIBRARY_FIND(cudaMemAdvise)
  CUDART_LIBRARY_FIND(cudaMemRangeGetAttribute)
  CUDART_LIBRARY_FIND(cudaMemRangeGetAttributes)
  CUDART_LIBRARY_FIND(cudaMemcpyToArray)
  CUDART_LIBRARY_FIND(cudaMemcpyFromArray)
  CUDART_LIBRARY_FIND(cudaMemcpyArrayToArray)
  CUDART_LIBRARY_FIND(cudaMemcpyToArrayAsync)
  CUDART_LIBRARY_FIND(cudaMemcpyFromArrayAsync)
  CUDART_LIBRARY_FIND(cudaMallocAsync)
  CUDART_LIBRARY_FIND(cudaFreeAsync)
  CUDART_LIBRARY_FIND(cudaMemPoolTrimTo)
  CUDART_LIBRARY_FIND(cudaMemPoolSetAttribute)
  CUDART_LIBRARY_FIND(cudaMemPoolGetAttribute)
  CUDART_LIBRARY_FIND(cudaMemPoolSetAccess)
  CUDART_LIBRARY_FIND(cudaMemPoolGetAccess)
  CUDART_LIBRARY_FIND(cudaMemPoolCreate)
  CUDART_LIBRARY_FIND(cudaMemPoolDestroy)
  CUDART_LIBRARY_FIND(cudaMallocFromPoolAsync)
  CUDART_LIBRARY_FIND(cudaMemPoolExportToShareableHandle)
  CUDART_LIBRARY_FIND(cudaMemPoolImportFromShareableHandle)
  CUDART_LIBRARY_FIND(cudaMemPoolExportPointer)
  CUDART_LIBRARY_FIND(cudaMemPoolImportPointer)
  CUDART_LIBRARY_FIND(cudaPointerGetAttributes)
  CUDART_LIBRARY_FIND(cudaDeviceCanAccessPeer)
  CUDART_LIBRARY_FIND(cudaDeviceEnablePeerAccess)
  CUDART_LIBRARY_FIND(cudaDeviceDisablePeerAccess)
  CUDART_LIBRARY_FIND(cudaGraphicsUnregisterResource)
  CUDART_LIBRARY_FIND(cudaGraphicsResourceSetMapFlags)
  CUDART_LIBRARY_FIND(cudaGraphicsMapResources)
  CUDART_LIBRARY_FIND(cudaGraphicsUnmapResources)
  CUDART_LIBRARY_FIND(cudaGraphicsResourceGetMappedPointer)
  CUDART_LIBRARY_FIND(cudaGraphicsSubResourceGetMappedArray)
  CUDART_LIBRARY_FIND(cudaGraphicsResourceGetMappedMipmappedArray)
  CUDART_LIBRARY_FIND(cudaGetChannelDesc)
  CUDART_LIBRARY_FIND(cudaCreateChannelDesc)
  CUDART_LIBRARY_FIND(cudaCreateTextureObject)
  CUDART_LIBRARY_FIND(cudaDestroyTextureObject)
  CUDART_LIBRARY_FIND(cudaGetTextureObjectResourceDesc)
  CUDART_LIBRARY_FIND(cudaGetTextureObjectTextureDesc)
  CUDART_LIBRARY_FIND(cudaGetTextureObjectResourceViewDesc)
  CUDART_LIBRARY_FIND(cudaCreateSurfaceObject)
  CUDART_LIBRARY_FIND(cudaDestroySurfaceObject)
  CUDART_LIBRARY_FIND(cudaGetSurfaceObjectResourceDesc)
  CUDART_LIBRARY_FIND(cudaDriverGetVersion)
  CUDART_LIBRARY_FIND(cudaRuntimeGetVersion)
  CUDART_LIBRARY_FIND(cudaGraphCreate)
  CUDART_LIBRARY_FIND(cudaGraphAddKernelNode)
  CUDART_LIBRARY_FIND(cudaGraphKernelNodeGetParams)
  CUDART_LIBRARY_FIND(cudaGraphKernelNodeSetParams)
  CUDART_LIBRARY_FIND(cudaGraphKernelNodeCopyAttributes)
  CUDART_LIBRARY_FIND(cudaGraphKernelNodeGetAttribute)
  CUDART_LIBRARY_FIND(cudaGraphKernelNodeSetAttribute)
  CUDART_LIBRARY_FIND(cudaGraphAddMemcpyNode)
  CUDART_LIBRARY_FIND(cudaGraphAddMemcpyNodeToSymbol)
  CUDART_LIBRARY_FIND(cudaGraphAddMemcpyNodeFromSymbol)
  CUDART_LIBRARY_FIND(cudaGraphAddMemcpyNode1D)
  CUDART_LIBRARY_FIND(cudaGraphMemcpyNodeGetParams)
  CUDART_LIBRARY_FIND(cudaGraphMemcpyNodeSetParams)
  CUDART_LIBRARY_FIND(cudaGraphMemcpyNodeSetParamsToSymbol)
  CUDART_LIBRARY_FIND(cudaGraphMemcpyNodeSetParamsFromSymbol)
  CUDART_LIBRARY_FIND(cudaGraphMemcpyNodeSetParams1D)
  CUDART_LIBRARY_FIND(cudaGraphAddMemsetNode)
  CUDART_LIBRARY_FIND(cudaGraphMemsetNodeGetParams)
  CUDART_LIBRARY_FIND(cudaGraphMemsetNodeSetParams)
  CUDART_LIBRARY_FIND(cudaGraphAddHostNode)
  CUDART_LIBRARY_FIND(cudaGraphHostNodeGetParams)
  CUDART_LIBRARY_FIND(cudaGraphHostNodeSetParams)
  CUDART_LIBRARY_FIND(cudaGraphAddChildGraphNode)
  CUDART_LIBRARY_FIND(cudaGraphChildGraphNodeGetGraph)
  CUDART_LIBRARY_FIND(cudaGraphAddEmptyNode)
  CUDART_LIBRARY_FIND(cudaGraphAddEventRecordNode)
  CUDART_LIBRARY_FIND(cudaGraphEventRecordNodeGetEvent)
  CUDART_LIBRARY_FIND(cudaGraphEventRecordNodeSetEvent)
  CUDART_LIBRARY_FIND(cudaGraphAddEventWaitNode)
  CUDART_LIBRARY_FIND(cudaGraphEventWaitNodeGetEvent)
  CUDART_LIBRARY_FIND(cudaGraphEventWaitNodeSetEvent)
  CUDART_LIBRARY_FIND(cudaGraphAddExternalSemaphoresSignalNode)
  CUDART_LIBRARY_FIND(cudaGraphExternalSemaphoresSignalNodeGetParams)
  CUDART_LIBRARY_FIND(cudaGraphExternalSemaphoresSignalNodeSetParams)
  CUDART_LIBRARY_FIND(cudaGraphAddExternalSemaphoresWaitNode)
  CUDART_LIBRARY_FIND(cudaGraphExternalSemaphoresWaitNodeGetParams)
  CUDART_LIBRARY_FIND(cudaGraphExternalSemaphoresWaitNodeSetParams)
  CUDART_LIBRARY_FIND(cudaGraphAddMemAllocNode)
  CUDART_LIBRARY_FIND(cudaGraphMemAllocNodeGetParams)
  CUDART_LIBRARY_FIND(cudaGraphAddMemFreeNode)
  CUDART_LIBRARY_FIND(cudaGraphMemFreeNodeGetParams)
  CUDART_LIBRARY_FIND(cudaDeviceGraphMemTrim)
  CUDART_LIBRARY_FIND(cudaDeviceGetGraphMemAttribute)
  CUDART_LIBRARY_FIND(cudaDeviceSetGraphMemAttribute)
  CUDART_LIBRARY_FIND(cudaGraphClone)
  CUDART_LIBRARY_FIND(cudaGraphNodeFindInClone)
  CUDART_LIBRARY_FIND(cudaGraphNodeGetType)
  CUDART_LIBRARY_FIND(cudaGraphGetNodes)
  CUDART_LIBRARY_FIND(cudaGraphGetRootNodes)
  CUDART_LIBRARY_FIND(cudaGraphGetEdges)
  CUDART_LIBRARY_FIND(cudaGraphNodeGetDependencies)
  CUDART_LIBRARY_FIND(cudaGraphNodeGetDependentNodes)
  CUDART_LIBRARY_FIND(cudaGraphAddDependencies)
  CUDART_LIBRARY_FIND(cudaGraphRemoveDependencies)
  CUDART_LIBRARY_FIND(cudaGraphDestroyNode)
  CUDART_LIBRARY_FIND(cudaGraphInstantiate)
  CUDART_LIBRARY_FIND(cudaGraphInstantiateWithFlags)
  CUDART_LIBRARY_FIND(cudaGraphInstantiateWithParams)
  CUDART_LIBRARY_FIND(cudaGraphExecGetFlags)
  CUDART_LIBRARY_FIND(cudaGraphExecKernelNodeSetParams)
  CUDART_LIBRARY_FIND(cudaGraphExecMemcpyNodeSetParams)
  CUDART_LIBRARY_FIND(cudaGraphExecMemcpyNodeSetParamsToSymbol)
  CUDART_LIBRARY_FIND(cudaGraphExecMemcpyNodeSetParamsFromSymbol)
  CUDART_LIBRARY_FIND(cudaGraphExecMemcpyNodeSetParams1D)
  CUDART_LIBRARY_FIND(cudaGraphExecMemsetNodeSetParams)
  CUDART_LIBRARY_FIND(cudaGraphExecHostNodeSetParams)
  CUDART_LIBRARY_FIND(cudaGraphExecChildGraphNodeSetParams)
  CUDART_LIBRARY_FIND(cudaGraphExecEventRecordNodeSetEvent)
  CUDART_LIBRARY_FIND(cudaGraphExecEventWaitNodeSetEvent)
  CUDART_LIBRARY_FIND(cudaGraphExecExternalSemaphoresSignalNodeSetParams)
  CUDART_LIBRARY_FIND(cudaGraphExecExternalSemaphoresWaitNodeSetParams)
  CUDART_LIBRARY_FIND(cudaGraphNodeSetEnabled)
  CUDART_LIBRARY_FIND(cudaGraphNodeGetEnabled)
  CUDART_LIBRARY_FIND(cudaGraphExecUpdate)
  CUDART_LIBRARY_FIND(cudaGraphUpload)
  CUDART_LIBRARY_FIND(cudaGraphLaunch)
  CUDART_LIBRARY_FIND(cudaGraphExecDestroy)
  CUDART_LIBRARY_FIND(cudaGraphDestroy)
  CUDART_LIBRARY_FIND(cudaGraphDebugDotPrint)
  CUDART_LIBRARY_FIND(cudaUserObjectCreate)
  CUDART_LIBRARY_FIND(cudaUserObjectRetain)
  CUDART_LIBRARY_FIND(cudaUserObjectRelease)
  CUDART_LIBRARY_FIND(cudaGraphRetainUserObject)
  CUDART_LIBRARY_FIND(cudaGraphReleaseUserObject)
  CUDART_LIBRARY_FIND(cudaGetDriverEntryPoint)
  CUDART_LIBRARY_FIND(cudaGetExportTable)
  CUDART_LIBRARY_FIND(cudaGetFuncBySymbol)
  CUDART_LIBRARY_FIND(cudaGetKernel)
  result = 0; // success
  return result;
}
