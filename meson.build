project('TetrisGL', ['cpp'],
    default_options: [
        'cpp_std=c++2a',
        #'default_library=static'
    ]
)

sources = ['src/main.cpp']
includes = [include_directories('include')]
deps = []


subdir('src')
subdir('third_party')


deps += dependency('glfw3')
deps += dependency('glad', fallback: ['glad', 'glad_dep'])


executable('tetrisgl',
    sources,
    dependencies: deps,
    include_directories: includes,
    link_args: '-ldl')