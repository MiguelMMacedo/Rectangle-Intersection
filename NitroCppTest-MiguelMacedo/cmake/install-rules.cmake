install(
    TARGETS nitro_rectangles_exe
    RUNTIME COMPONENT nitro_rectangles_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
