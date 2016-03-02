from os.path import join
from build_settings import MAIN_SOURCE_DIR, TOOLS_DIR


TEMPLATE_DIRS = [
    join(TOOLS_DIR, 'opengl', 'templates'),
]


OUTPUT_DIR = join(MAIN_SOURCE_DIR, 'generated')


# NOTE (Emil): Using a set here, as we want no duplicate entries.
FUNCTIONS = [
    'glViewport',
    'glGetError',
    'glClearColor',
    'glGetIntegerv',
    'glClear',
    'glDrawArrays',
    'glDrawElements',

    'glGenBuffers',
    'glBindBuffer',
    'glBufferData',

    'glCreateShader',
    'glDeleteShader',
    'glShaderSource',
    'glCompileShader',
    'glGetShaderiv',
    'glGetShaderInfoLog',

    'glCreateProgram',
    'glDeleteProgram',
    'glAttachShader',
    'glLinkProgram',
    'glUseProgram',
    'glGetProgramiv',
    'glGetProgramInfoLog',

    'glVertexAttribPointer',
    'glEnableVertexAttribArray',
    'glDisableVertexAttribArray',

    'glGenVertexArrays',
    'glBindVertexArray',

    'glGenTextures',
    'glBindTexture',

    'glTexParameteri',

    'glTexImage2D',
    'glGenerateMipmap',
]
