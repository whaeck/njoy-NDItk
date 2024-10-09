########################################################################
# Preamble
########################################################################

cmake_minimum_required( VERSION 3.27 )

set( subproject OFF )
if( DEFINED PROJECT_NAME )
  set( subproject ON )
endif()

project( NDItk
  VERSION 0.1.0
  LANGUAGES CXX
)

include( CTest )
include( CMakeDependentOption )
include( GNUInstallDirs )

########################################################################
# Project-wide setup
########################################################################

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )

cmake_dependent_option(
  NDItk.tests
  "Build the NDItk unit tests and integrate with ctest" ON
  "BUILD_TESTING AND NOT ${subproject}" OFF
)

cmake_dependent_option(
  NDItk.python
  "Build NDItk python bindings" ON
  "NOT ${subproject} OR DEFINED require.NDItk.python " OFF
)

if ( NDItk.python )
  set( require.tools.python CACHE BOOL ON )
endif()

option( NDItk.installation "Install NDItk" ON )

########################################################################
# Dependencies
########################################################################

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.cmake)
include( cmake/dependencies.cmake )

########################################################################
# Project targets
########################################################################

string( CONCAT prefix
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/src>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# NDItk : library
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

add_library( NDItk INTERFACE )
add_library( njoy::NDItk ALIAS NDItk )

target_include_directories( NDItk INTERFACE ${prefix} )

target_link_libraries( NDItk
  INTERFACE
    njoy::tools
)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# NDItk : python bindings
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if (NDItk.python AND NOT TARGET njoy::tools.python)
  message(WARNING "njoy::tools was not built with python enabled.  Disabling build of NDItk's python API.")
  set(NDItk.python OFF)
endif()

if( NDItk.python )

  pybind11_add_module( NDItk.python
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/NDItk.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/MultigroupTable.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/depletion.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/depletion/ReactionMultiplicityType.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/depletion/Multiplicities.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/depletion/ReactionMultiplicities.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/FissionType.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/Metadata.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/CrossSection.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/FluxWeights.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/EnergyGroupStructure.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/ReactionCrossSections.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/TotalCrossSection.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/AverageFissionEnergyRelease.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/FissionNeutronMultiplicity.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/FissionNeutronProduction.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/FissionNeutronSpectrumVector.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/FissionNeutronSpectrumMatrix.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/Velocities.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/HeatingNumbers.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/Kerma.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/OutgoingParticleTypes.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/OutgoingParticleTransportData.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/LegendreMoment.python.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/python/src/multigroup/ScatteringMatrix.python.cpp
      )

  target_link_libraries( NDItk.python PRIVATE njoy::NDItk )
  add_dependencies( NDItk.python njoy::tools.python )
  target_include_directories( NDItk.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/python/src )
  target_compile_options( NDItk.python PRIVATE -fvisibility=hidden )
  set_target_properties( NDItk.python PROPERTIES OUTPUT_NAME NDItk )
  set_target_properties( NDItk.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
  set_target_properties( NDItk.python PROPERTIES POSITION_INDEPENDENT_CODE ON )

  message( STATUS "Building NDItk's python API" )

  set( NDItk_PYTHONPATH "${CMAKE_CURRENT_BINARY_DIR}" )
  # Append potential installation and build paths for tools python module
  set( tools_PYTHONPATH "${CMAKE_CURRENT_BINARY_DIR}/_deps/tools-build" )
  if (tools_DIR)
    set( tools_PYTHONPATH "${tools_PYTHONPATH}:${tools_DIR}/../../../lib64" )
  endif()

  if( NDItk.tests )
    include( cmake/unit_testing_python.cmake )
  endif()

endif()

if( ${NDItk.tests} )
  include( cmake/unit_testing.cmake )
endif()

#######################################################################
# Installation
#######################################################################

if(NDItk.installation)
    include(CMakePackageConfigHelpers)

    install(TARGETS NDItk EXPORT NDItk-targets
      ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
      RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    )

    install(EXPORT NDItk-targets
      FILE "NDItk-targets.cmake"
      NAMESPACE njoy::
      DESTINATION share/cmake/NDItk
    )

    install(DIRECTORY src/
      DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
      FILES_MATCHING PATTERN "*.hpp"
      PATTERN "*test*" EXCLUDE
    )

    string(TOLOWER NDItk lowercasePackageName)

    write_basic_package_version_file("${lowercasePackageName}-config-version.cmake"
      VERSION ${PROJECT_VERSION}
      COMPATIBILITY AnyNewerVersion)

    configure_package_config_file(
      ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${lowercasePackageName}-config.cmake.in
      ${PROJECT_BINARY_DIR}/${lowercasePackageName}-config.cmake
      INSTALL_DESTINATION share/cmake/NDItk
    )

    install(FILES
      "${PROJECT_BINARY_DIR}/${lowercasePackageName}-config.cmake"
      "${PROJECT_BINARY_DIR}/${lowercasePackageName}-config-version.cmake"
      DESTINATION share/cmake/NDItk
    )

    if(NOT subproject)
      set(CPACK_PACKAGE_VENDOR "Los Alamos National Laboratory")
      set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
      include(CPack)
    endif()
endif()
