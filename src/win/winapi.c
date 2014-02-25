/* Copyright Joyent, Inc. and other Node contributors. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <assert.h>

#include "uv.h"
#include "internal.h"


/* Ntdll function pointers */
sRtlNtStatusToDosError pRtlNtStatusToDosError;
sNtDeviceIoControlFile pNtDeviceIoControlFile;
sNtQueryInformationFile pNtQueryInformationFile;
sNtSetInformationFile pNtSetInformationFile;
sNtQueryVolumeInformationFile pNtQueryVolumeInformationFile;
sNtQuerySystemInformation pNtQuerySystemInformation;


/* Kernel32 function pointers */
sGetQueuedCompletionStatusEx pGetQueuedCompletionStatusEx;
sSetFileCompletionNotificationModes pSetFileCompletionNotificationModes;
sCreateSymbolicLinkW pCreateSymbolicLinkW;
sCancelIoEx pCancelIoEx;
sInitializeSRWLock pInitializeSRWLock;
sAcquireSRWLockShared pAcquireSRWLockShared;
sAcquireSRWLockExclusive pAcquireSRWLockExclusive;
sTryAcquireSRWLockShared pTryAcquireSRWLockShared;
sTryAcquireSRWLockExclusive pTryAcquireSRWLockExclusive;
sReleaseSRWLockShared pReleaseSRWLockShared;
sReleaseSRWLockExclusive pReleaseSRWLockExclusive;
sInitializeConditionVariable pInitializeConditionVariable;
sSleepConditionVariableCS pSleepConditionVariableCS;
sSleepConditionVariableSRW pSleepConditionVariableSRW;
sWakeAllConditionVariable pWakeAllConditionVariable;
sWakeConditionVariable pWakeConditionVariable;
sUnregisterWait pUnregisterWait;
sUnregisterWaitEx pUnregisterWaitEx;
sRegisterWaitForSingleObject pRegisterWaitForSingleObject;
sGlobalMemoryStatusEx pGlobalMemoryStatusEx;
sQueueUserWorkItem pQueueUserWorkItem;
sGetProcessMemoryInfo pGetProcessMemoryInfo;
sGetAdaptersAddresses pGetAdaptersAddresses;
sInterlockedCompareExchangePointer pInterlockedCompareExchangePointer = NULL;
sInterlockedCompareExchange32 pInterlockedCompareExchange32;
sInterlockedCompareExchange64 pInterlockedCompareExchange64;
sFreeAddrInfoW pFreeAddrInfoW;
sGetAddrInfoW pGetAddrInfoW;

/*
static int is_x64 = (sizeof(void*) == 8);
static PVOID __cdecl InterlockedCompareExchangePointerXLiigo(PVOID volatile *Destination, PVOID Exchange, PVOID Comparand)
{
  if(is_x64)
    return (PVOID) pInterlockedCompareExchange64((LONGLONG volatile*)Destination, (LONGLONG)Exchange, (LONGLONG)Comparand);
  else
    return (PVOID) pInterlockedCompareExchange32((LONG volatile*)Destination, (LONG)Exchange, (LONG)Comparand);
}
*/

void uv_winapi_init() {
  HMODULE ntdll_module;
  HMODULE kernel32_module;

  ntdll_module = GetModuleHandleA("ntdll.dll");
  if (ntdll_module == NULL) {
    uv_fatal_error(GetLastError(), "GetModuleHandleA");
  }

  pRtlNtStatusToDosError = (sRtlNtStatusToDosError) GetProcAddress(
      ntdll_module,
      "RtlNtStatusToDosError");
  if (pRtlNtStatusToDosError == NULL) {
    uv_fatal_error(GetLastError(), "GetProcAddress");
  }

  pNtDeviceIoControlFile = (sNtDeviceIoControlFile) GetProcAddress(
      ntdll_module,
      "NtDeviceIoControlFile");
  if (pNtDeviceIoControlFile == NULL) {
    uv_fatal_error(GetLastError(), "GetProcAddress");
  }

  pNtQueryInformationFile = (sNtQueryInformationFile) GetProcAddress(
      ntdll_module,
      "NtQueryInformationFile");
  if (pNtQueryInformationFile == NULL) {
    uv_fatal_error(GetLastError(), "GetProcAddress");
  }

  pNtSetInformationFile = (sNtSetInformationFile) GetProcAddress(
      ntdll_module,
      "NtSetInformationFile");
  if (pNtSetInformationFile == NULL) {
    uv_fatal_error(GetLastError(), "GetProcAddress");
  }

  pNtQueryVolumeInformationFile = (sNtQueryVolumeInformationFile)
      GetProcAddress(ntdll_module, "NtQueryVolumeInformationFile");
  if (pNtQueryVolumeInformationFile == NULL) {
    uv_fatal_error(GetLastError(), "GetProcAddress");
  }

  pNtQuerySystemInformation = (sNtQuerySystemInformation) GetProcAddress(
      ntdll_module,
      "NtQuerySystemInformation");
  if (pNtQuerySystemInformation == NULL) {
    uv_fatal_error(GetLastError(), "GetProcAddress");
  }

  kernel32_module = GetModuleHandleA("kernel32.dll");
  if (kernel32_module == NULL) {
    uv_fatal_error(GetLastError(), "GetModuleHandleA");
  }

  pGetQueuedCompletionStatusEx = (sGetQueuedCompletionStatusEx) GetProcAddress(
      kernel32_module,
      "GetQueuedCompletionStatusEx");

  pSetFileCompletionNotificationModes = (sSetFileCompletionNotificationModes)
    GetProcAddress(kernel32_module, "SetFileCompletionNotificationModes");

  pCreateSymbolicLinkW = (sCreateSymbolicLinkW)
    GetProcAddress(kernel32_module, "CreateSymbolicLinkW");

  pCancelIoEx = (sCancelIoEx)
    GetProcAddress(kernel32_module, "CancelIoEx");

  pInitializeSRWLock = (sInitializeSRWLock)
    GetProcAddress(kernel32_module, "InitializeSRWLock");

  pAcquireSRWLockShared = (sAcquireSRWLockShared)
    GetProcAddress(kernel32_module, "AcquireSRWLockShared");

  pAcquireSRWLockExclusive = (sAcquireSRWLockExclusive)
    GetProcAddress(kernel32_module, "AcquireSRWLockExclusive");

  pTryAcquireSRWLockShared = (sTryAcquireSRWLockShared)
    GetProcAddress(kernel32_module, "TryAcquireSRWLockShared");

  pTryAcquireSRWLockExclusive = (sTryAcquireSRWLockExclusive)
    GetProcAddress(kernel32_module, "TryAcquireSRWLockExclusive");

  pReleaseSRWLockShared = (sReleaseSRWLockShared)
    GetProcAddress(kernel32_module, "ReleaseSRWLockShared");

  pReleaseSRWLockExclusive = (sReleaseSRWLockExclusive)
    GetProcAddress(kernel32_module, "ReleaseSRWLockExclusive");

  pInitializeConditionVariable = (sInitializeConditionVariable)
    GetProcAddress(kernel32_module, "InitializeConditionVariable");

  pSleepConditionVariableCS = (sSleepConditionVariableCS)
    GetProcAddress(kernel32_module, "SleepConditionVariableCS");

  pSleepConditionVariableSRW = (sSleepConditionVariableSRW)
    GetProcAddress(kernel32_module, "SleepConditionVariableSRW");

  pWakeAllConditionVariable = (sWakeAllConditionVariable)
    GetProcAddress(kernel32_module, "WakeAllConditionVariable");

  pWakeConditionVariable = (sWakeConditionVariable)
    GetProcAddress(kernel32_module, "WakeConditionVariable");

  pUnregisterWait = (sUnregisterWait)
    GetProcAddress(kernel32_module, "UnregisterWait");

  pUnregisterWaitEx = (sUnregisterWaitEx)
    GetProcAddress(kernel32_module, "UnregisterWaitEx");

  pRegisterWaitForSingleObject = (sRegisterWaitForSingleObject)
    GetProcAddress(kernel32_module, "RegisterWaitForSingleObject");

  pGlobalMemoryStatusEx = (sGlobalMemoryStatusEx)
    GetProcAddress(kernel32_module, "GlobalMemoryStatusEx");

  pQueueUserWorkItem = (sQueueUserWorkItem)
    GetProcAddress(kernel32_module, "QueueUserWorkItem");

  //http://msdn.microsoft.com/en-us/library/windows/desktop/ms683219(v=vs.85).aspx
  pGetProcessMemoryInfo = (sGetProcessMemoryInfo)
    GetProcAddress(kernel32_module, "GetProcessMemoryInfo");
  if(pGetProcessMemoryInfo == NULL) {
    pGetProcessMemoryInfo = (sGetProcessMemoryInfo)
      GetProcAddress(GetModuleHandleA("Psapi.dll"), "GetProcessMemoryInfo");
  }

  pGetAdaptersAddresses = (sGetAdaptersAddresses)
    GetProcAddress(GetModuleHandleA("Iphlpapi.dll"), "GetAdaptersAddresses");

  //liigo 2013-8-28
  //InterlockedCompareExchangePointer: This function is implemented using a compiler intrinsic where possible.
  //http://msdn.microsoft.com/en-us/library/windows/apps/ms683568(v=vs.85).aspx
  //pInterlockedCompareExchangePointer = (sInterlockedCompareExchangePointer)
  //  GetProcAddress(kernel32_module, "InterlockedCompareExchangePointer");
  pInterlockedCompareExchange32  = (sInterlockedCompareExchange32) GetProcAddress(kernel32_module, "InterlockedCompareExchange");
  pInterlockedCompareExchange64  = (sInterlockedCompareExchange64) GetProcAddress(kernel32_module, "InterlockedCompareExchange64");
  pInterlockedCompareExchangePointer = (sInterlockedCompareExchangePointer) pInterlockedCompareExchange32; //VC6 always create x86 programs

  pFreeAddrInfoW = (sFreeAddrInfoW)
    GetProcAddress(GetModuleHandleA("Ws2_32.dll"), "FreeAddrInfoW");

  pGetAddrInfoW = (sGetAddrInfoW)
    GetProcAddress(GetModuleHandleA("Ws2_32.dll"), "GetAddrInfoW");
}

