#ifndef VIRTUAL_STORAGE_H
#define VIRTUAL_STORAGE_H
//#include "rpc/rpc_error.h"
#include "rpc/client.h"
#include <iostream>
#include <service.h>
#include<account.h>
#include <template.h>
#include "user.h"

using namespace rpc;
class virtual_storage
{

public:
    bool load();
    bool save();
    virtual_storage();
    vector<Service> getAllServices(void);
    Service getServiceById(int Service_id);
    bool updateService(const Service &Service);
    bool removeService(int Service_id);
    int insertService(const Service &Service);
    // Accounts
    vector<Account> getAllAccounts(void);
     Account getAccountById(int Account_id);
    Template getTemplateById(int Account_id);
    bool updateAccount(const Account &Account);
    bool removeAccount(int Account_id);
    int insertAccount(const Account &Account);
    User Sql_getUser(string login, string password);
    vector<Service> Sql_getAllServicesByUser(int user_id );
    vector<Account> Sql_getAllAccountsByService(int user_id );
    vector<Template> Sql_getAllTemplatesByUser(int user_id );

    vector<Account> Sql_getAllAccountsFreeFromService(int user_id );
    int Sql_insertServiceToUser(int user_id,  struct Service &Service );
    bool Sql_connectAccountToService(int service_id, int account_id );
    bool Sql_deleteAccountFromService(int service_id, int account_id );
    int Sql_insertServiceToUser(int user_id, const Service &Service );
    Account Sql_getAccountByService(int service_id);
    int Sql_insertTemplate(int user_id, const Template &Template);
    int Sql_insertUser(User user);
    int Sql_removeTemplate(int templ_id, int user_id);
    int Sql_checkUser(string username);
    int Sql_getServicesNumber(int user_id);
    vector<Service>  Sql_getAllServicesByUserOffset(int user_id, int offset, int limit );
    vector<Service> Sql_getAllServicesByUserOffsetSearch(int user_id, int offset, int limit, string str );
    int Sql_getServicesNumberSearch(int user_id, string str);


private:
};

//};

#endif // VIRTUAL_STORAGE_H
