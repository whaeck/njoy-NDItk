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
 *  @brief Add standard subrecord definitions
 *
 *  This adds the following standard properties:
 *    - empty
 *
 *  @param[in] record   the record to which the definitions have to be added
 */
template < typename Record, typename Range, typename PythonClass >
void addStandardSubrecordDefinitions( PythonClass& record ) {

  record
  .def_property_readonly(

    "values",
    [] ( const Record& self ) -> Range
       { return self.values(); },
    "The data values of the subrecord"
  )
  .def_property_readonly(

    "size",
    [] ( const Record& self ) { return self.size(); },
    "The size of the subrecord"
  )
  .def_property_readonly(

    "empty",
    [] ( const Record& self ) { return self.empty(); },
    "Flag indicating whether or not the subrecord is empty"
  )
  .def(

    "to_string",
    [] ( const Record& self ) -> std::string {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      self.print( output );
      return buffer;
    },
    "Return the string representation of the subrecord\n\n"
    "Arguments:\n"
    "    self    the subrecord"
  );
}

/**
 *  @brief Add standard record definitions
 *
 *  This adds the following standard properties:
 *    - keyword
 *
 *  @param[in] record   the record to which the definitions have to be added
 */
template < typename Record, typename Range, typename PythonClass >
void addStandardRecordDefinitions( PythonClass& record ) {

  record
  .def_property_readonly(

    "keyword",
    [] ( const Record& self ) { return self.keyword(); },
    "The record keyword"
  )
  .def_property_readonly(

    "values",
    [] ( const Record& self ) -> Range
       { return self.values(); },
    "The data values of the record"
  )
  .def_property_readonly(

    "size",
    [] ( const Record& self ) { return self.size(); },
    "The size of the record"
  )
  .def_property_readonly(

    "empty",
    [] ( const Record& self ) { return self.empty(); },
    "Flag indicating whether or not the record is empty"
  )
  .def(

    "to_string",
    [] ( const Record& self ) -> std::string {

      std::string buffer;
      auto output = std::back_inserter( buffer );
      self.print( output );
      return buffer;
    },
    "Return the string representation of the record\n\n"
    "Arguments:\n"
    "    self    the record"
  );
}

#endif
