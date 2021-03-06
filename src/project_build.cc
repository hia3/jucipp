#include "project_build.h"
#include "config.h"

std::unique_ptr<Project::Build> Project::Build::create(const boost::filesystem::path &path) {
  std::unique_ptr<Project::Build> cmake(new CMakeBuild(path));
  if(!cmake->project_path.empty())
    return cmake;
  else
    return std::unique_ptr<Project::Build>(new Project::Build());
}

boost::filesystem::path Project::Build::get_default_path() {
  if(project_path.empty())
    return boost::filesystem::path();
    
  boost::filesystem::path default_build_path=Config::get().project.default_build_path;
  
  const std::string path_variable_project_directory_name="<project_directory_name>";
  size_t pos=0;
  auto default_build_path_string=default_build_path.string();
  auto path_filename_string=project_path.filename().string();
  while((pos=default_build_path_string.find(path_variable_project_directory_name, pos))!=std::string::npos) {
    default_build_path_string.replace(pos, path_variable_project_directory_name.size(), path_filename_string);
    pos+=path_filename_string.size();
  }
  if(pos!=0)
    default_build_path=default_build_path_string;
  
  if(default_build_path.is_relative())
    default_build_path=project_path/default_build_path;
  
  return default_build_path;
}

boost::filesystem::path Project::Build::get_debug_path() {
  if(project_path.empty())
    return boost::filesystem::path();
  
  boost::filesystem::path debug_build_path=Config::get().project.debug_build_path;
  
  const std::string path_variable_project_directory_name="<project_directory_name>";
  size_t pos=0;
  auto debug_build_path_string=debug_build_path.string();
  auto path_filename_string=project_path.filename().string();
  while((pos=debug_build_path_string.find(path_variable_project_directory_name, pos))!=std::string::npos) {
    debug_build_path_string.replace(pos, path_variable_project_directory_name.size(), path_filename_string);
    pos+=path_filename_string.size();
  }
  if(pos!=0)
    debug_build_path=debug_build_path_string;
  
  const std::string path_variable_default_build_path="<default_build_path>";
  pos=0;
  debug_build_path_string=debug_build_path.string();
  auto default_build_path=Config::get().project.default_build_path;
  while((pos=debug_build_path_string.find(path_variable_default_build_path, pos))!=std::string::npos) {
    debug_build_path_string.replace(pos, path_variable_default_build_path.size(), default_build_path);
    pos+=default_build_path.size();
  }
  if(pos!=0)
    debug_build_path=debug_build_path_string;
  
  if(debug_build_path.is_relative())
    debug_build_path=project_path/debug_build_path;
  
  return debug_build_path;
}

Project::CMakeBuild::CMakeBuild(const boost::filesystem::path &path) : Project::Build(), cmake(path) {
  project_path=cmake.project_path;
}

bool Project::CMakeBuild::update_default(bool force) {
  return cmake.update_default_build(get_default_path(), force);
}

bool Project::CMakeBuild::update_debug(bool force) {
  return cmake.update_debug_build(get_debug_path(), force);
}

boost::filesystem::path Project::CMakeBuild::get_executable(const boost::filesystem::path &path) {
  return cmake.get_executable(path);
}
