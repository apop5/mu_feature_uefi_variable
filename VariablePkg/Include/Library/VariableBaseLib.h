/** @file
 *
 * Copyright (c) Microsoft Corporation.
 * SPDX -License-Identifier: BSD-2-Clause-Patent
 */

#ifndef VARIABLE_BASE_LIB_H_
#define VARIABLE_BASE_LIB_H_

/// Variable Attribute definitions
#define VARIABLE_ATTRIBUTE

typedef struct _VARIABLE_ACCESS_REQUEST {
  CHAR16      *VariableName;                    /// Similar to UEFI specification
  UINT8       VariableNameSize;                 /// Number of Unicode characters in Variable Name

  EFI_GUID    VariableGuid;

  UINT32      VariableSize;                     /// Size of the variable data

  VOID        *VariableData;                    /// pointer to the variable data buffer

  UINT32      VariableAttributes;               /// Attributes associated with

  UINT32      AuthenticatedDataSize;            /// If this is an authenticated Variable, the size of the authentication data
  VOID        *AuthenticatedData;               /// Pointer to the authentication data
};

/**
 * @brief Read a variable
 *
 * @param VariableRequest  Pointer to the structure containing the variable read request information
 *
 *
 * @retval EFI_SUCCESS - Variable was located and data was returned in structure's VariableData field
 * @retval EFI_NOT_FOUND - Variable was not located
 * @retval EFI_INVALID_PARAMETER - VariableRequest Structure was NULL
 * @retval EFI_INVALID_PARAMETER - VariableRequest's VariableName was NULL
 * @retval EFI_BUFFER_TOO_SMALL - VariableRequest's VariableSize was too small to fit the variable, VariableSize was updated with the required size
 * @retval EFI_ACCESS_DENIED A variable matching VariableRequest was found, but access is not permitted due to attributes or policies
 * @retval EFI_NOT_FOUND A variable matching the VariableRequest structure was not found
 *
 */
typedef EFI_STATUS (EFIAPI *VARIABLE_READ)(
  VARIABLE_ACCESS_REQUEST *VariableRequest
  );

// Do we want to be strict in variable size?
//  i.e. variable L"VariableOne" is of size 0x08, and a variable write attempts to update it to size of 0x0A, should it be rejected and the caller
//   must delete the existing L"VariableOne", passing the existing size, and then write a new variable of 0x0A size?

/**
 * @brief Write a variable
 *
 * @param VariableRequest Pointer to the structure containing the variable write request information
 *
 * @retval EFI_SUCCESS - Variable was written into the variable store
 * @retval EFI_INVALID_PARAMETER VariableReqest structure was NULL
 * @retval EFI_INVALID_PARAMETER VariableRequest structure's VariableName field was NULL
 * @retval EFI_INVALID_PARAMETER VariableRequest structure's VariableSize field was zero
 * @retval EFI_INVALID_PARAMETER VariableRequest structure's VariableData field was NULL
 *
 * @retval EFI_VOLUME_FULL The variable was too large to fit into the available variable space
 *
 * @retval EFI_SECURITY_VIOLATION Variable was not written due to incorrect authentication data
 *
 * @retval EFI_ACCESS_DENIED Access to the variable store returned EFI_DEVICE_ERROR
 */
typedef EFI_STATUS (EFIAPI  *VARIABLE_WRITE)(
  VARIABLE_ACCESS_REQUEST  *VariableRequest
  );

/**
 * @brief Delete a variable
 *
 * @param VariableRequest Pointer to the structure containing the variable read request information
 *
 * @retval EFI_SUCCESS Variable was deleted from the variable store
 * @retval EFI_INVALID_PARAMTER VariableRequest structure was NULL
 * @retval EFI_INVALID_PARAMTER VariableRequest structure's VariableName field was NUL
 * @retval EFI_INVALID_PARAMETER VariableRequest structure's VariableSize field was zero
 * @retval EFI_INVALID_PARAMETER VariableRequest structure's VariableData field was NULL
 * @retval EFI_NOT_FOUND A variable matching the VariableRequest structure was not found
 *
 * @retval EFI_BAD_BUFFER_SIZE VariableRequest structure's VariableSize field did not match the known variable size // Do we want this?
 *
 */
typedef EFI_STATUS (EFIAPI *VARIABLE_DELETE)(
  VARIABLE_ACCESS_REQUEST *VariableRequest
  );

/**
 * @brief Repeated calls to this will return all accessible variables
 *
 */
typedef EFI_STATUS (EFIAPI *VARIABLE_ENUMERATE)(
  VARIABLE_ACCESS_REQUEST *VariableRequest,
  UINT16 *VariableIdentifier
  );

#endif
