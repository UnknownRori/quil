inc = include_directories('.')

subdir('input')
subdir('debug')

src = files(
  'app.c',
  'main.c',
  'quil.c',
)

executable(
  meson.project_name(),
  src,
  dependencies: [raylib_dep, input_dep, debug_dep],
  include_directories: [rstb_inc],
)
