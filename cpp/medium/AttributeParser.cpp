#include <iostream>
#include <map>
#include <sstream>
#include <vector>

std::map<std::string, std::string> parseHRML(std::vector<std::string>& hrml) {
  std::map<std::string, std::string> parsedData;
  std::stringstream hrmltagSS{};
  std::stringstream buffSS{};
  bool tagFlag{false};
  bool tagClosureFlag{false};
  bool valFlag{false};
  std::string attrStr{};
  for (std::string hrmlTag : hrml) {
    const char* hrmlTagPtr = hrmlTag.c_str();
    for (size_t i = 0; i < hrmlTag.size(); i++) {
      if (hrmlTagPtr[i] == '<') {
        tagFlag = true;
        continue;
      } else if (hrmlTagPtr[i] == '/') {
        tagFlag = false;
        tagClosureFlag = true;
      } else if (hrmlTagPtr[i] == '>') {
        if (tagClosureFlag) {
          size_t index = hrmltagSS.str().find_last_of('.');
          if (index != std::string::npos) {
            std::string lastTag =
                hrmltagSS.str().substr(index + 1, hrmltagSS.str().length());
            if (lastTag.compare(buffSS.str()) == 0) {
              auto updatedTag = hrmltagSS.str().substr(0, index);
              hrmltagSS.str(std::string());
              hrmltagSS << updatedTag;
            } else {
              std::cout << "error 1 \n";
            }
          } else {
            if (hrmltagSS.str().compare(buffSS.str()) == 0) {
              hrmltagSS.str(std::string());
            } else {
              std::cout << "error 2\n";
            }
          }
          tagClosureFlag = false;
        } else if (tagFlag) {
          if (hrmltagSS.str().length() > 0) {
            hrmltagSS << '.' << buffSS.str();
          } else {
            hrmltagSS << buffSS.str();
          }
          tagFlag = false;
        }
        buffSS.str(std::string());
        buffSS.clear();
      } else if (hrmlTagPtr[i] == '"') {
        if (valFlag) {
          std::string key = hrmltagSS.str() + "~" + attrStr;
          parsedData[key] = buffSS.str();
          buffSS.str(std::string());
          buffSS.clear();
          valFlag = false;
        } else {
          valFlag = true;
        }
      } else if (hrmlTagPtr[i] == '=') {
        if (!valFlag && !tagClosureFlag && !tagFlag) {
          buffSS >> attrStr;
          buffSS.str(std::string());
          buffSS.clear();
        }
      } else if (hrmlTagPtr[i] == ' ') {
        if (tagFlag) {
          if (hrmltagSS.str().length() > 0) {
            hrmltagSS << '.' << buffSS.str();
          } else {
            hrmltagSS << buffSS.str();
          }
          tagFlag = false;
          buffSS.str(std::string());
          buffSS.clear();
        }
      } else {
        buffSS << hrmlTagPtr[i];
      }
    }
  }
  return parsedData;
}

int main() {
  int n, q;
  std::cin >> n >> q;
  std::vector<std::string> hrml;
  std::cin.ignore();
  for (int i = 0; i < n; i++) {
    std::string str;
    std::getline(std::cin, str);
    hrml.push_back(str);
  }
  auto parsedData = parseHRML(hrml);
  std::stringstream output{};
  for (int i = 0; i < q; i++) {
    std::string str;
    std::getline(std::cin, str);
    if (parsedData.find(str) != parsedData.end()) {
      output << parsedData[str] << std::endl;
    } else {
      output << "Not Found!" << std::endl;
    }
  }
  std::cout << output.str();
  return 0;
}