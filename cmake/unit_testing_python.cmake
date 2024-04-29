#######################################################################
# Setup
#######################################################################

enable_testing()

function( add_python_test name source )

  set( test_name "NDItk.python.${name}.test" )
  add_test( NAME ${test_name}
            COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/${source}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
  set_tests_properties( ${test_name}
                        PROPERTIES ENVIRONMENT
                        PYTHONPATH=${tools_PYTHONPATH}:${NDItk_PYTHONPATH}:$ENV{PYTHONPATH})

endfunction()

#######################################################################
# Python unit testing
#######################################################################

message( STATUS "Adding NDItk Python unit testing" )

add_python_test( multigroup.CrossSection          multigroup/Test_NDItk_multigroup_CrossSection.py )
add_python_test( multigroup.FluxWeights           multigroup/Test_NDItk_multigroup_FluxWeights.py )
add_python_test( multigroup.Structure             multigroup/Test_NDItk_multigroup_Structure.py )
add_python_test( multigroup.ReactionCrossSections multigroup/Test_NDItk_multigroup_ReactionCrossSections.py )

