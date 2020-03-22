#
# Aufruf: $ cmake -DOPENSSL_ROOT_DIR:PATH=/usr/local/opt/openssl -DMBED_CERTS=ON ..
#
# Dabei werden Zertifikate in den Bin-Code eingebunden.
#
# Beim Cross-Compiler:
#
# cmake -Duse_amqp=OFF -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake -DMBED_CERTS=ON -DOWASYS=ON -Duse_default_uuid=ON -DCMAKE_C_FLAGS="-s -rdynamic -funwind-tables -mapcs-frame" -DCMAKE_PREFIX_PATH=/Volumes/crosstool/arm-owa3x-linux-gnueabi/arm-owa3x-linux-gnueabi/sysroot/usr -DCURL_LIBRARY=/Volumes/crosstool/curl-for-owa3x/lib/libcurl.a -DCURL_INCLUDE_DIR=/Volumes/crosstool/curl-for-owa3x/include -DOPENSSL_ROOT_DIR:PATH=/Volumes/crosstool/arm-owa3x-linux-gnueabi/arm-owa3x-linux-gnueabi/sysroot/usr -Dskip_samples=ON ..
# cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake  ..
# cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake -G Xcode ..
#
cmake_minimum_required(VERSION 3.4)

include_directories(owa4x)

#
# C-Definitions:
#

SET (SOURCES main.c logger.c d-sensors.c watchdog.c sms.c
             commands.c notify.c loop.c user.c
             owasys-rtu-module.c owasys-io-module.c owasys-gsm-module.c)

add_executable(gsm-alarm ${SOURCES})

target_link_libraries(gsm-alarm dl pthread systemd)
