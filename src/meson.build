s3dmath_inc = include_directories('../include')

s3dmath_srcs = [
  'Common.cpp',
  'CPU.cpp',
  'GeometricNode.cpp',
  'MathematicSystem.cpp',
  'Matrix.cpp',
  'Quaternion.cpp',
  'Vector.cpp',
  'Color.cpp',
  'Entity.cpp',
  'EntityFunction.cpp',
  'Camera.cpp',
  'RootEntity.cpp',
  'RenderList.cpp',
]


s3dmath_lib = static_library('s3dmath',
                s3dmath_srcs,
                install: true,
                include_directories: s3dmath_inc,
                cpp_args: cpp_define_args
                )
