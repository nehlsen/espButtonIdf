set(BUTTON_INCLUDEDIRS button/include)
set(BUTTON_SRCS
    "button/iot_button.c"
    "button/button.cpp"
)

idf_component_register(
    SRCS ${BUTTON_SRCS}
    INCLUDE_DIRS ${BUTTON_INCLUDEDIRS}
)
