# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Generated CMake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Inicializa o SDK do Raspberry Pi Pico
set(PICO_BOARD pico_w CACHE STRING "Board type")
include(pico_sdk_import.cmake)

project(interrupcao C CXX ASM)

# Inicializa o SDK do Pico
pico_sdk_init()

# Adiciona o executável
add_executable(interrupcao interrupcao.c )

pico_set_program_name(interrupcao "interrupcao")
pico_set_program_version(interrupcao "0.1")

# Gera o cabeçalho .h a partir do .pio
pico_generate_pio_header(interrupcao ${CMAKE_CURRENT_LIST_DIR}/interrupcao.pio)


# Ativa a saída padrão via USB
pico_enable_stdio_uart(interrupcao 0)
pico_enable_stdio_usb(interrupcao 1)

# Adiciona as bibliotecas padrão e as necessárias
target_link_libraries(interrupcao
    pico_stdlib
    hardware_pio
    hardware_adc  # Adicionando a biblioteca do ADC
)

# Adiciona diretórios de inclusão
target_include_directories(interrupcao PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Gera arquivos binários adicionais
pico_add_extra_outputs(interrupcao)
