cmake_minimum_required(VERSION 3.7)

set(CMAKE_SYSTEM_NAME Generic)  #目标机的OS，Generic表示目标机无操作系统
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)   #CMake识别相关的C和C++交叉编译器

set(AS arm-none-eabi-as)
set(AR arm-none-eabi-ar)
set(CP arm-none-eabi-objcopy)
set(DP arm-none-eabi-objdump)
set(SZ arm-none-eabi-size)

#Uncomment for hardware floating point
#SET(FPU_FLAGS "-mfloat-abi=hard -mfpu=fpv4-sp-d16")
#add_definitions(-DARM_MATH_CM4 -DARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING -D__FPU_PRESENT=1)

set(Fpu "-mfloat-abi=soft")
set(Mcu "-mcpu=cortex-m4 -mthumb -mthumb-interwork")

set(Cmp "-ffunction-sections -fdata-sections")

set(All "${Mcu} ${Fpu} ${Cmp} -g -fno-common -fmessage-length=0 -specs=nosys.specs -specs=nano.specs  -u _printf_float")

set(CMAKE_C_FLAGS_INIT "${All} -std=gnu99")
set(CMAKE_CXX_FLAGS_INIT "${All} -fno-unwind-tables -fno-exceptions -std=c++11 -Wwrite-strings")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${Mcu} -Wl,-gc-sections,--print-memory-usage -T ${CMAKE_SOURCE_DIR}/Core/LinkScript.ld")

project(ArmCpp CXX C ASM)   #项目名称，支持C++

file(GLOB Src "Core/*.*" "App/*.*" "MspLib/*.*" "Cmd/*.*" "Dev/*.*"
        "DtLib/*.*"
        "DtLib/DtFs/*.*"
        "DtLib/DtOs/*.*"
        "DtLib/DtUtil/*.*"
        "DtLib/DtCmd/*.*"
        "DtLib/Chip/*.*"
        "DtLib/Math/*.*"
        )

include_directories(Core App MspLib Cmd Dev
        DtLib
        DtLib/DtFs
        DtLib/DtOs
        DtLib/DtUtil
        DtLib/DtCmd
        DtLib/Chip
        DtLib/Math
        Dsp
        )

#link_libraries("Dsp/libarm_cortexM4lf_math.a")

add_executable(ArmCpp.elf ${Src} Cmd/G1.cpp)   #生成可执行文件

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map")

add_custom_command(TARGET ArmCpp.elf POST_BUILD
        COMMAND ${SZ} ArmCpp.elf
        COMMAND ${DP} -D ArmCpp.elf > Hello.s
        )