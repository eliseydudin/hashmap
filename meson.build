project('hashmap', 'c')

sources = ['src/hashmap.c']

hm_lib = shared_library('hashmap', sources, install: true)
install_headers('src/hashmap.h')

if get_option('enable-tests') 
    subdir('test')
endif
