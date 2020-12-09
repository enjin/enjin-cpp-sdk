from .TemplateType import TemplateType
from typing import List


class Template(object):

    _namespace_key = '#namespace'
    _import_key = '#import'
    _arg_key = '#arg'

    def __init__(self, namespace: str, template_type: TemplateType, contents: List[str], fragments: dict):
        parts = namespace.split('.')
        self.namespace = namespace
        self.name = parts[len(parts) - 1]
        self.template_type = template_type
        self._fragments = fragments
        self._contents = list()
        self._parameters = list()
        self._referenced_fragments = list()
        self._parse_contents(contents)

    def compile(self) -> str:
        builder = '\n'.join(self._contents)

        if self.template_type == TemplateType.FRAGMENT:
            return builder

        parameters = list(self._parameters)
        processed_fragments = list()
        fragment_stack = list()

        for reference in self._referenced_fragments:
            fragment_stack.append(self._fragments[reference])

        while len(fragment_stack) != 0:
            fragment = fragment_stack.pop()
            if fragment.namespace in processed_fragments:
                continue

            for reference in fragment._referenced_fragments:
                fragment_stack.append(self._fragments[reference])

            parameters += list(filter(lambda p: p not in parameters, fragment._parameters))
            builder += fragment.compile() + '\n'
            processed_fragments.append(fragment.namespace)

        replace_term = self.template_type.name.lower()
        formatted_params = ', '.join(parameters)
        return builder.replace(replace_term, '%s %s(%s)' % (replace_term, self.name, formatted_params))

    def _parse_contents(self, contents: List[str]) -> None:
        for line in contents:
            trimmed = line.strip()
            if trimmed.startswith(Template._import_key):
                self._referenced_fragments.append(Template._process_import(trimmed))
            elif trimmed.startswith(Template._arg_key):
                self._parameters.append(Template._process_arg(trimmed))
            elif not len(trimmed) == 0 and not trimmed.startswith('#'):
                self._contents.append(trimmed)

    @staticmethod
    def read_namespace(contents: List[str]):
        for line in contents:
            if line.startswith(Template._namespace_key):
                return line.split(' ')[1].strip()

        return None

    @staticmethod
    def _process_arg(line: str) -> str:
        parts = line.split(' ')
        if len(parts) == 3:
            return '$%s: %s' % (parts[1], parts[2])
        elif len(parts) == 4:
            return '$%s: %s = %s' % (parts[1], parts[2], parts[3])
        else:
            raise ValueError('Argument "line" in "_process_arg()" is of incorrect format')

    @staticmethod
    def _process_import(line: str) -> str:
        return line.split(' ')[1]
