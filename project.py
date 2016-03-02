from os.path import abspath, dirname, join
import sys
from argparse import ArgumentParser

TOOLS_DIR = join(dirname(abspath(__file__)), 'tools')
# sys.path.append(join(TOOLS_DIR, 'build'))
# sys.path.append(join(TOOLS_DIR, 'settings'))
sys.path.append(TOOLS_DIR)


if __name__ == '__main__':
    from build import build
    from opengl import generate_function_declarations

    FUNCTIONS = {
        'build': build,
        'opengl': generate_function_declarations,
    }

    parser = ArgumentParser()
    parser.add_argument(
        'command',
        help='Run a project script',
        choices=FUNCTIONS.keys()
    )

    args = parser.parse_args()

    func = FUNCTIONS[args.command]
    func()
