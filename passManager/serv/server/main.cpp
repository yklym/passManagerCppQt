#include <QCoreApplication>
#include <rpc/server.h>
#include "rpc/this_handler.h"
#include "account.h"
#include "service.h"
#include "sqlite_storage.h"
#include "template.h"
#include "user.h"
#include "optional.h"
SqliteStorage * stor= new SqliteStorage("./../../../data/");


double divide(double a, double b) {
    if (b == 0.0) {
        rpc::this_handler().respond_error(std::make_tuple(1, "Division by zero"));
    }
    return a / b;
}


bool save(){
    return stor->save();
}
vector<Service> getAllServices(){
    return stor->getAllServices();
}
Service getServiceById(int Service_id){
    optional<Service> buf=stor->getServiceById(Service_id).value();
    if(!buf){
        Service serv;
        serv.id = -1;
        return serv;
    }
    return buf.value();
}
bool updateService(const Service &Service){
    return stor->updateService(Service);
}

bool load(){
    return stor->load();
}
bool removeService(int Service_id){
    return stor->removeService(Service_id);
}
int insertService(const Service &Service){
    return  stor->insertService(Service);
}
vector<Account> getAllAccounts(void){
    return stor->getAllAccounts();
}
Account getAccountById(int Account_id){

    optional<Account> buf=stor->getAccountById(Account_id).value();
    if(!buf){
        Account serv;
        serv.id = -1;
        return serv;
    }
    return buf.value();
}
Template getTemplateById(int Account_id){
    optional<Template> buf=stor->getTemplateById(Account_id);
    if(!buf){
        Template serv;
        serv.id = -1;
        return serv;
    }
    return buf.value();
}
bool updateAccount(const Account &Account){
    return stor->updateAccount(Account);
}
bool removeAccount(int Account_id){
    return stor->removeAccount(Account_id);
}
int insertAccount(const Account & Account){
    return stor->insertAccount(Account);
}
User getUser(string login, string password){
    optional<User> buf=stor->Sql_getUser(login, password);
    if(!buf){
        User serv;
        serv.id = -1;
        return serv;
    }
    return buf.value();
}
vector<Service> getAllServicesByUser(int user_id ){
    return stor->Sql_getAllServicesByUser(user_id);
}
vector<Account> getAllAccountsByService(int user_id ){
    return stor->Sql_getAllAccountsByService(user_id);
}
vector<Template> getAllTemplatesByUser(int user_id ){
    return stor->Sql_getAllTemplatesByUser(user_id);
}
vector<Account> getAllAccountsFreeFromService(int user_id ){
    return stor->Sql_getAllAccountsFreeFromService(user_id);
}
//int insertServiceToUser(int user_id,  struct Service &Service1 ){
//    return stor->Sql_insertServiceToUser(user_id, Service1);
//}
bool connectAccountToService(int service_id, int account_id ){
    return stor->Sql_connectAccountToService(service_id, account_id);
}
bool deleteAccountFromService(int service_id, int account_id ){
    return stor->Sql_deleteAccountFromService(service_id, account_id);
}
int insertServiceToUser(int user_id, const Service &Service ){
    return stor->Sql_insertServiceToUser(user_id, Service);
}
Account getAccountByService(int service_id){
    return stor->Sql_getAccountByService(service_id);
}
int insertTemplate(int user_id, const Template &Template){
    return stor->Sql_insertTemplate(user_id, Template);
}
int Sql_insertUser(User user){
    return stor->Sql_insertUser(user);
}
int Sql_removeTemplate(int templ_id, int user_id){
    return stor->Sql_removeTemplate(templ_id,user_id);

}
int Sql_checkUser(string username){
    return stor->Sql_checkUser(username);
}
int Sql_getServicesNumber(int user_id){
    return stor->Sql_getServicesNumber(user_id);
}
vector<Service>  Sql_getAllServicesByUserOffset(int user_id, int offset, int limit ){
    return stor->Sql_getAllServicesByUserOffset(user_id, offset, limit);
}
vector<Service> Sql_getAllServicesByUserOffsetSearch(int user_id, int offset, int limit, string str ){
    return stor->Sql_getAllServicesByUserOffsetSearch(user_id, offset, limit, str);
}
int  Sql_getServicesNumberSearch(int user_id, string str){
    return stor->Sql_getServicesNumberSearch(user_id, str);
}

int main(int argc, char *argv[])
{


    QCoreApplication a(argc, argv);
    rpc::server srv(rpc::constants::DEFAULT_PORT);

    // It's possible to bind non-capturing lambdas
    // ... arbitrary callables
    // ... free functions
    srv.bind("div", &divide);
    // ... member functions with captured instances in lambdas



    srv.bind("load", &load);
    srv.bind("save", &save);
    srv.bind("getAllServices", &getAllServices);
    srv.bind("getServiceById", &getServiceById);
    srv.bind("updateService", &updateService);
    srv.bind("removeService", &removeService);
    srv.bind("insertService", &insertService);
    srv.bind("getAllAccounts", &getAllAccounts);
    srv.bind("getAccountById", &getAccountById);
    srv.bind("getTemplateById", &getTemplateById);
    srv.bind("updateAccount", &updateAccount);
    srv.bind("removeAccount", &removeAccount);
    srv.bind("insertAccount", &insertAccount);
    srv.bind("Sql_getUser", &getUser);
    srv.bind("Sql_getAllServicesByUser", &getAllServicesByUser);
    srv.bind("Sql_getAllAccountsByService", &getAllAccountsByService);
    srv.bind("Sql_getAllTemplatesByUser", &getAllTemplatesByUser);
    srv.bind("Sql_getAllAccountsFreeFromService", &getAllAccountsFreeFromService);
    srv.bind("Sql_insertServiceToUser", &insertServiceToUser);
    srv.bind("Sql_connectAccountToService", &connectAccountToService);
    srv.bind("Sql_deleteAccountFromService", &deleteAccountFromService);
    //    srv.bind("Sql_insertServiceToUser", &Sql_insertServiceToUser);
    srv.bind("Sql_getAccountByService", &getAccountByService);
    srv.bind("Sql_insertTemplate", &insertTemplate);
    srv.bind("Sql_insertUser", &Sql_insertUser);
    srv.bind("Sql_removeTemplate", &Sql_removeTemplate);
    srv.bind("Sql_checkUser", &Sql_checkUser);
    srv.bind("Sql_getServicesNumber", &Sql_getServicesNumber);
    srv.bind("Sql_getAllServicesByUserOffset", &Sql_getAllServicesByUserOffset);
    srv.bind("Sql_getAllServicesByUserOffsetSearch", &Sql_getAllServicesByUserOffsetSearch);
    srv.bind("Sql_getServicesNumberSearch", &Sql_getServicesNumberSearch);


    srv.run();
    return a.exec();
}



