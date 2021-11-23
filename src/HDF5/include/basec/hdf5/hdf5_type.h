/*******************************************************************************
 * @file hdf5_module.c
 * @author Florian Eigentler
 * @brief @version 0.1
 * @date 2021-11-08
 * @copyright Copyright (c) 2021
 ******************************************************************************/
#ifndef HDF5_TYPE_H
#define HDF5_TYPE_H

#include <hdf5.h>
#include "basec/basec_macro.h"
#include "basec/basec_type.h"

/*******************************************************************************
 * @brief HDF5 type enumeration
 ******************************************************************************/
typedef enum HDF5Type
{
    HDF5Int, /** HDF5 Integer type */
    // HDF5Float,  /** HDF5 Float type*/
    HDF5Double, /** HDF5 Double type*/
    HDF5String, /** HDF5 String type */
    _hdf5_type_max
} hdf5_type_t;

#endif /* HDF5_TYPE_H */