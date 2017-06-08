//
// Created by dell on 2017/6/8.
//

#ifndef SIMVER_REQUEST_H
#define SIMVER_REQUEST_H

#include<map>
#include<string>

class Request{
public:
    Request();
    ~Request();
    void setHeader(std::string head, std::string content){
        headers_[head] = content;
    }
    std::string getHeader(std::string head){
        return headers_.find(head) == headers_.end() ? "" : headers_[head];
    }

private:
    std::map<std::string, std::string> headers_;
};

#endif //SIMVER_REQUEST_H