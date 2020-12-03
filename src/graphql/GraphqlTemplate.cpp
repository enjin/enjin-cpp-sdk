#include "GraphqlTemplate.hpp"

#include "EnumUtils.hpp"
#include "StringUtils.hpp"
#include <sstream>
#include <vector>

using namespace enjin::sdk::graphql;

std::string process_arg(std::string &line) {
    std::vector<std::string> parts = enjin::sdk::utils::split(line, " ");
    std::stringstream fmt;

    switch (parts.size()) {
        case 3:
            fmt << parts[1] << ": " << parts[2];
            return fmt.str();
        case 4:
            fmt << parts[1] << ": " << parts[2] << " = " << parts[3];
            return fmt.str();
        default:
            return nullptr;
    }
}

std::string process_import(std::string &line) {
    return enjin::sdk::utils::split(line, " ")[1];
}

GraphqlTemplate::GraphqlTemplate() = default;

GraphqlTemplate::GraphqlTemplate(const std::string &name,
                                 TemplateType template_type,
                                 const std::list<std::string> &contents,
                                 std::map<std::string, GraphqlTemplate> fragments) {
    std::vector<std::string> parts = enjin::sdk::utils::split(name, ".");
    this->template_namespace = name;
    this->name = parts[parts.size() - 1];
    this->template_type = template_type;
    this->contents = parse_contents(contents);
    this->fragments = fragments;
}

GraphqlTemplate::~GraphqlTemplate() = default;

void GraphqlTemplate::compile() {
    if (this->template_type == TemplateType::FRAGMENT) {
        return;
    }

    std::list<std::string> parameters = std::list<std::string>(this->parameters);
    std::list<std::string> processed_fragments = std::list<std::string>();
    std::list<GraphqlTemplate> fragment_queue = std::list<GraphqlTemplate>();
    std::stringstream builder;
    builder << this->contents << "\n";

    for (const std::string &fragment : this->referenced_fragments) {
        fragment_queue.push_back(this->fragments[fragment]);
    }

    while (!fragment_queue.empty()) {
        GraphqlTemplate fragment_template = fragment_queue.front();
        fragment_queue.pop_front();

        auto begin = processed_fragments.begin();
        auto end = processed_fragments.end();
        auto iter = find(begin, end, fragment_template.get_namespace());
        if (iter != end) {
            continue;
        }

        for (const std::string &fragment : fragment_template.get_referenced_fragments()) {
            fragment_queue.push_back(this->fragments[fragment]);
        }

        for (const std::string &parameter : fragment_template.get_parameters()) {
            auto begin = this->parameters.begin();
            auto end = this->parameters.end();
            auto iter = find(begin, end, parameter);
            if (iter != end) {
                this->parameters.push_back(parameter);
            }
        }

        builder << fragment_template.contents << "\n";
        processed_fragments.push_back(fragment_template.get_namespace());
    }

    std::string replace_term = enjin::sdk::utils::to_lower(enjin::sdk::utils::get_name(this->template_type));
    std::string formatted_params = enjin::sdk::utils::join(", ", parameters);
    std::stringstream newValueStream;
    newValueStream << replace_term << " " << this->name << "(" << formatted_params << ")";
    this->compiled_contents = enjin::sdk::utils::replace(builder.str(), replace_term, newValueStream.str());
}

std::string GraphqlTemplate::get_namespace() {
    return this->template_namespace;
}

std::string GraphqlTemplate::get_name() {
    return this->name;
}

TemplateType GraphqlTemplate::get_template_type() {
    return this->template_type;
}

std::string GraphqlTemplate::get_contents() {
    return this->contents;
}

std::string GraphqlTemplate::get_compiled_contents() {
    return this->compiled_contents;
}

std::list<std::string> GraphqlTemplate::get_parameters() {
    return this->parameters;
}

std::list<std::string> GraphqlTemplate::get_referenced_fragments() {
    return this->referenced_fragments;
}

std::string GraphqlTemplate::parse_contents(const std::list<std::string> &contents) {
    std::stringstream stream;
    for (const std::string &line : contents) {
        std::string trimmed = enjin::sdk::utils::trim(line);

        // Checks which key the line starts with
        if (trimmed.find(arg_key) == 0) {
            this->parameters.push_back(process_arg(trimmed));
        } else if (trimmed.find(import_key) == 0) {
            referenced_fragments.push_back(process_import(trimmed));
        } else if (!enjin::sdk::utils::is_empty_or_whitespace(trimmed) && trimmed.find('#') != std::string::npos) {
            stream << line << "\n";
        }
    }

    return stream.str();
}

std::string GraphqlTemplate::read_namespace(const std::list<std::string> &contents) {
    for (const std::string &line : contents) {
        if (line.find(namespace_key) != std::string::npos) {
            return enjin::sdk::utils::split(line, " ")[1];
        }
    }

    return std::string ();
}
