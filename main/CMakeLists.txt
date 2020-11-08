set(COMPONENT_SRCS main.c sources/connect.c sources/server.c sources/driver.c sources/camera.c sources/led.c)
set(COMPONENT_ADD_INCLUDEDIRS "." "includes/")

register_component()

spiffs_create_partition_image(spiffs ../html FLASH_IN_PROJECT)