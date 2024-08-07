#ifndef CRUD_STATICCONTROLLER_HPP
#define CRUD_STATICCONTROLLER_HPP

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/json/ObjectMapper.hpp"
#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <filesystem> // For getting the current path

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

class StaticController : public oatpp::web::server::api::ApiController {
public:
  StaticController(const std::shared_ptr<oatpp::web::mime::ContentMappers>& apiContentMappers)
    : oatpp::web::server::api::ApiController(apiContentMappers)
  {}
public:

  static std::shared_ptr<StaticController> createShared(
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers) // Inject ContentMappers
  ){
    return std::make_shared<StaticController>(apiContentMappers);
  }

  std::string readFile(const std::string& filePath) {
    std::ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
      std::cerr << "Could not open file: " << filePath << std::endl; // Logging
      std::cerr << "Current path: " << std::filesystem::current_path() << std::endl; // Log current path
      throw std::runtime_error("Could not open file: " + filePath);
    }
    std::stringstream buffer;
    buffer << fileStream.rdbuf();
    return buffer.str();
  }

  ENDPOINT("GET", "/", root) {
    std::string html;
    try {
      html = readFile("../static/index.html");
    } catch (const std::runtime_error& e) {
      return createResponse(Status::CODE_500, e.what());
    }
    auto response = createResponse(Status::CODE_200, html);
    response->putHeader(Header::CONTENT_TYPE, "text/html");
    return response;
  }

  ENDPOINT("GET", "/styles.css", getStyles) {
    std::string css;
    try {
      css = readFile("../static/styles.css");
    } catch (const std::runtime_error& e) {
      return createResponse(Status::CODE_500, e.what());
    }
    auto response = createResponse(Status::CODE_200, css);
    response->putHeader(Header::CONTENT_TYPE, "text/css");
    return response;
  }

  ENDPOINT("GET", "/script.js", getScript) {
    std::string js;
    try {
      js = readFile("../static/script.js");
    } catch (const std::runtime_error& e) {
      return createResponse(Status::CODE_500, e.what());
    }
    auto response = createResponse(Status::CODE_200, js);
    response->putHeader(Header::CONTENT_TYPE, "application/javascript");
    return response;
  }

  ENDPOINT("GET", "../static/{filename}", getStaticFile,
           PATH(oatpp::String, filename)) {
    std::string filenameStr = filename->c_str();
    std::string fileExtension = filenameStr.substr(filenameStr.find_last_of(".") + 1);
    std::string filePath = "static/" + filenameStr;
    std::string fileContent;

    try {
      fileContent = readFile(filePath);
    } catch (const std::runtime_error& e) {
      return createResponse(Status::CODE_500, e.what());
    }

    auto response = createResponse(Status::CODE_200, fileContent);

    if (fileExtension == "html") {
      response->putHeader(Header::CONTENT_TYPE, "text/html");
    } else if (fileExtension == "js") {
      response->putHeader(Header::CONTENT_TYPE, "application/javascript");
    } else if (fileExtension == "css") {
      response->putHeader(Header::CONTENT_TYPE, "text/css");
    } else {
      response->putHeader(Header::CONTENT_TYPE, "text/plain");
    }

    return response;
  }

  // Fallback endpoint to serve static files for any unmapped route
  ENDPOINT("GET", "/*", defaultEndpoint, REQUEST(std::shared_ptr<IncomingRequest>, request)) {
    std::string filePath = "../static/" + std::string(request->getPathTail()->c_str());
    std::string fileContent;

    try {
      fileContent = readFile(filePath);
    } catch (const std::runtime_error& e) {
      return createResponse(Status::CODE_404, "File not found");
    }

    auto response = createResponse(Status::CODE_200, fileContent);
    std::string fileExtension = filePath.substr(filePath.find_last_of(".") + 1);

    if (fileExtension == "html") {
      response->putHeader(Header::CONTENT_TYPE, "text/html");
    } else if (fileExtension == "js") {
      response->putHeader(Header::CONTENT_TYPE, "application/javascript");
    } else if (fileExtension == "css") {
      response->putHeader(Header::CONTENT_TYPE, "text/css");
    } else {
      response->putHeader(Header::CONTENT_TYPE, "text/plain");
    }

    return response;
  }

};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif //CRUD_STATICCONTROLLER_HPP
