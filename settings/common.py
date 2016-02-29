from os.path import abspath, dirname, join

SETTINGS = dirname(abspath(__file__))

PROJECT_DIR = dirname(SETTINGS)

SOURCE_DIR = join(PROJECT_DIR, 'src')

TEMPLATE_DIRS = [
    join(PROJECT_DIR, 'settings', 'templates'),
]

INCLUDE_DIRS = [
    join(PROJECT_DIR, 'include'),
    join(PROJECT_DIR, 'generated'),
    join(PROJECT_DIR, 'libraries'),
]

DATA_DIR = join(PROJECT_DIR, 'data')

BUILD_DIR = join(PROJECT_DIR, 'build')

# ######### START MACROS ##########
MACROS = [
    'CAPSTAN_DEBUG',
    'CAPSTAN_ASSERT',
    'CAPSTAN_CONSOLE',
]
# ######### END MACROS ##########

# ######### START OUTPUT ##########
OUTPUT_FILENAME = 'capstan'
# ######### END OUTPUT ##########
