target_sources(${PROJECT_NAME} PRIVATE
    main.c
    superloop.c
)

add_subdirectory(display)
add_subdirectory(drivers)
add_subdirectory(utils)
