

#include "Request.h"
#include "spdlog/spdlog.h"
#include "../config/Constants.h"

Request::Request(mg_connection *connection, http_message *httpMessage) : connection(connection),
                                                                         httpMessage(httpMessage), url(""), body(""),
                                                                         httpVerb(""), elementId(-1), event(-1),
                                                                         eventData(NULL) {
    parseMessage(httpMessage);
    spdlog::get("console")->info("Processing request {0} {1}", httpVerb, url);
}

Request::~Request() {

}

void Request::writeResponse(Response *response) {
    std::string data = response->getData();
    mg_printf(connection, "%s", data.c_str());
}

void Request::parseMessage(http_message *httpMessage) {
    for (size_t i = 0; i < httpMessage->method.len; ++i) {
        httpVerb += httpMessage->method.p[i];
    }

    for (size_t i = 0; i < httpMessage->uri.len; ++i) {
        url += httpMessage->uri.p[i];
    }

    for (size_t i = 0; i < httpMessage->body.len; ++i) {
        body += httpMessage->body.p[i];
    }
}

const std::string &Request::getUrl() const {
    return url;
}

const std::string &Request::getBody() const {
    return body;
}

const std::string &Request::getHttpVerb() const {
    return httpVerb;
}

int Request::getElementId() const {
    return elementId;
}

void Request::setElementId(int elementId) {
    Request::elementId = elementId;
}

void Request::setUrl(const std::string &url) {
    Request::url = url;
}

mg_connection *Request::getConnection() const {
    return connection;
}

http_message *Request::getHttpMessage() const {
    return httpMessage;
}

const std::string &Request::getElementIdString() const {
    return elementIdString;
}

void Request::setElementIdString(const std::string &elementIdString) {
    Request::elementIdString = elementIdString;
}

Request::Request(mg_connection *connection, int event, void *eventData) : connection(connection), httpMessage(NULL),
                                                                          url("/tracks"), body(""), httpVerb(HTTP_POST),
                                                                          elementId(-1), event(event),
                                                                          eventData(eventData) {
}

int Request::getEvent() const {
    return event;
}

void *Request::getEventData() const {
    return eventData;
}
