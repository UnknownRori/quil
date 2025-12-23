inc = include_directories('.')

src = files(
  'app.c',
  'main.c',
  'quil.c',
)

executable(
  meson.project_name(),
  src,
  dependencies: [raylib_dep],
  include_directories: [rstb_inc],
)
