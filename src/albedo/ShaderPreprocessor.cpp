#include "ShaderPreprocessor.h"
#include "../utils.h"
#include <fmt/core.h>
#include <iostream>
#include <regex>

namespace albedo {
ShaderPreprocessor::ShaderPreprocessor(fs::path base_path, const fs::path &name) : base_path(std::move(base_path)) {
    load_file(name.lexically_normal());
    result = out.str();
    c_result = result.c_str();
}

void ShaderPreprocessor::load_file(const fs::path &name) {
    if (std::find(stack.begin(), stack.end(), name) != stack.end()) {
        std::stringstream ss;
        ss << "#pragma include cycle: ";
        for (auto i = stack.size() - 1; i >= 0; --i) {
            if (stack[i] == name)
                ss << "[";
            ss << stack[i] << " -> ";
        }
        ss << name << "]";
        throw ShaderPreprocessException(ss.str());
    }
    stack.push_back(name);

    static std::regex include_regex(R"(^\s*#pragma\s+include\s*<\s*(\S*)\s*>\s*$)");
    int source_number = ids.insert({name, source_number_base + ids.size()}).first->second;

    fs::ifstream file(base_path / name);
    std::string line;
    int line_number = 0;
    while (getline(file, line)) {
        line_number++;
        if (line_number == 1) {
            if (line.find("#version") != std::string::npos) {
                // we have to set the line number *after* the #version, otherwise errors ensue
                out << line << "\n";
                out << "#line 1 " << source_number << " // " << name << "\n";
                continue;
            } else {
                out << "#line 0 " << source_number << " // " << name << "\n";
            }
        }

        std::smatch match;
        if (std::regex_match(line, match, include_regex)) {
            fs::path include_name(match[1].str());
            if (include_name.has_root_path() || !name.has_parent_path()) {
                include_name = include_name.relative_path();
            } else {
                include_name = name.parent_path() / include_name;
            }
            include_name = include_name.lexically_normal();
            load_file(include_name);
            out << "#line " << line_number << " " << source_number << " // " << name << "\n";
        } else {
            out << line << "\n";
        }
    }
}

std::string ShaderPreprocessor::str() const { return result; }
const GLchar *const *ShaderPreprocessor::c_str() const { return &c_result; }

std::string ShaderPreprocessor::transform_log(const std::string &source) {
    std::string transformed;
    transformed.reserve(source.length()); // avoids a few memory allocations

    std::string::size_type last_pos = 0;

    struct Replacement {
        std::string search;
        std::string replace;
        std::string::size_type next;
    };

    std::vector<Replacement> replacements;

    for (auto &[name, id] : ids) {
        std::string search_str = fmt::format("{}", id);
        replacements.push_back({search_str, name.string(), source.find(search_str)});
    }

    Replacement end_replacement = Replacement{"", "", source.size()};
    while (true) {
        Replacement *min = &end_replacement;
        for (auto &replacement : replacements) {
            if (replacement.next < last_pos && replacement.next != std::string::npos) {
                replacement.next = source.find(replacement.search, last_pos);
            }
            if (replacement.next == std::string::npos)
                continue;
            if (replacement.next < min->next)
                min = &replacement;
        }
        if (min->next == source.size()) {
            transformed += source.substr(last_pos);
            break;
        } else {
            transformed.append(source, last_pos, min->next - last_pos);
            transformed += min->replace;
            last_pos = min->next + min->search.length();
        }
    }

    return transformed;
}
} // namespace albedo