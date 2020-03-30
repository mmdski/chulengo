from setuptools import setup

try:
    from sphinx.setup_command import BuildDoc
    sphinx_imported = True
except ImportError:
    sphinx_imported = False

name = 'chulengo'
version = '0.0'
release = '0.0.1'

setup_kwargs = {'cmdclass': {}}

if sphinx_imported:
    docs_source = 'docs/'
    docs_build_dir = 'docs/_build'
    docs_builder = 'html'
    setup_kwargs['cmdclass'].update({'build_sphinx': BuildDoc})
    sphinx_kwargs = {
        'command_options': {
            'build_sphinx': {
                'project': ('setup.py', name),
                'version': ('setup.py', version),
                'release': ('setup.py', release),
                'source_dir': ('setup.py', docs_source),
                'build_dir': ('setup.py', docs_build_dir),
                'builder': ('setup.py', docs_builder)}
        }
    }
    setup_kwargs.update(sphinx_kwargs)

setup(**setup_kwargs)
