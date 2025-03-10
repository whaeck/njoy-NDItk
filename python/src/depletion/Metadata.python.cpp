// system includes
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// local includes
#include "NDItk/depletion/Metadata.hpp"
#include "tools/views/views-python.hpp"
#include "definitions.hpp"
#include "read.hpp"

// namespace aliases
namespace python = pybind11;

namespace depletion {

void wrapMetadata( python::module& module, python::module& ) {

  // type aliases
  using Record = njoy::NDItk::depletion::Metadata;

  // wrap views created by this record

  // create the record
  python::class_< Record > record(

    module,
    "Metadata",
    "A group Metadata record for depletion data"
  );

  // wrap the record
  record
  .def(

    python::init< 
      std::string,
      std::string,
      std::string,
      int,
      std::optional< std::string >,
      std::optional< std::string > >(),
    python::arg( "zaid" ), 
    python::arg( "libname" ),
    python::arg( "process" ), 
    python::arg( "incident" ), 
    python::arg( "information" ) = std::nullopt,
    python::arg( "source" ) = std::nullopt,
    "Initialise the record\n\n"
    "Arguments:\n"
    "    self                the metadata\n"
    "    zaid                the zaid of the table\n"
    "    libname             the library name\n"
    "    process             the processing date\n"
    "    incident            the number of incident particles\n"
    "    information         the table information line (optional)\n"
    "    source              the source date (optional)\n"
  )
  .def_property_readonly(

    "zaid",
    &Record::zaid,
    "The zaid of the table"
  )
  .def_property_readonly(

    "information",
    &Record::information,
    "The table information line"
  )
  .def_property_readonly(

    "library_name",
    &Record::libraryName,
    "The library name"
  )
  .def_property_readonly(

    "source_date",
    &Record::sourceDate,
    "The source date"
  )
  .def_property_readonly(

    "processing_date",
    &Record::processingDate,
    "The process date"
  )
  .def_property_readonly(

    "number_incident_particles",
    &Record::numberIncidentParticles,
    "The number of incident particles"
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
    "    self    the metadata"
  );
}

} // depletion namespace
