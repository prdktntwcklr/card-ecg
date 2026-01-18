target_sources(card-ecg PRIVATE Startup.S)

target_link_options(card-ecg PRIVATE
    "-T${CMAKE_CURRENT_SOURCE_DIR}/aduc706x_rom.ld"
)
