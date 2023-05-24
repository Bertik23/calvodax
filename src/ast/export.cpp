#include "export.h"

#include <filesystem>
#include <fstream>

#include "../utils/exceptions.h"

Export::Export(const std::string & str): file(str) {}

Export::~Export() = default;

std::shared_ptr<Rational> Export::eval(Context & cntx) const {
    try {
        std::filesystem::path f(file+".cldx");
        if (std::filesystem::is_directory(f))
            throw text_error("Can't write to path.");
        std::filesystem::create_directories(f.parent_path());
        std::ofstream of(f);
        for (auto & var : cntx.variable_map){
            if (var.second.get() == nullptr) continue;
            of << var.first << " = " << *var.second << "\n";
        }
        if (!of) throw text_error("Couldn't write to path");
        std::cout << "Succesfully exported to: " << f << std::endl;
        return std::shared_ptr<Rational>(new Rational(0));
    } catch(std::filesystem::filesystem_error & e){
        throw text_error("Can't write to path. " + std::string(e.what()));
    }
}

void Export::print(std::ostream & os) const {
    os << "Export " << file;
}

Export * Export::clone() const {
    return new Export(*this);
}
