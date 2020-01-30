#ifndef SERVICE_H
#define SERVICE_H

#pragma once
#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include <QString>
#include<rpc/msgpack.hpp>
#include <QtCore>

//
using std::string;
using std::vector;

struct Service
{
    int id = -1;
    string name = "";
    string description = "";
    int user_id = -1;
    int account_id = -1;
    MSGPACK_DEFINE_ARRAY(id, name, description,user_id, account_id);

    Service(){
        this->name = "";
         this->id = -1;
    }
    Service(string name, string description, int id, int user_id, int account_id){
        this->name = name;
         this->id = id;
        this->description = description;
        this->user_id = user_id;
        this->account_id = account_id;
    }
    Service(const Service & other){
        this->id = other.id;
        this->name = other.name;
        this->description = other.description;
        this->user_id = other.user_id;
        this->account_id = other.account_id;
    }
    ~Service(){

    }

};
Q_DECLARE_METATYPE(Service);
#endif // SERVICE_H
