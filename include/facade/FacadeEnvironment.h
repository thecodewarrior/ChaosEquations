#ifndef CHAOSEQUATIONS_FACADEENVIRONMENT_H
#define CHAOSEQUATIONS_FACADEENVIRONMENT_H

#include <boost/filesystem.hpp>

namespace facade {

namespace fs = boost::filesystem;

class FacadeEnvironment {
public:
    static fs::path resources_dir;
};

} // namespace facade

#endif // CHAOSEQUATIONS_FACADEENVIRONMENT_H
