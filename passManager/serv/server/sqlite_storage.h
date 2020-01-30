 #ifndef SQLITE_STORAGE_H
#define SQLITE_STORAGE_H
#include <QCryptographicHash>


#include <vector>
#include <string>

#include "optional.h"
#include "service.h"
#include "account.h"
//#include "storage.hpp"
#include "user.h"
 #include "template.h"

#include <QDebug>
 #include <QString>
#include <QtCore>
#include <QFile>

#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>




using std::string;
using std::vector;

//#include "storage.hpp"


class SqliteStorage
{    
    const string dir_name_;
    QSqlDatabase db_;

    vector<Service> Services_;
    vector<Account> Accounts_;

    int getNewServiceId(){return -1;}
    int getNewAccountId(){return -1;}

//    static Service rowToService(const CsvRow &row);
//    static CsvRow ServiceToRow(const Service &st);
//    static Account rowToAccount(const CsvRow &row);
//    static CsvRow AccountToRow(const Account &cs);

  public:
    SqliteStorage(const string &dir_name);

    bool load();
    bool save();
    // Services
    vector<Service> getAllServices(void);
    optional<Service> getServiceById(int Service_id);
    bool updateService(const Service &Service);
    bool removeService(int Service_id);
    int insertService(const Service &Service);
    // Accounts
    vector<Account> getAllAccounts(void);
    optional<Account> getAccountById(int Account_id);
    optional<Template> getTemplateById(int Account_id);
    bool updateAccount(const Account &Account);
    bool removeAccount(int Account_id);
    int insertAccount(const Account &Account);



    //user

    optional<User> Sql_getUser(string login, string password);
    vector<Service> Sql_getAllServicesByUser(int user_id );
    vector<Service> Sql_getAllServicesByUserOffset(int user_id, int offset, int limit );

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
    vector<Service> Sql_getAllServicesByUserOffsetSearch(int user_id, int offset, int limit, string str );
    int Sql_getServicesNumberSearch(int user_id, string str);
 };

#endif // SQLITE_STORAGE_H
