//
//  connect.cc
//  Connect: programming model with onion architecture.
//
//  Created by Hai Liang Wang<hailiang.hl.wang@gmail.com> on 17/09/14.
//  Copyright © 2017. All rights reserved.
//
#include "connect.h"

#include <iostream>

using namespace std;
using namespace Common;

namespace Common {
namespace Connect {

Middleware::Middleware(){};
Middleware::~Middleware(){};

Connect::Connect(){};
Connect::~Connect(){};

void Connect::use(Middleware& mw)
{
    _middlewares.push_back(&mw);
}

void Connect::handle(std::string& req, std::string& res){
    std::vector<Middleware* >::iterator next = _middlewares.begin();
    std::vector<Middleware* >::const_iterator end = _middlewares.end();
    
    std::function<void() > compose;
    compose = [&]() mutable {
        if (next != _middlewares.end()){
            next = next + 1;
            if(next!=end){
                (*next)->apply(req, res, compose);
            }
        }
    };

    (*next)->apply(req, res, compose);
}

Mw1::Mw1(){};
Mw1::~Mw1(){};

void Mw1::apply(std::string& req, std::string& res, std::function<void() >& next){
    std::cout<< "Mw1 req:" << req <<", res:" << res << endl;
    next();
    std::cout<< "Mw1 req2:" << req <<", res2:" << res << endl;
}

Mw2::Mw2(){};
Mw2::~Mw2(){};

void Mw2::apply(std::string& req, std::string& res, std::function<void() >& next){
    std::cout<< "Mw2 req:" << req <<", res:" << res << endl;
    res += " Mw2 apply-before-next";
    next();
    std::cout<< "Mw2 req2:" << req <<", res2:" << res << endl;
    res += " Mw2 apply-post-next";
}

}
} // name

int main(int argc, char const *argv[])
{
    // auto glambda = [](int D) -> bool {
    //     std::cout << "Print int " << D << endl;
    //     return D < 0;
    // };

    // callback(12, glambda);
    
    Connect::Connect app;
    Connect::Mw1 mw;
    app.use(mw);
    Connect::Mw2 mw2;
    app.use(mw2);
    std::string req = "query    ...";
    std::string res = "response ...";
    app.handle(req, res);
    /**
     * Mw1 req:query    ..., res:response ...
     * Mw2 req:query    ..., res:response ...
     * Mw2 req2:query    ..., res2:response ... Mw2 apply-before-next
     * Mw1 req2:query    ..., res2:response ... Mw2 apply-before-next Mw2 apply-post-next
     */

    return 0;
}