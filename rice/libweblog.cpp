#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"
//#include "rice/Class.hpp"
#include "parser.h"

using namespace Rice;

extern "C"
void Init_LibWeblog() {
    //Class tmp_ = define_class("LibWeblog");

    Data_Type<Weblogdb> rb_cWeblogdb =
      define_class<Weblogdb>("Weblogdb")
      .define_constructor(Constructor<Weblogdb>())
      .define_constructor(Constructor<Weblogdb, std::string>())
      .define_method("setDBFile", &Weblogdb::setDbFile)
      .define_method("write", &Weblogdb::write)
      .define_method("fetch", &Weblogdb::fetch)
      .define_method("fetch_all", &Weblogdb::fetch_all)
      .define_method("createTables", &Weblogdb::createTables);

    Data_Type<Parser> rb_cParser =
      define_class<Parser>("Parser")
      .define_constructor(Constructor<Parser, Weblogdb>())
      .define_method("parseWeblog", &Parser::parseWeblog)
      .define_method("count", &Parser::count)
      .define_method("toDatabase", &Parser::toDatabase)
      .define_method("toString", &Parser::toString);

    Data_Type<Weblog> rb_cWeblog =
      define_class<Weblog>("Weblog")
      .define_constructor(Constructor<Weblog>());
}
