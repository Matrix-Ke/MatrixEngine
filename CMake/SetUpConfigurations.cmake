# # #尽量不要是强制使用set(CMAKE_BUILD_TYPE release)这种形式， 把配置写死在代码中,如果没有buildType就提供STRING提示选择
# set(DefaultBuildType "Release")
# if(NOT CMAKE_CONFIGURATION_TYPES)  #AND NOT CMAKE_BUILD_TYPE
#     message(STATUS "Setting build type to '${DefaultBuildType}' as none was specified.")
#     set(CMAKE_CONFIGURATION_TYPES "${DefaultBuildType}" CACHE STRING "Choose the type of build." FORCE)
#     # Set the possible values of build type for cmake-gui
#     set_property(CACHE CMAKE_CONFIGURATION_TYPES PROPERTY STRINGS
#     "Debug" "Release" "Profile" "Ship")
# endif()


if(NOT SET_UP_CONFIGURATIONS_DONE)
    set(SET_UP_CONFIGURATIONS_DONE TRUE)

    # No reason to set CMAKE_CONFIGURATION_TYPES if it's not a multiconfig generator
    # Also no reason mess with CMAKE_BUILD_TYPE if it's a multiconfig generator.
    get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    if(isMultiConfig)
        set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Profile" CACHE STRING "" FORCE) 
    else()
        if(NOT CMAKE_BUILD_TYPE)
            message("Defaulting to release build.")
            set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
        endif()
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY HELPSTRING "Choose the type of build")
        # set the valid options for cmake-gui drop-down list
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;Profile")
    endif()
    # now set up the Profile configuration
    # set(CMAKE_C_FLAGS_PROFILE "...")
    set(CMAKE_CXX_FLAGS_PROFILE "${CMAKE_CXX_FLAGS_RELEASE}")
    set(CMAKE_EXE_LINKER_FLAGS_PROFILE "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
    set(CMAKE_SHARED_LINKER_FLAGS_PROFILE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE}")
endif()