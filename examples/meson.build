
inc = include_directories([
  '../include',
  ])

srcs = [
  './vector.cpp',
]

deps = [
  s3dmath_dep,
]

executable(
  'vector',
  srcs,
  install: false,
  include_directories: inc,
  dependencies: deps,
  cpp_args: cpp_define_args,
)

