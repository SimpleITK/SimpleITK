
file ( GLOB SimpleITKBasicFiltersSource *.cxx *.h )


macro( generate_dual_filter FILTERNAME )

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

macro( generate_single_filter FILTERNAME )

  set(FILTERNAME  ${FILTERNAME})

  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/sitkImageFilterTemplate.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILTERNAME}ImageFilter.h"
    )

  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/sitkImageFilterTemplate.cxx.in"
    "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILTERNAME}ImageFilter.cxx"
    )

  set(SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersSource}
    "${CMAKE_CURRENT_BINARY_DIR}/sitk${FILTERNAME}ImageFilter.cxx")

endmacro()


generate_dual_filter( Subtract )
generate_dual_filter( Divide )
generate_dual_filter( Multiply )
generate_dual_filter( Add )
generate_dual_filter( Atan2 )
generate_dual_filter( Mask )
generate_dual_filter( MaskNegated )
generate_dual_filter( Minimum )
generate_dual_filter( Maximum )
generate_dual_filter( SquaredDifference )
generate_dual_filter( BinaryMagnitude )

generate_dual_filter( Cos )
generate_dual_filter( Sin )
generate_dual_filter( Tan )

include_directories (
 ${CMAKE_CURRENT_SOURCE_DIR}
 ${CMAKE_CURRENT_BINARY_DIR}
 )


add_library ( SimpleITKBasicFilters ${SimpleITKBasicFiltersSource} )
target_link_libraries ( SimpleITKBasicFilters SimpleITKCommon ITKBasicFilters )
