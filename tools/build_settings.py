from os.path import abspath, dirname, join


TOOLS_DIR = dirname(abspath(__file__))


PROJECT_DIR = dirname(TOOLS_DIR)


MAIN_SOURCE_DIR = join(PROJECT_DIR, 'capstan')


SOURCE_DIR = join(MAIN_SOURCE_DIR, 'src')


INCLUDE_DIRS = [
    join(MAIN_SOURCE_DIR, 'include'),
    join(MAIN_SOURCE_DIR, 'generated'),
    join(MAIN_SOURCE_DIR, 'libraries'),
]


DATA_DIR = join(PROJECT_DIR, 'data')


BUILD_DIR = join(PROJECT_DIR, 'build')


# ######### START MACROS ##########
MACROS = [
    'CAPSTAN_DEBUG',
    'CAPSTAN_ASSERT',
    'CAPSTAN_CONSOLE',
    'CAPSTAN_INTRINSICS',
]
# ######### END MACROS ##########


# ######### START OUTPUT ##########
OUTPUT_FILENAME = 'capstan'
# ######### END OUTPUT ##########
