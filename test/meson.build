hm_dep = declare_dependency(link_with: hm_lib, include_directories: '../src')

test_sources = ['tests.c']
test_exe = executable('main', test_sources, dependencies: [hm_dep])
test('main', test_exe)
