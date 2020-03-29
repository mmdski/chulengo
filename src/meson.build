chlib_sources = ['chlerror.c', 'chlmem.c', 'chlxscoords.c']

chlib_c_args = ['-DCHL_COMPILATION']

if target_machine.system() == 'windows'
    chlib = static_library('chlib',
                           [chlib_sources],
                           include_directories : inc,
                           dependencies : [m_dep, glib_dep],
                           c_args : chlib_c_args,
                           name_prefix : '', 
                           name_suffix : 'lib')
else
    chlib = static_library('chlib',
                           chlib_sources,
                           include_directories : inc,
                           dependencies : [m_dep, glib_dep],
                           c_args : chlib_c_args)
endif
