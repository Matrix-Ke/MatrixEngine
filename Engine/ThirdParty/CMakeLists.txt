


# if(NOT TARGET glfw)
#     option(GLFW_BUILD_EXAMPLES "" OFF)
#     option(GLFW_BUILD_TESTS "" OFF)
#     option(GLFW_BUILD_DOCS "" OFF)
#     option(GLFW_INSTALL "" OFF)
#     add_subdirectory(glfw)
#     set_target_properties(glfw PROPERTIES FOLDER ${third_party_folder}/glfw)
#     set_target_properties(update_mappings PROPERTIES FOLDER ${third_party_folder}/glfw)
# endif()

# if(NOT TARGET spdlog)
#     option(SPDLOG_BUILD_EXAMPLE "" OFF)
#     option(SPDLOG_INSTALL "" OFF)
#     add_subdirectory(spdlog)
#     set_target_properties(spdlog PROPERTIES FOLDER ${third_party_folder}/spdlog)
# endif()




# add_subdirectory(TBB)
fAdd_all_subdirectory()
