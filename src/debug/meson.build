debug_src = files(
  'input_debug.c',
)

debug_lib = static_library(
  'input',
  debug_src,
  dependencies: [raylib_dep, input_dep],
  include_directories: [inc],
)

debug_dep = declare_dependency(
  link_with: debug_lib,
  include_directories: [inc],
)
