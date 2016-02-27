from .common import *


LIBS = [
    'user32.lib',
    'opengl32.lib',
    'gdi32.lib',
    'XInput.lib',
]

MACROS += ['CAPSTAN_WIN32', ]

MACRO_DEFINITIONS = ['/D' + macro for macro in MACROS]


COMPILER = {
    'NAME': 'cl',
    # COMPILER OPTIONS
    # /Od    - Disable optimizations
    # /I     - Include directories
    # /c     - Compiles without linking
    # /Fe    - Renames executable file
    # /MT(d) - Creates a multithreaded executable file using LIBCMT.lib
    # /WX    - Treat warnings like errors
    # /wdn   - Disable warning [n]
    # /Wn    - Specify warning level n=[0..4], /Wall=/W4
    # /Zi    - Produces a program database (PDB) with debugging information
    # /MP[n] - Use multiple process to compile the code
    #          with maximum n process
    'FLAGS': [
        '/nologo',
        '/MP',
        '/Od',
        '/I', INCLUDE_DIR,
        '/c',
        '/MTd',
        '/WX',
        '/W3',
        '/wd4996',
        '/Zi',
    ],
}

LINKER = {
    'NAME': 'link',
    # LINKER OPTIONS
    # /PDB    - Creates program database (PDB) debugging information
    # /WX     - Treat linker warnings as errors
    'FLAGS': [
        '/DEBUG',
        '/NOLOGO',
    ]
}
