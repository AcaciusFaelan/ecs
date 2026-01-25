include(FetchContent)

# Dependencies for this Project

# Example with Raylib ___________________________________
# FetchContent_Declare(
#   raylib
#   GIT_REPOSITORY https://github.com/raysan5/raylib.git
#   GIT_TAG master
# )

# set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# FetchContent_MakeAvailable(raylib)
# _______________________________________________________

# Put further Dependencies here:


# Linking Dependencies when necessary
target_link_libraries(${PROJECT_NAME} PRIVATE
  # raylib
)
