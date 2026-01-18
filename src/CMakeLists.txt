target_sources(card-ecg PRIVATE
    main.c
    superloop.c
)

add_subdirectory(display)
add_subdirectory(drivers)
add_subdirectory(utils)
