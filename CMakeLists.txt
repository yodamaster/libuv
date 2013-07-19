cmake_minimum_required(VERSION 2.6)

PROJECT(uv)

#SET(CMAKE_SYSTEM_NAME Linux)
#SET(CMAKE_C_COMPILER "mips-openwrt-linux-gcc")
#SET(CMAKE_CXX_COMPILER "mips-openwrt-linux-g++")


SET(CMAKE_C_FLAGS "-std=c89 -Os -pedantic -Wall -Wextra -Wno-unused-parameter -D_LARGEFILE_SOURCE -D_GNU_SOURCE -D_FILE_OFFSET_BITS=64")

SET(	SOURCES
		src/unix/async.c
		src/unix/core.c
		src/unix/dl.c
		src/unix/error.c
		src/unix/fs.c
		src/unix/getaddrinfo.c
		src/unix/linux-core.c
		src/unix/linux-inotify.c
		src/unix/linux-syscalls.c
		src/unix/loop-watcher.c
		src/unix/loop.c
		src/unix/pipe.c
		src/unix/poll.c
		src/unix/process.c
		src/unix/proctitle.c
		src/unix/signal.c
		src/unix/stream.c
		src/unix/tcp.c
		src/unix/thread.c
		src/unix/threadpool.c
		src/unix/timer.c
		src/unix/tty.c
		src/unix/udp.c
		src/fs-poll.c
		src/inet.c
		src/uv-common.c
		src/version.c
	)
# src/unix/aix.c src/unix/fsevents.c(iOS?) src/unix/kqueue.c
	
ADD_LIBRARY(uv ${SOURCES})

INCLUDE_DIRECTORIES(include include/uv-private src)


FILE(GLOB HEADERS "include/*.h")
FILE(GLOB HEADERS_PRIVATE "include/uv-private/*.h")

INSTALL(TARGETS uv DESTINATION lib)
INSTALL(FILES ${HEADERS} DESTINATION include)
INSTALL(FILES ${HEADERS_PRIVATE} DESTINATION include/uv-private)
 