cmake = import('cmake')

inc = include_directories([
  './include',
  '../include',
  ])

srcs = [
  './src/example.cpp',
  './src/gl.cpp',
]

glfw_proj = cmake.subproject('glfw')
glfw_dep = glfw_proj.dependency('glfw')

deps = [
  s3dmath_dep,
  glfw_dep,
]

if ['windows'].contains(host_machine.system())

elif ['darwin'].contains(host_machine.system())
  
  cocoa_dep = dependency('cocoa', required: true)
  deps += cocoa_dep
  iokit_dep = dependency('IOKit', required: true)
  deps += iokit_dep

elif ['linux'].contains(host_machine.system())

endif

executable(
  'example',
  srcs,
  install: false,
  include_directories: inc,
  dependencies: deps,
  cpp_args: cpp_define_args,
)

