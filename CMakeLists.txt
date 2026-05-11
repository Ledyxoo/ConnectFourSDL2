cmake_minimum_required(VERSION 3.10)
project(ConnectFour C)

set(CMAKE_C_STANDARD 11)

# Dossiers d'inclusion
include_directories(include)

# Sources
file(GLOB SOURCES "src/*.c")

# Recherche de SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Executable
add_executable(ConnectFour ${SOURCES})

# Liens des bibliothèques
target_link_libraries(ConnectFour 
    SDL2::SDL2 
    SDL2_image::SDL2_image 
    SDL2_mixer::SDL2_mixer 
    SDL2_ttf::SDL2_ttf
    m
)

# Copie des Assets vers le dossier de build pour le test local
add_custom_command(TARGET ConnectFour POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Assets
    $<TARGET_FILE_DIR:ConnectFour>/Assets
)

# Configuration spécifique à Windows (si nécessaire pour le déploiement)
if(WIN32)
    set_target_properties(ConnectFour PROPERTIES WIN32_EXECUTABLE TRUE)
endif()
