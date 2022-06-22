from setuptools import setup

try:
    from sphinx.setup_command import BuildDoc
    sphinx_imported = True
except ImportError:
    sphinx_imported = False

name = 'chulengo'
version = '0.0'
release = '0.0.1'

with open('README.md', 'r') as fh:
    long_description = fh.read()

setup_kwargs = {
    'name': name,
    'version': release,
    'packages': ['chulengo'],
    'url': 'https://github.com/mmdski/chulengo',
    'classifiers': [
        'Development Status :: 2 - Pre-Alpha',
        'Intended Audience :: Science/Research',
        'License :: OSI Approved :: GNU General Public License v3 (GPLv3)',
        'Programming Language :: Python :: 3',
        'Topic :: Scientific/Engineering :: Hydrology'
    ],
    'description': 'computational hydraulics',
    'long_description': long_description,
    'long_description_content_type': 'text/markdown',
    'install_requires': ['numpy==1.22.0', 'scipy'],
    'license': 'GPLv3',
    'cmdclass': {}}

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
