//
// Created by gxh on 2017/6/1.
//
#include "HttpServer.h"
#include "log/log.h"
#include <sys/stat.h>

using namespace simver;
using namespace std;
using namespace std::placeholders;

string HttpServer::WWW_PATH = "";
string HttpServer::SERVER_STRING = "Server: simver/0.1.0\r\n";

HttpServer::HttpServer(uint16_t port, simver::EventLoop *loop)
        :server_("simver", port, loop){
    server_.setConnectionCallback(bind(&HttpServer::onConnection, this, _1));
    server_.setMessageCallback(bind(&HttpServer::onMessage, this, _1, _2));
}

void HttpServer::start() {
    server_.start();
}

void HttpServer::onConnection(Connection *con) {
    if(con->connected()){
        requestMap_[con->getFd()] = new Request();
    }
    else{
        removeRequest(con->getFd());
    }
}

void HttpServer::onMessage(Connection *con, Buffer* buffer) {
    int fd = con->getFd();
    const void* crlf = buffer->findCRLF();
    Request* req = requestMap_[fd];
    while(crlf){
        const void* data = buffer->peek();
        string line(data, crlf - 1);
        if(!req->compelted()){
            size_t index = line.find(':');
            if(index == string::npos){
                LOG_ERROR("HttpServer::onMessage() Error request");
                removeRequest(con->getFd());
                server_.removeConnection(con);
                return;
            }
            string header = line.substr(0, index), content = line.substr(index + 1, line.size() - index - 1);
            req->setHeader(header, content);
        }
        else{
            req->clear();
            size_t index = line.find(' ');
            if(index == string::npos){
                removeRequest(con->getFd());
                LOG_ERROR("HttpServer::onMessage() Error request");
                server_.removeConnection(con);
                return;
            }
            string method = line.substr(0, index);
            size_t index2 = line.find(index + 1, ' ');
            if(index2 == string::npos){
                removeRequest(con->getFd());
                LOG_ERROR("HttpServer::onMessage() Error request");
                server_.removeConnection(con);
                return;
            }
            string path = line.substr(index + 1, index2 - index), version = line.substr(index2 + 1, line.size() - index2 - 1);
            req->setHeader("method", method);
            req->setHeader("path", path);
            req->setHeader("version", version);
            req->setIncompleted();
        }
        size_t len = crlf + 2 - data;
        buffer->retrieve(len);
        const void* tcrlf = buffer->findCRLF();
        if(tcrlf && tcrlf - crlf == 2){
            req->setCompleted();
            //handle requeset
            handleRequest(req, con);
        }
        crlf = tcrlf;
    }
}

void HttpServer::handleRequest(Request* request, Connection *con) {
    struct stat st;
    if((*request)["method"] == "GET"){
        string path((*request)["path"]);
        size_t qindex = path.find('?');
        if(qindex != string::npos){
            badRequest(con);
            return;
        }
        path = WWW_PATH + path;
        if(path.back() == '/'){
            path += "index.html";
        }
        if(stat(path.c_str(), &st) == -1){
            notFound(con);
            return;
        }
        if ((st.st_mode & S_IFMT) == S_IFDIR){
            path += "index.html";
        }
        if ((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH) ){
            badRequest(con);
        }
        else{
            serveFile(con, path);
        }
    }
    else{
        badRequest(con);
    }
}

void HttpServer::notFound(Connection* con) {
    string response;
    response += "HTTP/1.0 404 NOT FOUND\r\n";
    response += SERVER_STRING;
    response += "Content-Type: text/html\r\n";
    response += "\r\n";
    response += "<HTML><TITLE>Not Found</TITLE>\r\n";
    response += "<BODY><P>The server could not fulfill\r\n";
    response += "your request because the resource specified\r\n";
    response += "is unavailable or nonexistent.\r\n";
    response += "</BODY></HTML>\r\n";
    Buffer buf;
    buf.append(response.data(), response.size());
    con->send(&buf);
}

void HttpServer::badRequest(simver::Connection *con) {
    string response;
    response += "HTTP/1.0 400 BAD REQUEST\r\n";
    response += "Server: simver/0.1.0\r\n";
    response += "Content-Type: text/html\r\n";
    response += "\r\n";
    response += "<P>Your browser sent a bad request, ";
    response += "such as a POST without a Content-Length.\r\n";
    Buffer buf;
    buf.append(response.data(), response.size());
    con->send(&buf);
}

void HttpServer::serveFile(simver::Connection *con, string path) {
    FILE *resource = NULL;
    resource = fopen(path, "r");
    if(resource == NULL){
        notFound(con);
    }
    else{
        string headers;
        headers += "HTTP/1.0 200 OK\r\n";
        headers += SERVER_STRING;
        headers += "Content-Type: text/html\r\n";
        headers += "\r\n";
        Buffer buf;
        buf.append(headers.data(), headers.size());
        char rbuf[1024];
        fgets(rbuf, sizeof(rbuf), resource);
        while(!feof(resource)){
            buf.append(rbuf, strlen(rbuf));
            fgets(rbuf, sizeof(buf), resource);
        }
        con->send(&buf);
    }
}