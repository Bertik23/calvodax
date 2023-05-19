#include <exception>
#include <string>

class text_error: public std::exception{
public:
    text_error(const std::string &);
    const char * what() const noexcept override;
private:
    std::string message;
};

class syntax_error: public text_error{
    using text_error::text_error;
};