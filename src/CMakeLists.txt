# Set the sources for the library
set(SOURCES 
    CayenneLPP.cpp
)

# Add the library target
add_library(CayenneLPP ${SOURCES})

# Include directories for headers
target_include_directories(CayenneLPP PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
