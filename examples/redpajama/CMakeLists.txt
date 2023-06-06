set(TARGET redpajama)
set(CHAT_TARGET redpajama-chat)
set(QUANTIZE_TARGET quantize-gptneox)

add_executable(${TARGET}
  main-redpajama.cpp
  gptneox.cpp
  common-gptneox.cpp
  )

target_link_libraries(${TARGET} PRIVATE llama ${CMAKE_THREAD_LIBS_INIT})
target_compile_features(${TARGET} PRIVATE cxx_std_11)
if(TARGET BUILD_INFO)
  add_dependencies(${TARGET} BUILD_INFO)
endif()

# -- redpajama-chat
add_executable(${CHAT_TARGET}
  main-redpajama-chat.cpp
  gptneox.cpp
  common-gptneox.cpp
  )
target_link_libraries(${CHAT_TARGET} PRIVATE llama ${CMAKE_THREAD_LIBS_INIT})
target_compile_features(${CHAT_TARGET} PRIVATE cxx_std_11)
if(TARGET BUILD_INFO)
  add_dependencies(${CHAT_TARGET} BUILD_INFO)
endif()

# -- quantize-gptneox
add_executable(${QUANTIZE_TARGET}
  quantize-gptneox.cpp
  gptneox.cpp
  common-gptneox.cpp
  )
target_link_libraries(${QUANTIZE_TARGET} PRIVATE llama ${CMAKE_THREAD_LIBS_INIT})
target_compile_features(${QUANTIZE_TARGET} PRIVATE cxx_std_11)
if(TARGET BUILD_INFO)
  add_dependencies(${QUANTIZE_TARGET} BUILD_INFO)
endif()
