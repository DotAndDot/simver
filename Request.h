//
// Created by dell on 2017/6/8.
//

#ifndef SIMVER_REQUEST_H
#define SIMVER_REQUEST_H

#include<map>
#include<string>

class Request{
public:
    Request():state_("completed"){};
    ~Request();

    bool compelted(){ return state_ == "completed"; }
    void setIncompleted(){ state_ = "incompleted";}
    void setCompleted(){ state_ = "completed"; }
    void setState(std::string sta){ state_ = sta; }

    void setHeader(std::string head, std::string content){
        headers_[head] = content;
    }
    std::string getHeader(std::string head){
        return headers_.find(head) == headers_.end() ? "" : headers_[head];
    }

    std::string& operator [](std::string key){
        if(headers_.find(key) != headers_.end()){
            return headers_[key];
        }
        std::string t;
        return t;
    }

    void clear(){ headers_.clear(); }

private:
    std::map<std::string, std::string> headers_;
    std::string state_;
};

#endif //SIMVER_REQUEST_H
