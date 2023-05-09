project(${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cc")
list(REMOVE_ITEM SOURCES "main.cc")
message(STATUS "Found sources: ${SOURCES}")

add_executable("ftp_server")
set_target_properties("ftp_server" PROPERTIES ENABLE_EXPORTS TRUE)

target_sources("ftp_server"
    PRIVATE
      "main.cc"
    PUBLIC
      ${SOURCES}
)

target_include_directories(
    "ftp_server"
    PRIVATE
      .
    PUBLIC
      $<BUILD_INTERFACE:${PROJECT_INCLUDE_DIR}>
)
