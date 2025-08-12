cmake_minimum_required( VERSION 3.27 )
include( FetchContent )

FetchContent_Declare( tools
    GIT_REPOSITORY  ../../njoy/tools
    GIT_TAG         b03f7f65070d84009c1ba5ae2e095f2e8a1a6ed4  # tag: v0.4.4
    )

#######################################################################
# Load dependencies
#######################################################################

if(NDItk.python)
  FetchContent_Declare( pybind11
      GIT_REPOSITORY  ../../pybind/pybind11
      GIT_TAG         a2e59f0e7065404b44dfe92a28aca47ba1378dc4 # tag: v2.13.6
      )
  FetchContent_MakeAvailable(
    pybind11
    )
endif()

if(NDItk.tests)
  FetchContent_Declare( Catch2
      GIT_REPOSITORY  ../../catchorg/Catch2
      GIT_TAG         3f0283de7a9c43200033da996ff9093be3ac84dc # tag: v3.3.2
      )
  FetchContent_MakeAvailable(
      Catch2
    )
endif()

FetchContent_MakeAvailable(
    tools
    )
