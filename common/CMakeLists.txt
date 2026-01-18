target_sources(${PROJECT_NAME} PRIVATE Startup.S)

target_link_options(${PROJECT_NAME} PRIVATE
    "-T${CMAKE_CURRENT_SOURCE_DIR}/aduc706x_rom.ld"
)
