#ifndef JUCI_PROJECT_BUILD_H_
#define JUCI_PROJECT_BUILD_H_

#include <boost/filesystem.hpp>
#include "cmake.h"

namespace Project {
  class Build {
  public:
    Build() {}
    virtual ~Build() {}
    
    boost::filesystem::path project_path;
    
    boost::filesystem::path get_default_path();
    virtual bool update_default(bool force=false) {return false;}
    boost::filesystem::path get_debug_path();
    virtual bool update_debug(bool force=false) {return false;}
    
    virtual boost::filesystem::path get_executable(const boost::filesystem::path &path) {return boost::filesystem::path();}
    
    static std::unique_ptr<Build> create(const boost::filesystem::path &path);
  };
  
  class CMakeBuild : public Build {
    ::CMake cmake;
  public:
    CMakeBuild(const boost::filesystem::path &path);
    
    bool update_default(bool force=false) override;
    bool update_debug(bool force=false) override;
    
    boost::filesystem::path get_executable(const boost::filesystem::path &path) override;
  };
}

#endif // JUCI_PROJECT_BUILD_H_
