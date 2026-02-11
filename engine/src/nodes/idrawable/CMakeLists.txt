add_library(idrawable INTERFACE
    ${GF_INCLUDES_PRIVATE}/nodes/idrawable/idrawable.h
)
add_library(gfe::idrawable ALIAS idrawable)
target_include_directories(idrawable
    INTERFACE
        ${GF_INCLUDES_PUBLIC}/
)
# target_link_libraries(idrawable PUBLIC
# )
