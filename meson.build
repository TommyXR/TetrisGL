project('TetrisGL', ['cpp'],
    default_options: [
        'cpp_std=c++2a',
        'default_library=static'
    ]
)

link_args = []
if host_machine.system() == 'windows'
  link_args += '--static'
else
  link_args += '-ldl'
endif

sources = ['src/main.cpp']
includes = [include_directories('include')]
deps = []


subdir('src')
subdir('third_party')


deps += dependency('glfw3', static: true)
deps += dependency('glad', fallback: ['glad', 'glad_dep'])
deps += dependency('sfml-audio', static: true)


executable('tetrisgl',
    sources,
    dependencies: deps,
    include_directories: includes,
    link_args: link_args)
