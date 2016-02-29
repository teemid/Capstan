from os.path import join
from .common import PROJECT_DIR


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


OUTPUT_DIR = join(PROJECT_DIR, 'generated')
