import os
from subprocess import run
import pathlib

from .settings.windows import (
    BUILD_DIR,
    COMPILER,
    LIBS,
    LINKER,
    MACRO_DEFINITIONS,
    OUTPUT_FILENAME,
    SOURCE_DIR,
)


class WorkDirectory(object):
    def __init__(self, new_work_dir):
        self.new_work_dir = new_work_dir
        self.cwd = os.getcwd()

    def __enter__(self):
        os.chdir(self.new_work_dir)

    def __exit__(self, type, value, traceback):
        os.chdir(self.cwd)


def create_build_dir():
    if not os.path.isdir(BUILD_DIR):
        os.mkdir(BUILD_DIR)


def compile_file(file):
    cmd = [COMPILER.get('NAME', 'cl')]
    cmd += COMPILER.get('FLAGS', [])
    cmd.append(os.path.abspath(file.__str__()))
    cmd += MACRO_DEFINITIONS

    return cmd


def link():
    cmd = [LINKER.get('NAME', 'link')]
    cmd += LINKER.get('FLAGS', [])
    cmd += [
        '/OUT:{0}.exe'.format(OUTPUT_FILENAME),
        '*.obj'
    ]
    cmd += LIBS

    return cmd


def compile():
    source_dir = pathlib.Path(SOURCE_DIR)
    source_files = list(source_dir.glob('**/*.cpp'))

    with WorkDirectory(BUILD_DIR):
        for file in source_files:
            run(compile_file(file))

        run(link())
