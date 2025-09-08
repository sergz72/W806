SET(CMAKE_SYSTEM_NAME Generic)
SET(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.14)

set(CMAKE_C_STANDARD 23)

# specify the cross compiler
SET(CMAKE_C_COMPILER_WORKS 1)

SET(LINKER_SCRIPT ../../gcc_csky.ld)

SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(COMMON_FLAGS "-mhard-float -fdata-sections -ffunction-sections -mcpu=ck804ef -nostartfiles -lm")

SET(CMAKE_C_FLAGS_INIT "${COMMON_FLAGS}")
SET(CMAKE_ASM_FLAGS_INIT "${COMMON_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,-gc-sections,--print-memory-usage -T ${LINKER_SCRIPT}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2")

project(w806_blink C ASM)

add_definitions(-D__weak=__attribute__\(\(weak\)\) -D__packed=__attribute__\(\(__packed__\)\))
add_definitions(-DTLS_CONFIG_CPU_XT804=1 -DGCC_COMPILE=1 -DWM_SWD_ENABLE=1)
if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG)
endif()

file(GLOB SOURCES
        "src/main.c"
        "src/wm_hal_msp.c"
        "../lib/src/wm_hal.c"
        "../lib/src/wm_gpio.c"
        "../lib/src/wm_cpu.c"
        "../wm_it.c"
        "../startup.S"
        "../vectors.S"
        "../lib/system.c"
        "../lib/board_init.c"
        "../lib/trap_c.c"
        "../libc/libc_port.c"
)

include_directories(src ../lib/include/driver ../lib/include ../arch/csi_core ../arch)

add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})

set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map")

set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)
set(IMG_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.img)
set(FLS_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.fls)
set(BASE_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME})

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${BIN_FILE}")

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ../../wm_tool -b ${BIN_FILE} -fc 0 -it 1 -ih 8010000 -ra 8010400 -ua 8010000 -nh 0 -un 0 -vs -o ${BASE_FILE})

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND cat ../../W806_secboot.img ${IMG_FILE} > ${FLS_FILE})
