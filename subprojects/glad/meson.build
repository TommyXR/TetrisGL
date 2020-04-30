project('glad', 'c')

inc = include_directories('include')

# library() is an unspecified library (static/dynamic).
# it can be specified with options in the project() function.
# See /meson.build
glad_lib = library('glad',
    'src/glad.c',
    include_directories: inc,
    link_args: '-ldl')


glad_dep = declare_dependency(
    link_with: glad_lib)
