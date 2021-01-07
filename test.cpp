#include <iostream>
#include <curl/curl.h>

static size_t write_data(
  void* contents, 
  size_t size, 
  size_t nmemb, 
  void* userp)
{
  ((std::string*)userp)->append(
    (char*)contents, size * nmemb); 
  
  return size * nmemb;
}

std::string get_result(const std::string& pin)
{
  struct curl_slist* list{ nullptr };

  list = curl_slist_append(list,
    "Content-Type: application/json");

  std::string result{};

  CURL* curl = curl_easy_init();

  std::string url{ "http://127.0.0.1:8000/api/pin/" + pin };

  curl_easy_setopt(curl,
    CURLOPT_URL, url);
  curl_easy_setopt(curl,
    CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(curl,
    CURLOPT_USERAGENT, "curl/7.38.0");
  curl_easy_setopt(curl,
    CURLOPT_HTTPHEADER, list);
  curl_easy_setopt(curl,
    CURLOPT_MAXREDIRS, 50L);
  curl_easy_setopt(curl,
    CURLOPT_CUSTOMREQUEST, "POST");
  curl_easy_setopt(curl,
    CURLOPT_TCP_KEEPALIVE, 1L);
  curl_easy_setopt(curl,
    CURLOPT_WRITEFUNCTION, write_data);
  curl_easy_setopt(curl,
    CURLOPT_WRITEDATA, &result);

  CURLcode ret = curl_easy_perform(curl);

  curl_easy_cleanup(curl); 
  curl_slist_free_all(list);

  return result;
}

std::string get_pin()
{
  std::string pin{};
  std::cout << "pin: ";
  std::cin >> pin;

  return pin;
}

extern "C" auto main(void) -> void
{
  std::string pin{ get_pin() };

  std::string result{ get_result(pin) };

  if (result.find("valid_pin") != std::string::npos)
    std::cout << "success! valid pin\n";
  else
    std::cout << "sorry, invalid pin\n";

  std::cin.get();
}
