cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include(pico_sdk_import.cmake)

# We also need PICO EXTRAS
#include(pico_extras_import.cmake)

project(mcume C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

add_subdirectory(lib/FatFs_SPI)
add_subdirectory(lib/sdcard)
#add_subdirectory(lib/tinyusb)

include_directories(./lib/FatFs_SPI)
include_directories(./lib/sdcard)

include_directories($ENV{PICO_SDK_PATH}/lib/tinyusb/hw)
include_directories($ENV{PICO_SDK_PATH}/lib/tinyusb/src)

include_directories(config)
#include_directories(vga_t4)
#include_directories(picovga_t4)
include_directories(picovga_t4_vgaboard)
include_directories(tft_t)
include_directories(psram)

set(PICOSPECCY_SOURCES 
		picospeccy/Z80.c 
		picospeccy/AY8910.c
		picospeccy/spec.c
		picospeccy/zx_filetyp_z80.c
		picospeccy/emuapi.cpp
		picospeccy/picospeccy.cpp
		picospeccy/AudioPlaySystem.cpp
	)

include_directories(picocpc/include)
set(PICOCPC_SOURCES
		picocpc/emuapi.cpp
		picocpc/picocpc.cpp
		picocpc/cpc.cpp
        picocpc/CRTC.cpp
		picocpc/GA.cpp
        picocpc/Processor.cpp
		picocpc/Bus.cpp
		picocpc/Memory.cpp
		picocpc/Display.cpp
		picocpc/hid_app.c
        picocpc/PPI.cpp
		picocpc/AY8910.c
		picocpc/include/KeyManager.h
		picocpc/KeyManager.cpp
		picocpc/BusCConnector.cpp
		picocpc/include/BusCConnector.h
        picocpc/ROMLoader.cpp
		picocpc/include/ROMLoader.h
)

set(PICOSND_SOURCES
#		picosnd/LibFC14/Dump.cpp
#		picosnd/LibFC14/FC_Data.cpp
#		picosnd/LibFC14/FC.cpp
#		picosnd/LibFC14/fc14audiodecoder.cpp
#		picosnd/LibFC14/LamePaulaMixer.cpp
#		picosnd/LibFC14/LamePaulaVoice.cpp
#		picosnd/LibFC14/Paula.cpp
#		picosnd/StSnd/digidrum.cpp
#		picosnd/StSnd/LzhLib.cpp
#		picosnd/StSnd/Ym2149Ex.cpp
#		picosnd/StSnd/Ymload.cpp
#		picosnd/StSnd/YmMusic.cpp
#		picosnd/StSnd/YmUserInterface.cpp
		picosnd/sndplay.cpp
		picosnd/sid.cpp
		picosnd/reSID.cpp
		picosnd/emuapi.cpp
		picosnd/AudioPlaySystem.cpp
		picosnd/picosnd.cpp
	)

set(VGA_T4_SOURCES 
		vga_t4/VGA_t4.cpp
		vga_t4/scanvideo.c
	)

set(PICOVGA_T4_VGABOARD_SOURCES
		picovga_t4_vgaboard/VGA_t4.cpp
		picovga_t4_vgaboard/vga.cpp
		picovga_t4_vgaboard/vga_vmode.cpp
)

set(PICOVGA_T4_SOURCES 
		picovga_t4/VGA_t4.cpp
		picovga_t4/vga.cpp
		picovga_t4/vga_vmode.cpp
)

set(PSRAM_SOURCES 
		psram/psram_t.cpp
	)

set(TFT_T_SOURCES 
		tft_t/tft_t_dma.cpp
	)

set(GFXENGINE_SOURCES 
		gfxengine/gfxengine.cpp
	)

set(TESTIO_SOURCES 
		testio/testio.cpp
		testio/emuapi.cpp
	)

set(TESTVGA_SOURCES
        testvga/testvga.cpp
)

set(TESTKEYMAX_SOURCES 
		testkeymax/testkeymax.cpp
		testkeymax/emuapi.cpp
	)

set(TESTPSRAM_SOURCES 
		testpsram/testpsram.cpp
		testpsram/emuapi.cpp
	)

# Vic20,ZX81,ZX Spectrum,Colem
#add_compile_definitions(OVERRULE_WIDTH=320 OVERRULE_HEIGHT=192)

add_executable(mcume
#		${GFXENGINE_SOURCES}
#		${PICO20_SOURCES}
#		${PICO64_SOURCES}
#		${PICO81_SOURCES}
#		${PICO800_SOURCES}
#		${PICO5200_SOURCES}
#		${PICO8086_SOURCES}
#		${PICOCOLEM_SOURCES}
#		${PICOO2EM_SOURCES}
#		${PICOVCS_SOURCES}
#		${PICOSPECCY_SOURCES}
		${PICOCPC_SOURCES}
#		${PICONOFRENDO_SOURCES}
#		${PICOSND_SOURCES}
#		${TESTIO_SOURCES}
#       ${TESTVGA_SOURCES}
#		${TESTKEYMAX_SOURCES}
#		${TESTPSRAM_SOURCES}
#		${PICOVALIDATION_SOURCES}
#		${PSRAM_SOURCES}
#		${VGA_T4_SOURCES}
		${PICOVGA_T4_VGABOARD_SOURCES}
#       ${PICOVGA_T4_SOURCES}
#       ${TFT_T_SOURCES}
	)


#	pico_generate_pio_header(mcume ${CMAKE_CURRENT_LIST_DIR}/vga_t4/timing.pio)
#	pico_generate_pio_header(mcume ${CMAKE_CURRENT_LIST_DIR}/vga_t4/scanvideo.pio)
#	pico_generate_pio_header(mcume ${CMAKE_CURRENT_LIST_DIR}/picovga_t4/picovga.pio)
pico_generate_pio_header(mcume ${CMAKE_CURRENT_LIST_DIR}/picovga_t4_vgaboard/picovga.pio)

set(SD_CS "22" CACHE STRING "Specify the Chip Select GPIO pin for the SD card")
set(SD_SCK "5" CACHE STRING "Specify the Clock GPIO pin for the SD card")
set(SD_MOSI "18" CACHE STRING "Select the Master Out Slave In GPIO pin for the SD card")
set(SD_MISO "19" CACHE STRING "Select the Master In Slave Out GPIO pin for the SD card")

target_compile_definitions(mcume PRIVATE
		SDCARD_PIN_SPI0_CS=${SD_CS}
		SDCARD_PIN_SPI0_SCK=${SD_SCK}
		SDCARD_PIN_SPI0_MOSI=${SD_MOSI}
		SDCARD_PIN_SPI0_MISO=${SD_MISO}
		SDCARD_PIO=pio1
		SDCARD_PIO_SM=0
)

add_compile_definitions(mcume PRIVATE
		PICO_SCANVIDEO_PLANE_COUNT=3
		PICO_SCANVIDEO_MAX_SCANLINE_BUFFER2_WORDS=10
		PICO_SCANVIDEO_MAX_SCANLINE_BUFFER3_WORDS=10
)

# Make sure TinyUSB can find the config.h file
target_include_directories(mcume PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(mcume PRIVATE
		pico_multicore
		pico_stdlib
		sdcard
		FatFs_SPI
		#        pico_scanvideo_dpi
		hardware_spi
		hardware_gpio
		hardware_pio
		hardware_adc
		hardware_pwm
		# For USB keyboard, make sure these are commented out if you need USB Serial output shown.
		tinyusb_host
		tinyusb_board
	)

target_compile_options(mcume PUBLIC -O3)
#target_compile_options(mcume PUBLIC -Wall -Wextra -Wno-unused-function -Wno-unused-parameter)

IF (NOT DEFINED N_SD_CARDS)
    SET(N_SD_CARDS 1)
ENDIF()
target_compile_definitions(mcume PUBLIC N_SD_CARDS=${N_SD_CARDS})

pico_enable_stdio_uart(mcume 0)
pico_enable_stdio_usb(mcume 0)

pico_add_extra_outputs(mcume)

