project(
  'katze',
  'cpp',
  version: '0.1.0',
  license: 'MIT',
  default_options: ['warning_level=3', 'cpp_std=c++17']
)

dependencies = [
  dependency('sdl3'),
  dependency('sdl3-ttf'),
]

include_dir = include_directories('include')

subdir('include')
subdir('src')

katze_lib = library(
  meson.project_name(),
  katze_sources,
  version: meson.project_version(),
  dependencies: dependencies,
  include_directories: include_dir,
  install: true,
)

katze_dep = declare_dependency(
  link_with: katze_lib,
  version: meson.project_version(),
  dependencies: dependencies,
  include_directories: include_dir,
)

if get_option('examples')
  subdir('examples')
endif

import('pkgconfig').generate(
  katze_lib,
  name: 'libkatze',
  description: 'GUI library written in C++17',
  version: meson.project_version(),
  filebase: meson.project_name(),
  requires: dependencies,
)
