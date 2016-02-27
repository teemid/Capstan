from os.path import abspath, dirname, join

MODULE = dirname(dirname(abspath(__file__)))

PROJECT_DIR = dirname(dirname(MODULE))
SOURCE_DIR = join(PROJECT_DIR, 'src')
INCLUDE_DIR = join(PROJECT_DIR, 'include')
DATA_DIR = join(PROJECT_DIR, 'data')
BUILD_DIR = join(PROJECT_DIR, 'build')

OUTPUT_FILENAME = 'capstan'

MACROS = [
    'CAPSTAN_DEBUG',
    'CAPSTAN_ASSERT',
    'CAPSTAN_CONSOLE',
]
