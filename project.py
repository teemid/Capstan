import os
import sys
from argparse import ArgumentParser

MANAGE = os.path.dirname(os.path.abspath(__file__))
sys.path.append(os.path.join(MANAGE, 'scripts'))
sys.path.append(os.path.join(MANAGE, 'settings'))


if __name__ == '__main__':
    from scripts.compile import compile
    from scripts.opengl import generate_function_declarations

    FUNCTIONS = {
        'compile': compile,
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
