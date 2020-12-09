from .Template import Template
from .TemplateType import TemplateType
from os import listdir, path
import re


class TemplateLoader:
    _TEMPLATE_REGEX = re.compile(
        '^(?:[a-zA-Z\\\\:-]*schemas\\\\)'
        '(?:project|player|shared)\\\\'
        '(?P<type>fragment|query|mutation)\\\\'
        '(?:[a-zA-Z]+)\\.gql$'
    )

    def __init__(self, resource_dir):
        self.operations = dict()
        self._fragments = dict()
        self._resource_dir_path = resource_dir

    def load(self) -> None:
        self._load_raw_resources()

    def _load_raw_resources(self) -> None:
        if self._resource_dir_path is None or path.exists(self._resource_dir_path):
            pass

        path_stack = list()
        path_stack.append(self._resource_dir_path)

        while len(path_stack) > 0:
            resource_path = path_stack.pop()

            if path.isdir(resource_path):
                files = listdir(resource_path)
                if len(files) > 0:
                    path_stack += ['%s\\%s' % (resource_path, f) for f in files]
            else:
                matcher = re.match(TemplateLoader._TEMPLATE_REGEX, path.abspath(resource_path))
                if matcher is None:
                    continue

                group_type = matcher.groupdict()['type']
                for template_type in TemplateType:
                    if template_type.name.lower() == group_type.lower():
                        self._load_and_cache_template_contents(resource_path, template_type)
                        break

    def _load_and_cache_template_contents(self, file_path: str, template_type: TemplateType) -> None:
        with open(file_path, 'r') as f:
            contents = f.readlines()

        if contents is None:
            return None

        namespace = Template.read_namespace(contents)
        if namespace is None:
            return None

        if template_type == TemplateType.FRAGMENT:
            self._fragments[namespace] = Template(namespace, template_type, contents, self._fragments)
        elif template_type == TemplateType.MUTATION or template_type == TemplateType.QUERY:
            self.operations[namespace] = Template(namespace, template_type, contents, self._fragments)
        else:
            raise ValueError('Unknown template type: %s' % template_type)
