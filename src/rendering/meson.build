rendering_src = files(
  'buffer.c',
  'cursor_carret.c',
)

rendering_lib = static_library(
  'rendering',
  rendering_src,
  dependencies: [raylib_dep, memory_dep, editor_dep],
  include_directories: [inc, rstb_inc],
)

rendering_dep = declare_dependency(
  link_with: rendering_lib,
  include_directories: [inc, rstb_inc],
)
