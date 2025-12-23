memory_src = files(
  'arena.c',
)

memory_lib = static_library(
  'memory',
  memory_src,
  dependencies: [],
  include_directories: [inc, rstb_inc],
)

memory_dep = declare_dependency(
  link_with: memory_lib,
  include_directories: [inc, rstb_inc],
)
