//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
//
// Use of this sample source code is subject to the terms of the Microsoft
// license agreement under which you licensed this sample source code. If
// you did not accept the terms of the license agreement, you are not
// authorized to use this sample source code. For the terms of the license,
// please see the license agreement between you and Microsoft or, if applicable,
// see the LICENSE.RTF on your install media or the root of your tools installation.
// THE SAMPLE SOURCE CODE IS PROVIDED "AS IS", WITH NO WARRANTIES.
//
#ifndef _WATCHDOG_API_H_
#define _WATCHDOG_API_H_


#ifdef __cplusplus
extern "C" {
#endif

//
// Watchdog timer support
//

//
// default actions
//
#define WDOG_NO_DFLT_ACTION         0
#define WDOG_KILL_PROCESS           1
#define WDOG_RESET_DEVICE           2

#define WD_TOTAL_DFLT_ACTION        3

//
// watchdog APIs
//
HANDLE CreateWatchDogTimer (
    LPCWSTR pszWatchDogName,
    DWORD dwPeriod,
    DWORD dwWait,
    DWORD dwDfltAction,
    DWORD dwParam,
    DWORD dwFlags);

HANDLE OpenWatchDogTimer (
    LPCWSTR pszWatchDogName,
    DWORD dwFlags);

BOOL StartWatchDogTimer (
    HANDLE hWatchDog,
    DWORD dwFlags);

BOOL StopWatchDogTimer (
    HANDLE hWatchDog,
    DWORD dwFlags);

BOOL RefreshWatchDogTimer (
    HANDLE hWatchDog,
    DWORD dwFlags);

#ifdef __cplusplus
}
#endif

#endif  // _WATCHDOG_API_H_

