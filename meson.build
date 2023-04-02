project(
  'Domain Of Gods', 'cpp',
  version : '0.0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17', 'debug=true', 'buildtype=debug']
)

libdir = meson.current_source_dir() + './Dependencies/'

cpp = meson.get_compiler('cpp')
GGUI = cpp.find_library('GGUI', dirs : libdir)
TerGen = cpp.find_library('TerGen', dirs : libdir)

# Link GGUI and TerGen to this project:
libGGUI = declare_dependency(link_with : GGUI)
libTerGen = declare_dependency(link_with : TerGen)

# Source files:
src = files(
  'Src/Map.cpp',


  'main.cpp'
)

# Create the executable:
executable(
  'DomainOfGods',
  src,
  dependencies : [libGGUI, libTerGen],
)