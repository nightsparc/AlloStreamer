set(SOURCES
	Cubemap.cpp
    Process.cpp
    Allocator.cpp
    Frame.cpp
    Binoculars.cpp
	Stats.cpp
	StatsUtils.cpp
	to_human_readable_byte_count.cpp
	Barrier.cpp
	Console.cpp
    CommandHandler.cpp
    Config.cpp
    CommandLine.cpp
)
	
set(HEADERS
	Cubemap.hpp
    config.h
    ConcurrentQueue.hpp
    Process.h
    Allocator.h
    Frame.hpp
    Binoculars.hpp
	Stats.hpp
	StatsUtils.hpp
	to_human_readable_byte_count.hpp
	Barrier.hpp
	format.hpp
	Console.hpp
    CommandHandler.hpp
    Config.hpp
    CommandLine.hpp
)

find_package(Boost
  1.54                  # Minimum version
  REQUIRED
  signals
  date_time
  chrono
  system
  filesystem
)
find_package(FFmpeg REQUIRED)
find_package(Readline REQUIRED)

add_library(AlloShared
	STATIC
	${SOURCES} ${HEADERS}
)
target_link_libraries(AlloShared
	${Boost_LIBRARIES}
	${Readline_LIBRARIES}
)
target_include_directories(AlloShared
	PRIVATE
	${Boost_INCLUDE_DIRS}
	${FFMPEG_INCLUDE_DIRS}
	${Readline_INCLUDE_DIRS}
)
set_target_properties(AlloShared
    PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Lib/${CMAKE_BUILD_TYPE}"
)
