#include "virtual_storage.h"

virtual_storage::virtual_storage()
{
}

//    this->c.client = k;

bool virtual_storage::load(){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    std::cout << "add(2, 3) = ";
    bool load = c.call("load").as<bool>();
    std::cout<< load;
    return load;
    //            std::cout << five << std::endl;

}
bool virtual_storage::updateService(const Service &Service){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    bool load = c.call("updateService", Service).as<bool>();
    return load;
}
 int virtual_storage::insertService(const Service &Service){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    bool load = c.call("insertService", Service).as<int>();
    return load;
}
  bool virtual_storage::removeService(int Service_id){
     client c("localhost", rpc::constants::DEFAULT_PORT);

     bool load = c.call("removeService", Service_id).as<bool>();
     return load;
     //            std::cout << five << std::endl;

 }
bool virtual_storage::save(){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    bool load = c.call("save").as<bool>();
    return load;
    //            std::cout << five << std::endl;

}

vector<Service> virtual_storage::getAllServices(void){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("getAllServices").as<vector<Service>>();
}

vector<Account> virtual_storage::getAllAccounts(void){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("getAllAccounts").as<vector<Account>>();
}
Account virtual_storage::getAccountById(int  Account_id){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("getAccountById",Account_id).as<Account>();
}
Template virtual_storage::getTemplateById(int Account_id){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("getTemplateById", Account_id).as<Template>();
}
bool virtual_storage::updateAccount(const Account &Account){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("updateAccount", Account ).as<bool>();
}
bool virtual_storage::removeAccount(int Account_id){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("removeAccount", Account_id).as<bool>();
}
int virtual_storage::insertAccount(const Account &Account){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("insertAccount", Account).as<int>();
}
User virtual_storage::Sql_getUser(string login, string password){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("Sql_getUser", login, password).as<User>();
}
vector<Service> virtual_storage::Sql_getAllServicesByUser(int user_id){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("Sql_getAllServicesByUser", user_id).as<vector<Service>>();
}
vector<Account> virtual_storage::Sql_getAllAccountsByService(int user_id){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("Sql_getAllAccountsByService", user_id).as<vector<Account>>();
}
vector<Template> virtual_storage::Sql_getAllTemplatesByUser(int user_id){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("Sql_getAllTemplatesByUser", user_id).as<vector<Template>>();
}
vector<Account> virtual_storage::Sql_getAllAccountsFreeFromService(int user_id){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("Sql_getAllAccountsFreeFromService", user_id).as<vector<Account>>();
}
int virtual_storage::Sql_insertServiceToUser(int user_id,  const Service &Service){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("Sql_insertServiceToUser", user_id, Service).as<int>();
}
bool virtual_storage::Sql_connectAccountToService(int service_id, int account_id){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("Sql_connectAccountToService", service_id, account_id).as<bool>();
}
bool virtual_storage::Sql_deleteAccountFromService(int service_id, int account_id){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("Sql_deleteAccountFromService", service_id, account_id).as<bool>();
}
int virtual_storage::Sql_insertTemplate(int user_id, const Template &Template){
    client c("localhost", rpc::constants::DEFAULT_PORT);
    return c.call("Sql_insertTemplate", user_id, Template).as<int>();
}
int virtual_storage::Sql_insertUser(User user){
    client c("localhost", rpc::constants::DEFAULT_PORT);
    return c.call("Sql_insertUser", user).as<int>();
}
int virtual_storage::Sql_removeTemplate(int templ_id, int user_id){
    client c("localhost", rpc::constants::DEFAULT_PORT);
    return c.call("Sql_removeTemplate", templ_id, user_id).as<int>();
}
Account virtual_storage::Sql_getAccountByService(int service_id){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("Sql_getAccountByService", service_id).as<Account>();
}
int virtual_storage::Sql_checkUser(string username){
    client c("localhost", rpc::constants::DEFAULT_PORT);

    return c.call("Sql_checkUser", username).as<int>();
}
vector<Service>  virtual_storage::Sql_getAllServicesByUserOffset(int user_id, int offset, int limit ){
    client c("localhost", rpc::constants::DEFAULT_PORT);
    return c.call("Sql_getAllServicesByUserOffset", user_id, offset, limit).as<vector<Service>>();
}
int virtual_storage::Sql_getServicesNumber(int user_id){
    client c("localhost", rpc::constants::DEFAULT_PORT);
    return c.call("Sql_getServicesNumber", user_id ).as<int>();
}
vector<Service>  virtual_storage::Sql_getAllServicesByUserOffsetSearch(int user_id, int offset, int limit, string str ){
    client c("localhost", rpc::constants::DEFAULT_PORT);
    return c.call("Sql_getAllServicesByUserOffsetSearch", user_id, offset, limit, str).as<vector<Service>>();
}
int  virtual_storage::Sql_getServicesNumberSearch(int user_id, string str){
    client c("localhost", rpc::constants::DEFAULT_PORT);
    return c.call("Sql_getServicesNumberSearch", user_id, str ).as<int>();
}


