input_src = files(
  'input.c',
)

input_lib = static_library(
  'input',
  input_src,
  dependencies: [raylib_dep],
  include_directories: [inc],
)

input_dep = declare_dependency(
  link_with: input_lib,
  include_directories: [inc],
)
