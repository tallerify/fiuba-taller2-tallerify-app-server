

#include "PlayController.h"
#include "../config/Constants.h"

PlayController::PlayController() {
    playRegex = "/play/.*\\.mp3$";
    addRoute(HTTP_GET, "/play/", new RequestHandler<PlayController, JSONResponse>(this, &PlayController::get));
}

PlayController::~PlayController() {

}

bool PlayController::handles(std::string method, std::string url) {
    return method == HTTP_GET && std::regex_match(url, playRegex);
}

Response *PlayController::process(Request &request) {
    Response *response = NULL;

    response = Controller::process(request);
    if (!response && request.getHttpVerb() == HTTP_GET) {
        // It's a play track
        setElementId(request);
        request.setUrl("/play/");
        response = Controller::process(request);
    }

    return response;
}

void PlayController::get(Request &request, JSONResponse &response) {
    std::string fileLocation = "../music/" + request.getElementIdString(); // TODO: Check in compose the location
    mg_http_serve_file(request.getConnection(), request.getHttpMessage(), fileLocation.c_str(),
                       mg_mk_str("audio/mpeg3"), mg_mk_str(""));
}
