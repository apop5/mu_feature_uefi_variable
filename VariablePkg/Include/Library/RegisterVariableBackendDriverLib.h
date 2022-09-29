/** @file
 *
 * Copyright (c) Microsoft Corporation.
 * SPDX -License-Identifier: BSD-2-Clause-Patent
 */

#ifndef REGISTER_VARIABLE_BACKEND_DRIVER_LIB_H_
#define REGISTER_VARIABLE_BACKEND_DRIVER_LIB_H_

typedef struct _VARIABLE_BACKEND_DRIVER {
  CHAR16    BackendStorageDriverName[100];      // Humanreadable name for backend storage driver
  // functions for accessing backend
} VARIABLE_BACKEND_DRIVER;

/**
 * @brief Register a VariableStorage Backend Handler
 *
 * @param DriverBackEnd Pointer to the variable backend handler and associated data
 * @param Handle On success, the handle associated with the registered backend
 *
 * @retval EFI_SUCCSS The backend was successfully registered
 * @retval EFI_INVALID_PARAMETER The backend was not registered due to invalid parameters
 */
EFI_STATUS EFIPAI
RegisterBackendStorage (
  VARIABLE_BACKEND_DRIVER  *DriverBackEnd,
  EFI_HANDLE               *Handle
  );

/**
 * @brief Unregister the associated Backend handler
 *
 * @param Handle The backend handler to unregisters
 * @retval EFI_SUCCESS The backend handler was unregistered
 */
UnRegisterBackendStorage (
  EFI_HANDLE  *Handle
  );

#endif
