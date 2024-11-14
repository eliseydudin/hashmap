project('hashmap', 'c')

sources = ['src/hashmap.c']

hm_lib = shared_library('hashmap', sources)

if get_option('enable-tests') 
    subdir('test')
endif
