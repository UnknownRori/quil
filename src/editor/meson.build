editor_src = files(
  'editor.c',
  'node.c',
  'time_travel.c',
)

editor_lib = static_library(
  'editor',
  editor_src,
  dependencies: [memory_dep],
  include_directories: [inc, rstb_inc],
)

editor_dep = declare_dependency(
  link_with: editor_lib,
  include_directories: [inc, rstb_inc],
)
