{% for function in opengl_functions -%}
    GetFunction(PFN{{ function | upper }}PROC, {{ function.rjust(length) }});
{% endfor %}
