set(APP_NAME "${PROJECT_NAME}-example")

set(APP_MODULE_DIRECTORY "${PROJECT_SOURCE_DIR}/example")
set(APP_SOURCE_DIRECTORY "${APP_MODULE_DIRECTORY}")

file(GLOB_RECURSE Example_HEADERS "*.h")
file(GLOB_RECURSE Example_SOURCES "*.cpp")

add_executable(${APP_NAME} ${Example_SOURCES} ${Example_HEADERS})

target_link_libraries(${APP_NAME} ${LIBRARY_NAME})