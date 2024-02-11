project('dbms-cc', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++20'])

headers = include_directories('headers')

sources = files(
  'src/main.cpp'
  )

deps = [dependency('fmt')]

exe = executable('dbms-cc', 
  sources,
  include_directories: headers,
  dependencies: deps,
  install : true)

test('basic', exe)
