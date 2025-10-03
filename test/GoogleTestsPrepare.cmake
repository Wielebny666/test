# check if GOOGLETEST_SOURCE_FOLDER was specified or if it's empty (default is empty)
set(NO_GOOGLETEST_SOURCE_FOLDER TRUE)
if(GOOGLETEST_SOURCE_FOLDER)
    if(NOT "${GOOGLETEST_SOURCE_FOLDER}" STREQUAL "")
        set(NO_GOOGLETEST_SOURCE_FOLDER FALSE)
    endif()
endif()

# Googletest version
set(GOOGLETEST_VERSION_EMPTY TRUE)

# check if build was requested with a specifc Googletest version
if(DEFINED GOOGLETEST_VERSION)
    if(NOT "${GOOGLETEST_VERSION}" STREQUAL "")
        set(GOOGLETEST_VERSION_EMPTY FALSE)
    endif()
endif()

if(GOOGLETEST_VERSION_EMPTY)
  SET(GOOGLETEST_VERSION "release-1.12.1")
endif()


if(NO_GOOGLETEST_SOURCE_FOLDER)
    # no Googletest source specified, download it from it's repo
    message(STATUS "Googletest ${GOOGLETEST_VERSION} from GitHub repo")

    FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG        ${GOOGLETEST_VERSION}
    )

else()
    # Googletest source was specified
    message(STATUS "Googletest ${GOOGLETEST_VERSION} (source from: ${GOOGLETEST_SOURCE_FOLDER})")

    FetchContent_Declare(
      googletest
      SOURCE_DIR ${GOOGLETEST_SOURCE_FOLDER}
    )

endif()

FetchContent_MakeAvailable(googletest)
