#include "sqlite_storage.h"


SqliteStorage:: SqliteStorage(const string &dir_name) : dir_name_(dir_name) {
    db_ = QSqlDatabase::addDatabase("QSQLITE");
}

//vector<Service> getAllServices(void);
bool SqliteStorage::load(){

    QString path = QString::fromStdString(this->dir_name_) + "data.sqlite";
    this->db_.setDatabaseName(path);    // set sqlite database file path
    bool connected = db_.open();  // open db connection

    if (!connected) {
        qDebug() << "Error while opening storage"+ path;
        return false;
    }
    qDebug() << "Opened storage://"+ path;
    return true;

}
bool SqliteStorage::save(){
    if(this->db_.isOpen()){
        this->db_.close();
        return true;
    }
    return false;

}
vector<Service> SqliteStorage::getAllServices(void){
    QSqlQuery query("SELECT * FROM services");
    vector<Service> Services;
    while (query.next())
    {
        Service buf;
        buf.name = query.value("name").toString().toStdString();
        buf.description = query.value("description").toString().toStdString();
        buf.id = query.value("id").toInt();
        buf.account_id = query.value("account_id").toInt();
        buf.user_id = query.value("user_id").toInt();
        Services.push_back(buf);
        //       qDebug() << buf.id << " | ";
    }
    query.finish();

    return Services;

}
optional<Service> SqliteStorage::getServiceById(int Service_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM services WHERE id = :id");
    query.bindValue(":id", Service_id);
    if (!query.exec()) {  // do exec if query is prepared SELECT query
        qDebug() << "Get Service error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
    }
    if (query.next()) {

        Service buf;
        buf.name = query.value("name").toString().toStdString();
        buf.description = query.value("description").toString().toStdString();
        buf.user_id = query.value("user_id").toInt();
        buf.account_id = query.value("account_id").toInt();
        buf.id = query.value("id").toInt();
        query.finish();
        return buf;
    } else {
        query.finish();

        return nullopt;
    }
}


//Service SqliteStorage::rowToService(const CsvRow &row)
//{
//    Service class_item;
//    class_item.id = std::stoi(row[0]);
//    class_item.name = row[1];
//    class_item.username = row[2];
//    return class_item;
//}
bool SqliteStorage::updateService(const Service &Service)
{
    QSqlQuery query;
    query.prepare("UPDATE services SET name = :name, description = :description, account_id = :account_id WHERE id = :nmb");
    query.bindValue(":name", QString::fromStdString(Service.name));
    query.bindValue(":description", QString::fromStdString(Service.description));
    query.bindValue(":account_id", Service.account_id);
    query.bindValue(":nmb", Service.id);
    if (!query.exec()){
        qDebug() << "update error:" << query.lastError() << ", SqLite error code:" << query.lastError().number();
        return false;
    }

    return true;
}
int SqliteStorage::insertService(const Service &Service)
{
    struct Service item = Service;

    QSqlQuery query;
    query.prepare("INSERT INTO services (name, description, user_id, account_id) VALUES (:name, :description, :user_id, :account_id)");
    query.bindValue(":name", QString::fromStdString(Service.name));
    query.bindValue(":description", QString::fromStdString(Service.description));
    query.bindValue(":account_id", Service.account_id);
    query.bindValue(":user_id", Service.user_id);

    if (!query.exec())
    {
        qDebug() << "add error:" << query.lastError() << ", SqLite error code:" << query.lastError().number();

    }
    QVariant id = query.lastInsertId();
    return id.toInt();


    return item.id;
}
//CsvRow SqliteStorage::ServiceToRow(const Service &st)
//{
//    vector<string> res;
//    res.push_back(std::to_string(st.id));
//    res.push_back(st.name);
//    res.push_back(st.username);
//    return res;
//}



bool SqliteStorage::removeService(int Service_id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM services WHERE id = :id");
    query.bindValue(":id", Service_id);
    if (!query.exec()){
        qDebug() << "deletePerson error:" << query.lastError();
        return false;
    }
    return true;
}

//Account SqliteStorage::rowToAccount(const CsvRow &row)
//{
//    Account class_item;
//    class_item.id = std::stoi(row[0]);
//    class_item.login = row[1];
//    class_item.password = row[2];
//    class_item.pass_strength = row[3];
//    return class_item;
//}


vector<Account> SqliteStorage::getAllAccounts()
{
    QSqlQuery query("SELECT * FROM accounts");
    vector<Account> Accounts;
    while (query.next())
    {
        Account buf;
        buf.login = query.value("login").toString().toStdString();
        buf.password = query.value("password").toString().toStdString();
        buf.pass_strength = query.value("pass_strength").toString().toStdString();
        buf.id = query.value("id").toInt();
        buf.isTemplate = query.value("isTemplate").toBool();
        buf.service_id = query.value("service_id").toInt();
        Accounts.push_back(buf);
        //       qDebug() << buf.id << " | ";
    }
    query.finish();

    return Accounts;
}




//CsvRow SqliteStorage::AccountToRow(const Account &st)
//{
//    vector<string> res;
//    res.push_back(std::to_string(st.id));
//    res.push_back(st.login);
//    res.push_back(st.password);
//    res.push_back(st.pass_strength);
//    return res;
//}



optional<Account> SqliteStorage::getAccountById(int Account_id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM accounts WHERE id = :id");
    query.bindValue(":id", Account_id);
    if (!query.exec()) {  // do exec if query is prepared SELECT query
        qDebug() << "Get Account error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
    }
    qDebug() << "GeTTACCOUNTBY ID:";
    if (query.next()) {

        Account buf;
        buf.id = query.value("id").toInt();
        buf.login = query.value("login").toString().toStdString();
        qDebug() << query.value("login").toString();
        buf.password = query.value("password").toString().toStdString();
        buf.pass_strength = query.value("pass_strength").toString().toStdString();
        buf.isTemplate = query.value("isTemplate").toBool();
        buf.service_id = query.value("service_id").toInt();
        query.finish();
        return buf;
    } else {
        query.finish();

        return nullopt;
    }
}

optional<Template> SqliteStorage::getTemplateById(int account_id){
    QSqlQuery query;

    query.prepare("SELECT * FROM templates WHERE id = :id");
    query.bindValue(":id", account_id);
    if (!query.exec()) {  // do exec if query is prepared SELECT query
        qDebug() << "Get Account error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
    }
    qDebug() << "GeTTACCOUNTBY ID:";
    if (query.next()) {

        Template buf;
        buf.id = query.value("id").toInt();
        buf.login = query.value("login").toString().toStdString();
        qDebug() << query.value("login").toString();
        buf.password = query.value("password").toString().toStdString();
        buf.pass_strength = query.value("pass_strength").toString().toStdString();
         buf.description = query.value("description").toString().toStdString();
        query.finish();
        return buf;
    } else {
        query.finish();

        return nullopt;
    }
}
bool SqliteStorage::updateAccount(const Account &Account)
{
    QSqlQuery query;
    query.prepare("UPDATE accounts SET login = :login, password = :pass, "
                  "pass_strength = :pass_str, isTemplate = :isTemplate,"
                  "service_id = :service_id "
                  "WHERE id = :nmb");
    query.bindValue(":login", QString::fromStdString(Account.login));

    query.bindValue(":isTemplate", Account.isTemplate);
    query.bindValue(":service_id", Account.service_id);

    query.bindValue(":pass", QString::fromStdString(Account.password));
    query.bindValue(":pass_str", QString::fromStdString(Account.pass_strength));
    query.bindValue(":nmb", Account.id);
    if (!query.exec()){
        qDebug() << "update error:" << query.lastError() << ", SqLite error code:" << query.lastError().number();
        return false;
    }
}


//--------------------------------------------------------------

bool SqliteStorage::removeAccount(int Service_id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM accounts WHERE id = :id");
    query.bindValue(":id", Service_id);
    if (!query.exec()){
        qDebug() << "deletePerson error:" << query.lastError();
        return false;
    }
    return true;
}



int SqliteStorage::insertAccount(const Account &account)
{

    QSqlQuery query;
    query.prepare("INSERT INTO accounts (login, password, pass_strength, isTemplate, service_id)"
                  " VALUES (:login, :pass, :pass_str, :isTemplate, :service_id)");
    query.bindValue(":login", QString::fromStdString(account.login));
    query.bindValue(":pass", QString::fromStdString(account.password));


    query.bindValue(":isTemplate",  account.isTemplate);
    query.bindValue(":service_id", account.service_id);
    query.bindValue(":pass_str", QString::fromStdString(account.pass_strength));
    if (!query.exec())
    {
        qDebug() << "add error:" << query.lastError() << ", SqLite error code:" << query.lastError().number();

    }
    QVariant id = query.lastInsertId();
    return id.toInt();


}

//-------------------------------------------------------------------------------------------------
//USER

QString hashPassword(QString const & pass) {
    QByteArray pass_ba =  pass.toUtf8();
    QByteArray hash_ba = QCryptographicHash::hash(pass_ba, QCryptographicHash::Md5);
    QString pass_hash = QString(hash_ba.toHex());
    return pass_hash;
}

optional<User>  SqliteStorage::Sql_getUser(string login, string password){
    QSqlQuery query;
    //    query.prepare("SELECT * FROM users WHERE username = \"user\" AND password_hash =  \"1a1dc91c907325c69271ddf0c944bc72\" ");
    query.prepare("SELECT * FROM users WHERE username = :username AND password_hash = :password_hash");
    query.bindValue(":username", QString::fromStdString(login));
    query.bindValue(":password_hash", hashPassword(QString::fromStdString(password)));
    qDebug()<< QString::fromStdString(login);

//    qDebug()<< hashPassword(password);
    if (!query.exec())
    {
        qDebug() << "Get Service error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();
        return nullopt;
        throw 1;
    }
    if (query.next())
    {
        User user;
        user.id = query.value("id").toInt();
        user.username = login;
        user.password = password;
        query.finish();
        return user;
    }
    query.finish();
    return nullopt;
}
vector<Service>  SqliteStorage::Sql_getAllServicesByUser(int user_id ){
    QSqlQuery query;
    query.prepare("SELECT * FROM services where user_id = :user_id");
    query.bindValue(":user_id", user_id);

    vector<Service> Services;
    if (!query.exec())
    {
        qDebug() << "Get Service error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        throw 1;
    }
    while (query.next())
    {
        Service buf;
        buf.name = query.value("name").toString().toStdString();
        buf.description = query.value("description").toString().toStdString();
        buf.account_id = query.value("account_id").toInt();
        buf.user_id = query.value("user_id").toInt();
        buf.id = query.value("id").toInt();
        Services.push_back(buf);
        qDebug() << buf.id << " | ";
    }
    query.finish();

    return Services;
}
vector<Template>SqliteStorage::Sql_getAllTemplatesByUser(int user_id ){
    QSqlQuery query;
    query.prepare("SELECT * FROM template_links where user_id = :service_id");
    query.bindValue(":service_id", user_id);
    if (!query.exec())
    {
        qDebug() << "Get Service error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        throw 1;
    }
    vector<Template> Accounts;
    while (query.next())
    {
        Template buf;
        int bufAccId = query.value("template_id").toInt();

        buf = this->getTemplateById(bufAccId).value();

        Accounts.push_back(buf);
    }
    query.finish();

    return Accounts;
}
vector<Account>  SqliteStorage::Sql_getAllAccountsByService(int user_id ){
    QSqlQuery query;
    query.prepare("SELECT * FROM links where service = :service_id");
    query.bindValue(":service_id", user_id);
    if (!query.exec())
    {
        qDebug() << "Get Service error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        throw 1;
    }
    vector<Account> Accounts;
    while (query.next())
    {
        Account buf;
        int bufAccId = query.value("account").toInt();

        buf = this->getAccountById(bufAccId).value();

        //        buf.login = query.value("login").toString().toStdString();
        //        buf.password = query.value("password").toString().toStdString();
        //        buf.pass_strength = query.value("pass_strength").toString().toStdString();
        //        buf.id = query.value("id").toInt();
        Accounts.push_back(buf);
        //       qDebug() << buf.id << " | ";
    }
    query.finish();

    return Accounts;

}

vector<Account> SqliteStorage::Sql_getAllAccountsFreeFromService( int user_id){

    vector<Account> allAccounts= this->getAllAccounts();
    vector<Account>conAccounts = this->Sql_getAllAccountsByService(user_id);
    vector<Account>result;

    for(Account acc : allAccounts){
        bool flag = true;
        for(Account newAcc: conAccounts){
            if(acc.id == newAcc.id){
                flag=false;
                qDebug() << "="+QString::fromStdString(acc.login);
                break;
            }
        }
        if(flag){
            result.push_back(acc);
            qDebug() << QString::fromStdString(acc.login);
        }
    }
    //    while (query.next())
    //    {
    //        Account buf;
    //        int bufAccId = query.value("account").toInt();

    //        buf = this->getAccountById(bufAccId).value();

    ////        buf.login = query.value("login").toString().toStdString();
    ////        buf.password = query.value("password").toString().toStdString();
    ////        buf.pass_strength = query.value("pass_strength").toString().toStdString();
    ////        buf.id = query.value("id").toInt();
    //        Accounts.push_back(buf);
    //        //       qDebug() << buf.id << " | ";
    //    }
    //    query.finish();

    return result;
}

bool  SqliteStorage::Sql_connectAccountToService(int service_id, int account_id ){
    QSqlQuery query;
    query.prepare("INSERT INTO links ( service, account) VALUES (:serv_id, :acc_id)");
    query.bindValue(":serv_id", service_id);
    query.bindValue(":acc_id", account_id);
    if (!query.exec())
    {
        qDebug() << "add error:" << query.lastError() << ", SqLite error code:" << query.lastError().number();
        return false;
    }
    return true;

}
int SqliteStorage::Sql_removeTemplate(int templ_id, int user_id){
//    QSqlQuery query;
//    query.prepare("DELETE FROM templates WHERE id = :templ_id");
//    query.bindValue(":templ_id", templ_id);

//    if (!query.exec()){
//        qDebug() << "deletePerson error:" << query.lastError();
//        return false;
//    }
    QSqlQuery query2;
    query2.prepare("DELETE FROM template_links where template_id = :acc_id AND user_id = :us_id");
    query2.bindValue(":us_id", user_id);
    query2.bindValue(":acc_id", templ_id);
    if (!query2.exec()){
        qDebug() << "deletePerson error:" << query2.lastError();
        return false;
    }

    QSqlQuery query3;
    query3.prepare("SELECT COUNT(*) as number FROM template_links where template_id = :acc_id ");
     query3.bindValue(":acc_id", templ_id);
    if (!query3.exec()){
        qDebug() << "deletePerson error:" << query3.lastError();
        return false;
    }
    if (query3.next()) {
        int number =query3.value("number").toInt();
        if(number !=0){
            return false;
        }
    }

    QSqlQuery query4;
    query4.prepare("DELETE FROM templates where id = :acc_id ");
     query4.bindValue(":acc_id", templ_id);
     if (!query4.exec()){
         qDebug() << "deletePerson error:" << query4.lastError();
         return false;
     }
     return true;
}

bool  SqliteStorage::Sql_deleteAccountFromService(int service_id, int account_id ){
    QSqlQuery query;
    query.prepare("DELETE FROM links WHERE service = :serv_id AND account = :acc_id");
    query.bindValue(":serv_id", service_id);
    query.bindValue(":acc_id", account_id);
    if (!query.exec()){
        qDebug() << "deletePerson error:" << query.lastError();
        return false;
    }

    QSqlQuery query2;
    query2.prepare("DELETE FROM accounts where id = :acc_id");
    query2.bindValue(":acc_id", account_id);
    if (!query2.exec()){
        qDebug() << "deletePerson error:" << query.lastError();
        return false;
    }
    return true;
}
int SqliteStorage::Sql_insertServiceToUser(int user_id, const Service &Service ){

    QSqlQuery query;
    query.prepare("INSERT INTO services (name, description, user_id, account_id,) VALUES (:name, :description, :user_id, :account_id)");
    query.bindValue(":name", QString::fromStdString(Service.name));
    query.bindValue(":description", QString::fromStdString(Service.description));
    //       query.bindValue(":username", QString::fromStdString(Service.username));
    query.bindValue(":user_id", user_id);
    query.bindValue(":account_id", Service.account_id);

    if (!query.exec())
    {
        qDebug() << "add error:" << query.lastError() << ", SqLite error code:" << query.lastError().number();

    }
    QVariant id = query.lastInsertId();
    return id.toInt();


}

Account SqliteStorage::Sql_getAccountByService(int service_id){
    //    QSqlQuery query;
    //    query.prepare("SELECT account_id FROM services where id = :service_id");
    //    query.bindValue(":service_id", service_id);
    //    if (!query.exec())
    //    {
    //         qDebug() << "Get Service error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

    //        throw 1;
    //    }


    //    int account_id = query.value("account_id").toInt();
    //    qDebug()<<"!!!!ID:" << account_id;
    optional<Account> buf = this->getAccountById(service_id);
    if(buf){
        return buf.value();
    }else{
        Account ret;

        ret.id = -1;
        return ret;
    }


}

int SqliteStorage::Sql_insertTemplate(int user_id, const Template &Template){
    QSqlQuery query;
    query.prepare("INSERT INTO templates (login, password, pass_strength )"
                  " VALUES (:login, :pass, :pass_str)");
    query.bindValue(":login", QString::fromStdString(Template.login));
    query.bindValue(":pass", QString::fromStdString(Template.password));
    query.bindValue(":pass_str", QString::fromStdString(Template.pass_strength));
    if (!query.exec())
    {
        qDebug() << "add error:" << query.lastError() << ", SqLite error code:" << query.lastError().number();

    }
    QVariant id = query.lastInsertId();
    query.finish();

    QSqlQuery query2;
    query2.prepare("INSERT INTO template_links (user_id, template_id) VALUES (:user_id, :template_id)");
    query2.bindValue(":user_id", user_id);
    query2.bindValue(":template_id",id.toInt());
    if (!query2.exec())
    {
        qDebug() << "add error:" << query.lastError() << ", SqLite error code:" << query.lastError().number();

    }
    return id.toInt();
}

int SqliteStorage::Sql_insertUser(User user){
    QSqlQuery query3;
    query3.prepare("SELECT COUNT(*) as number FROM users where username = :username ");
     query3.bindValue(":username", QString::fromStdString(user.username));
    if (!query3.exec()){
        qDebug() << "deletePerson error:" << query3.lastError();
        return false;
    }
    if (query3.next()) {
        int number =query3.value("number").toInt();
        qDebug() << number;
        if(number !=0){
            return -1;
        }
    }

//    if(this->Sql_checkUser(user.username)!=-1){
//        qDebug() << "hi hello)";
//        return -1;
//    }
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password_hash)"
                  " VALUES (:username, :password_hash)");
    query.bindValue(":username", QString::fromStdString(user.username));
    query.bindValue(":password_hash", hashPassword(QString::fromStdString(user.password)));
    if (!query.exec())
    {
        qDebug() << "add error:" << query.lastError() << ", SqLite error code:" << query.lastError().number();
        return -1;
    }
    QVariant id = query.lastInsertId();
    query.finish();
    qDebug() <<id.toInt();

    return id.toInt();
}

int SqliteStorage::Sql_checkUser(string username){

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", QString::fromStdString(username));
    if (!query.exec())
        {
        return false;
            qDebug() << "add error:" << query.lastError() << ", SqLite error code:" << query.lastError().number();
            return -1;
        }
    if(query.size()== 0){
        qDebug() << "No users";
        return -1;
    }else {
        while (query.next())
        {
            qDebug() << "Users"<< query.value("id").toInt();
            return query.value("id").toInt();
        }
    }

}

int SqliteStorage::Sql_getServicesNumber(int user_id){
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) as number FROM services where user_id = :user_id");
    query.bindValue(":user_id", user_id);
    if (!query.exec())
    {
        qDebug() << "add error:" << query.lastError() << ", SqLite error code:" << query.lastError().number();
        return -1;
    }if (query.next()) {
        return query.value("number").toInt();
    }
}

vector<Service> SqliteStorage::Sql_getAllServicesByUserOffset(int user_id, int offset, int limit ){
    QSqlQuery query;
    query.prepare("SELECT * FROM services where user_id = :user_id LIMIT :page_size OFFSET :skipped_items");
    query.bindValue(":user_id", user_id);
    query.bindValue(":page_size", offset);
    query.bindValue(":skipped_items", limit);

    vector<Service> Services;
    if (!query.exec())
    {
        qDebug() << "Get Service Offset error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        throw 1;
    }
    while (query.next())
    {
        Service buf;
        buf.name = query.value("name").toString().toStdString();
        buf.description = query.value("description").toString().toStdString();
        buf.account_id = query.value("account_id").toInt();
        buf.user_id = query.value("user_id").toInt();
        buf.id = query.value("id").toInt();
        Services.push_back(buf);
        qDebug() << buf.id << " | ";
    }
    query.finish();

    return Services;
}
vector<Service> SqliteStorage::Sql_getAllServicesByUserOffsetSearch(int user_id, int offset, int limit, string str ){
//    SELECT *
//    FROM items
//    WHERE title LIKE ('%' || :search_text || '%')
//    LIMIT :page_size
//    OFFSET :skipped_items
    QSqlQuery query;
    query.prepare("select * FROM users INNER JOIN services on users.id == services.user_id AND services.name  LIKE ('%' || :search_text || '%')  LIMIT :page_size OFFSET :skipped_items");
    query.bindValue(":user_id", user_id);
    query.bindValue(":page_size", offset);
    query.bindValue(":skipped_items", limit);
    query.bindValue(":search_text", QString::fromStdString(str));

    vector<Service> Services;
    if (!query.exec())
    {
        qDebug() << "Get Service Offset error:" << query.lastError().text() << ", SqLite error code:" << query.lastError().number();

        throw 1;
    }
    while (query.next())
    {
        Service buf;
        buf.name = query.value("name").toString().toStdString();
        buf.description = query.value("description").toString().toStdString();
        buf.account_id = query.value("account_id").toInt();
        buf.user_id = query.value("user_id").toInt();
        buf.id = query.value("id").toInt();
        Services.push_back(buf);
        qDebug() << buf.id << " | ";
    }
    query.finish();

    return Services;
}
int SqliteStorage::Sql_getServicesNumberSearch(int user_id, string str){
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) as number FROM services where user_id = :user_id AND name LIKE ('%' || :search_text || '%') ");
    query.bindValue(":user_id", user_id);
    query.bindValue(":search_text", QString::fromStdString(str));

    if (!query.exec())
    {
        qDebug() << "add error:" << query.lastError() << ", SqLite error code:" << query.lastError().number();
        return -1;
    }if (query.next()) {
        return query.value("number").toInt();
    }
}



