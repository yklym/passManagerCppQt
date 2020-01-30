#ifndef TEMPLATE_H
#define TEMPLATE_H


#pragma once
#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include <QString>
#include <QtCore>
#include<rpc/msgpack.hpp>

//
using std::string;
using std::vector;


struct Template
{
    int id;
    string login;
    string password;
    string pass_strength;
    string description;
    MSGPACK_DEFINE_ARRAY(id, login, password,pass_strength,description);

    Template(){}  // default

    Template(int id, string login, string password, string pass_strength, string desription, int usage_rate){
        this->id = id;
        this->login = login;
        this->password = password;
        this->pass_strength = pass_strength;
        this->description = description;
     }
         Template(const Template & other){
            this->id = other.id;
            this->login = other.login;
            this->password = other.password;
            this->pass_strength = other.pass_strength;
            this->description = other.description;
         }
};
Q_DECLARE_METATYPE(Template)

//Q_DECLARE_METATYPE(Student);




#endif // TEMPLATE_H
