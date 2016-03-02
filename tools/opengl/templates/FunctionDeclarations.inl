{% for function in opengl_functions -%}
    {% if extern %}extern {% endif %}PFN{{ function | upper }}PROC {{ function.rjust(length) }};
{% endfor %}
