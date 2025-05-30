add_library(sqlite3 STATIC sqlite3/sqlite3.c)
target_include_directories(sqlite3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(rapidxml INTERFACE)
target_include_directories(rapidxml INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/rapidxml
)