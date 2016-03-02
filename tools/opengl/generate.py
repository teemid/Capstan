from os.path import join

from jinja2 import Environment, FileSystemLoader

from settings.opengl import (
    FUNCTIONS,
    OUTPUT_DIR,
    TEMPLATE_DIRS
)


loader = FileSystemLoader(TEMPLATE_DIRS)
jinja = Environment(loader=loader)


def render_template(template_name, context, output_filename=None):
    template = jinja.get_template(template_name)
    output_file = join(OUTPUT_DIR, output_filename or template_name)

    with open(output_file, 'w') as f:
        rendered_template = template.render(context)
        f.write(rendered_template)


def generate_function_declarations():
    templates = {
        'declaration': 'FunctionDeclarations.inl',
        'load': 'LoadFunctions.inl'
    }

    context = {
        'opengl_functions': FUNCTIONS,
        'length': len(max(FUNCTIONS, key=len))
    }

    render_template(templates['declaration'], context)
    context['extern'] = True
    render_template(
        templates['declaration'],
        context,
        'Extern' + templates['declaration'],
    )
    render_template(templates['load'], context)
