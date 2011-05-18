## A macro to generate master header files that can
## be rolled up into a single top level include.
macro ( CreateLibMasterHeader LIBNAME MASTERHEADER LIBHEADERS)

  if( NOT EXISTS  ${MASTERHEADER} )
    MESSAGE( "Writing Rollup Header: ${MASTERHEADER}" )
    file ( WRITE ${MASTERHEADER}
      "#ifndef __${LIBNAME}_h__\n"
      "#define __${LIBNAME}_h__\n"
      "\n"
      )
    foreach ( CURRHEADER ${LIBHEADERS} )
      GET_FILENAME_COMPONENT ( CURR_SHORT_NAME ${CURRHEADER} NAME )
      file( APPEND ${MASTERHEADER} "#include \"${CURR_SHORT_NAME}\"\n" )
    endforeach( CURRHEADER )
    file ( APPEND ${MASTERHEADER} "#endif // __${LIBNAME}_h__\n" )
  else()
    MESSAGE( "Skipping Rollup Header Write: ${MASTERHEADER}" )
  endif()

endmacro( CreateLibMasterHeader )

