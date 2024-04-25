#ifndef NJOY_NDITK_PYTHON_DEFINITIONS
#define NJOY_NDITK_PYTHON_DEFINITIONS

// system includes
#include <complex>

// other includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "tools/views/views-python.hpp"

namespace python = pybind11;

/**
 *  @brief Add standard record definitions
 *
 *  This adds the following standard properties:
 *
 *  @param[in] record   the record to which the definitions have to be added
 */
template < typename Record, typename PythonClass >
void addStandardRecordDefinitions( PythonClass& record ) {

}

#endif
