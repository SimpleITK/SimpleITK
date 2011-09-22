
include(VariableList)

function( configure_file_buildtime filename out_filename )


set( regex_1 "^[^@]*(@[^@]+@[^@]*)+[^@]*$")

file ( STRINGS "${filename}" results REGEX "${regex_1}" )
set( vars "" )

foreach( line ${results})

  set( regex_2 "^[^@]*@([^@]+)@(.*)$" )

  string( REGEX MATCH "${regex_2}" line_match "${line}" )
  list( APPEND vars ${CMAKE_MATCH_1} )
  while( CMAKE_MATCH_1 )
    string( REGEX MATCH "${regex_2}" line_match  "${CMAKE_MATCH_2}" )
    list( APPEND vars ${CMAKE_MATCH_1} )
  endwhile()
    
  list( SORT vars )
  list( REMOVE_DUPLICATES vars )



  
endforeach()

message("vars=${vars}")

VariableListToArgs( vars configure_vars )
message("configure_vars=${configure_vars}")

#message("vars=${configure_vars}")

file( WRITE "${CMAKE_BINARY_DIR}/CMake/configure_file_buildtime.cmake"
  "configure_file( ${filename} ${out_filename} )" )

set( cmd ${CMAKE_COMMAND} "${configure_vars}" -P "${CMAKE_BINARY_DIR}/CMake/configure_file_buildtime.cmake")

add_custom_command(
  OUTPUT ${out_filename}
  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  COMMENT "BuildTime Configure of ${filename} to ${out_filename}\n COMMAND ${cmd}"
  COMMAND  ${cmd}
)

add_custom_target(ConfigureFileBuildtime ALL DEPENDS ${out_filename} )

endfunction()
