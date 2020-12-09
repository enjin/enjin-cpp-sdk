from .TemplateLoader import TemplateLoader
from os import getcwd
from typing import List, Tuple


def generate() -> List[Tuple[str, str]]:
    resource_dir = getcwd()
    template_loader = TemplateLoader(resource_dir)
    template_loader.load()

    templates = list()
    for template in template_loader.operations.values():
        k = template.namespace
        v = template.compile().replace('\n', ' ')
        templates.append((k, v))

    return templates
