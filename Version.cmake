# Version info
set(SimpleITK_Major 0)
set(SimpleITK_Minor 5)
set(SimpleITK_Patch 1)

include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
git_describe(GIT_TAG)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/Code/Common/src/sitkVersion.cxx.in" "${CMAKE_CURRENT_BINARY_DIR}/Code/Common/src/sitkVersion.cxx" @ONLY)

