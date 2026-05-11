cmake_minimum_required(VERSION 3.10)
project(ConnectFour C)

set(CMAKE_C_STANDARD 11)

# Dossiers d'inclusion
include_directories(include)

# Sources
file(GLOB SOURCES "src/*.c")

# Recherche de SDL2 (Utilise les fichiers de configuration de SDL2)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Executable
add_executable(ConnectFour ${SOURCES})

# Cibles SDL2 (Compatibilité vcpkg / apt)
# vcpkg utilise souvent des noms différents pour les cibles.
# On essaie de lier les cibles modernes, sinon on utilise les variables.
if(TARGET SDL2::SDL2)
    target_link_libraries(ConnectFour PRIVATE SDL2::SDL2)
else()
    target_link_libraries(ConnectFour PRIVATE ${SDL2_LIBRARIES})
endif()

if(TARGET SDL2_image::SDL2_image)
    target_link_libraries(ConnectFour PRIVATE SDL2_image::SDL2_image)
else()
    target_link_libraries(ConnectFour PRIVATE ${SDL2_IMAGE_LIBRARIES})
endif()

if(TARGET SDL2_mixer::SDL2_mixer)
    target_link_libraries(ConnectFour PRIVATE SDL2_mixer::SDL2_mixer)
else()
    target_link_libraries(ConnectFour PRIVATE ${SDL2_MIXER_LIBRARIES})
endif()

if(TARGET SDL2_ttf::SDL2_ttf)
    target_link_libraries(ConnectFour PRIVATE SDL2_ttf::SDL2_ttf)
else()
    target_link_libraries(ConnectFour PRIVATE ${SDL2_TTF_LIBRARIES})
endif()

# Bibliothèque mathématique (uniquement sur Linux/Unix)
if(NOT WIN32)
    find_library(MATH_LIBRARY m)
    if(MATH_LIBRARY)
        target_link_libraries(ConnectFour PRIVATE ${MATH_LIBRARY})
    endif()
endif()

# Copie des Assets vers le dossier de build pour le test local
add_custom_command(TARGET ConnectFour POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Assets
    $<TARGET_FILE_DIR:ConnectFour>/Assets
)

# Configuration spécifique à Windows
if(WIN32)
    # On lie explicitement SDL2main pour que SDL_main soit géré correctement
    if(TARGET SDL2::SDL2main)
        target_link_libraries(ConnectFour PRIVATE SDL2::SDL2main)
    endif()
endif()
