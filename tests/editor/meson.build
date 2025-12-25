test_files = [
  'editor_init_test.c',
  'editor_load_buffer_test.c',
  'time_travel_init.c',
  'time_travel_undo.c',
  'time_travel_redo.c',
]

foreach f : test_files
  name = f.split('.')[0]
  exe = executable(
    name,
    [f],
    dependencies: [editor_dep, memory_dep],
    include_directories: [inc],
  )
  test(name, exe)
endforeach
