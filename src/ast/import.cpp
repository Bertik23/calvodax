#include "import.h"

#include <filesystem>
#include <fstream>

#include "../utils/exceptions.h"
#include "../parser/parser.h"

Import::Import(const std::string & str): file(str) {}

Import::~Import() = default;

std::shared_ptr<Rational> Import::eval(Context & cntx) const {
    try {
        std::filesystem::path f(file+".cldx");
        //if (std::filesystem::is_regular_file(f))
            //throw text_error("Can't read from path.");
        std::ifstream ifile(f);
        if (!ifile.is_open())
            throw text_error("Couldn't open file " + f.string());
        std::string line;
        try {
            while (ifile){
                std::getline(ifile, line);
                if (line == "") continue;
                auto tokens = tokenize(line);
                parse(tokens)->eval(cntx);
            }
        } catch(text_error & e) {
            throw text_error("Invalid save file. " + std::string(e.what()));
        }
        if (ifile.bad()) throw text_error("Couldn't read from path");
        std::cout << "Succesfully imported from: " << f << std::endl;
        return std::shared_ptr<Rational>(new Rational(0));
    } catch(std::filesystem::filesystem_error & e){
        throw text_error("Can't write to path. " + std::string(e.what()));
    }
}

void Import::print(std::ostream & os) const {
    os << "Import " << file;
}

Import * Import::clone() const {
    return new Import(*this);
}
