# tests

test_env = environment()
test_env.set('G_TEST_SRCDIR', meson.current_source_dir())
test_env.set('G_TEST_BUILDDIR', meson.current_build_dir())

# xscoords tests
testxscoords = executable('testxscoords', ['testxscoords.c'],
                          include_directories : [inc],
                          dependencies : [glib_dep],
                          link_with : [chlib])
test('testxscoords',
     testxscoords,
     env: test_env
     )

vlgnd = find_program('valgrind', required : false)
if vlgnd.found()

     test('testxscoords_mem', vlgnd,
          args : [
               '--leak-check=full',
               '--error-exitcode=33',
               testxscoords.full_path()
               ]
          )

endif
