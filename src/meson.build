inc = include_directories('.')

subdir('memory')
subdir('editor')
subdir('input')
subdir('rendering')
subdir('debug')

src = files(
  'app.c',
  'main.c',
  'quil.c',
)

executable(
  meson.project_name(),
  src,
  dependencies: [raylib_dep, input_dep, debug_dep, memory_dep, editor_dep, rendering_dep],
  include_directories: [rstb_inc],
)
