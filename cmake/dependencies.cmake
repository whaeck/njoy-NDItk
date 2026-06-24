cmake_minimum_required( VERSION 3.27 )
include( FetchContent )

FetchContent_Declare( tools
    GIT_REPOSITORY  ../../njoy/tools
    GIT_TAG         9428024113dd96ffb3e2fe87e3bdfec9aa225a32  # NOT A RELEASED VERSION - CHANGE ME!
    )

#######################################################################
# Load dependencies
#######################################################################

if(NDItk.python)
  FetchContent_Declare( pybind11
      GIT_REPOSITORY  ../../pybind/pybind11
      GIT_TAG         a2e59f0e7065404b44dfe92a28aca47ba1378dc4  # tag: v2.13.6
      )
  FetchContent_MakeAvailable(
    pybind11
    )
endif()

if(NDItk.tests)
  FetchContent_Declare( Catch2
      GIT_REPOSITORY  ../../catchorg/Catch2
      GIT_TAG         b670de4fe12ac7c5e858b7de3a14fb4bd18c760e  # tag: v3.14.0
      )
  set( BUILD_SHARED_LIBS ON )
  FetchContent_MakeAvailable(
      Catch2
    )
  set( BUILD_SHARED_LIBS OFF )
endif()

FetchContent_MakeAvailable(
    tools
    )
