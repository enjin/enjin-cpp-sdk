add_executable(template_generator
        TemplateGenerator.cpp
        Template.cpp
        Template.hpp
        TemplateLoader.cpp
        TemplateLoader.hpp
        TemplateType.cpp
        TemplateType.hpp)

target_link_libraries(template_generator ${PROJECT_NAME}_utils)
