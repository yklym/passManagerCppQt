#ifndef USER_H
#define USER_H
#include <string>
#include<rpc/msgpack.hpp>
struct User{


    std::string username;
    std::string password;
    int id = -1;
    MSGPACK_DEFINE_ARRAY(id, username, password);
};
//Q_DECLARE_METATYPE(User);

#endif // USER_H
