#ifndef JUCI_NOTEBOOK_H_
#define JUCI_NOTEBOOK_H_

#include <iostream>
#include "gtkmm.h"
#include "source.h"
#include "source_clang.h"
#include <type_traits>
#include <map>
#include <sigc++/sigc++.h>

class Notebook : public Gtk::Notebook {
  class TabLabel : public Gtk::Box {
  public:
    TabLabel(const boost::filesystem::path &path);
    Gtk::Label label;
    Gtk::Button button;
  };
  
private:
  Notebook();
public:
  static Notebook &get() {
    static Notebook singleton;
    return singleton;
  }
  
  Source::View* get_view(int page);
  size_t get_index(int page);
  int size();
  Source::View* get_current_view();
  bool close(int page);
  bool close_current_page();
  void open(const boost::filesystem::path &file_path);
  bool save(int page);
  bool save_current();
  void configure(int view_nr);
  boost::filesystem::path get_current_folder();

  std::vector<Source::View*> source_views; //Is NOT freed in destructor, this is intended for quick program exit.

  Gtk::Label info;
  Gtk::Label status;
private:
  bool save_modified_dialog(int page);
  std::vector<std::unique_ptr<Gtk::Widget> > source_maps;
  std::vector<std::unique_ptr<Gtk::ScrolledWindow> > scrolled_windows;
  std::vector<std::unique_ptr<Gtk::HBox> > hboxes;
  std::vector<std::unique_ptr<TabLabel> > tab_labels;
  
  size_t last_index;
};
#endif  // JUCI_NOTEBOOK_H_
