
file ( GLOB SimpleITKBasicFiltersSource *.cxx *.h )


macro( generate_filter FILTERNAME )

  set(FILTERNAME  ${FILTERNAME})

  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/sitkDualImageFilterTemplate.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILTERNAME}ImageFilter.h"
    )

  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/sitkDualImageFilterTemplate.cxx.in"
    "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILTERNAME}ImageFilter.cxx"
    )

  set(SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersSource}
    "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILTERNAME}ImageFilter.cxx")

endmacro()


generate_filter( Subtract )
generate_filter( Divide )
generate_filter( Multiply )
generate_filter( Add )
generate_filter( Atan2 )
generate_filter( Mask )
generate_filter( MaskNegated )
generate_filter( Minimum )
generate_filter( Maximum )
generate_filter( SquaredDifference )
generate_filter( BinaryMagnitude )


include_directories (
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${CMAKE_CURRENT_BINARY_DIR}
 )


add_library ( SimpleITKBasicFilters ${SimpleITKBasicFiltersSource} )
target_link_libraries ( SimpleITKBasicFilters SimpleITKCommon ITKBasicFilters )
