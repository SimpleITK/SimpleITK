#
# java Examples
#

sitk_add_java_test( Example.ImageGetSetBuffer
        "${CMAKE_CURRENT_SOURCE_DIR}/ImageGetSetBuffer.java"
        DATA{${SimpleITK_DATA_ROOT}/Input/RA-Short.nrrd})
