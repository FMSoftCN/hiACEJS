
find_path(SECUREC_INCLUDE_DIRS securec.h)
find_library(SECUREC_LIBRARIES sec_config)
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SECUREC DEFAULT_MSG
    SECUREC_INCLUDE_DIRS SECUREC_LIBRARIES)
mark_as_advanced(SECUREC_INCLUDE_DIRS SECUREC_LIBRARIES)

