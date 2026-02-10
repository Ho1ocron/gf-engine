add_library(core_utils INTERFACE
    ${GFE_INCLUDES_CORE}/utils/bounded_counter.h
)
add_library(gfe::core_utils ALIAS core_utils)
target_include_directories(core_utils
    INTERFACE
        ${GFE_INCLUDES_PUBLIC}/
)
# target_link_libraries(core_utils PUBLIC
# )
