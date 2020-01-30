#ifndef ACCOUNT_H
#define ACCOUNT_H

#pragma once
#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include <QString>
#include <QtCore>

//
using std::string;
using std::vector;

//struct Account
//{
//    int id;
//    string login;
//    string password;
//    string pass_strength;

//    Account();
//    Account(const Account & other);
////    ~Account(){}

//};

struct Account
{
    int id;
    string login;
    string password;
    string pass_strength;
    bool isTemplate;
    int service_id;
    MSGPACK_DEFINE_ARRAY(id, login, password,pass_strength,isTemplate, service_id);
    Account(){}  // default

    Account(int id, string login, string password, string pass_strength, bool isTemplate, int service_id){
        this->id = id;
        this->login = login;
        this->password = password;
        this->pass_strength = pass_strength;
        this->isTemplate = isTemplate;
        this->service_id = service_id;
    }
    Account(const Account & other){
        this->id = other.id;
        this->login = other.login;
        this->password = other.password;
        this->pass_strength = other.pass_strength;
        this->isTemplate = other.isTemplate;
        this->service_id = other.service_id;
    } // copy
};
Q_DECLARE_METATYPE(Account);

//Q_DECLARE_METATYPE(Student);

#endif // ACCOUNT_H


