hm_dep = declare_dependency(link_with: hm_lib, include_directories: '../src')

test_sources = ['test.c']
test_exe = executable('test', test_sources, dependencies: [hm_dep])
test('test', test_exe)

test_sources = ['test_time.c']
test_exe = executable('time', test_sources, dependencies: [hm_dep])
test('time', test_exe)
