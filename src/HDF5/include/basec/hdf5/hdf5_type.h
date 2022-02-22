/*******************************************************************************
 * @file hdf5_module.h
 * @author Florian Eigentler
 * @brief @version 1.0.0
 * @date 2022-02-22
 * @copyright Copyright (c) 2022 by Florian Eigentler.
 *  This work is licensed under terms of the MIT license (<LICENSE>).
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
    HDF5Double, /** HDF5 Double type*/
    HDF5String, /** HDF5 String type */
    _hdf5_type_max
} hdf5_type_t;

#endif /* HDF5_TYPE_H */