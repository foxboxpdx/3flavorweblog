#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"

using namespace Rice;
using namespace LibWeblog;

extern "C"
void Init_Weblog() {
    Data_Type<Weblog> rb_cWeblogdb =
      define_class<Weblog>("Weblogdb")
      .define_constructor(Constructor<Weblogdb>())
      .define_method("setDBFile", &Weblogdb::setDbFile)
      .define_method("write", &Weblogdb::write)
      .define_method("fetch", &Weblogdb::fetch)
      .define_method("fetch_all", &Weblogdb::fetch_all)
      .define_method("createTables", &Weblogdb::createTables);
}

void Init_Parser() {
    Data_Type<Parser> rb_cParser =
      define_class<Parser>("Parser")
      .define_constructor(Constructor<Parser>())
      .define_method("parseWeblog", &Parser::parseWeblog)
      .define_method("count", &Parser::count)
      .define_method("toDatabase", &Parser::toDatabase)
      .define_method("toString", &Parser::toString);
}

Struct rb_cWeblog = define_struct()
    .define_member("ip_addr")
    .define_member("date")
    .define_member("request")
    .define_member("code")
    .define_member("size")
    .define_member("referer")
    .define_member("agent")
    .initialize("Weblog");
Struct::Instance weblog_instance(rb_cWeblog.new_instance());

