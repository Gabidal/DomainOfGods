project(
  'Domain Of Gods', 'cpp',
  version : '0.0.1',
  default_options : ['warning_level=1', 'cpp_std=c++17', 'debug=true', 'buildtype=debug']
)

libs = declare_dependency(
  link_args : [
    meson.current_source_dir() + '/Dependencies/TerGen.a',
    meson.current_source_dir() + '/Dependencies/GGUI.lib',
    meson.current_source_dir() + '/Dependencies/libraylib.a'
  ]
)

cpp = meson.get_compiler('cpp')
win = cpp.find_library('Winmm', required: true)

# Source files:
src = files(
  'Src/Entity.cpp',
  'Src/Globals.cpp',
  'Src/Map.cpp',
  'Src/Chaos.cpp',

  'UI/Render.cpp',

  'main.cpp'
)

# Create the executable:
executable(
  'DomainOfGods',
  src,
  dependencies : [libs, win],
)