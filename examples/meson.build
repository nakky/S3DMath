
inc = include_directories([
  '../include',
  ])


deps = [
  s3dmath_dep,
]

srcs = [
  'vector.cpp',
]

executable(
  'vector',
  srcs,
  install: false,
  include_directories: inc,
  dependencies: deps,
  cpp_args: cpp_define_args,
)

