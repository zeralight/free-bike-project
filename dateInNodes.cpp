#include <iostream>
#include <string>
#include <vector>

std::vector<int> dateInNodes(std::string csvDate) {
  std::vector<std::string> tmpDateInNodes;
  std::string tmpNode="";
  for (int i=0; i<=csvDate.size(); ++i) {
    if (csvDate[i]=='/' || csvDate[i]==':' || csvDate[i]==' ' || csvDate[i]=='\000') {
      tmpDateInNodes.push_back(tmpNode);
      tmpNode="";
    }
    else {
      tmpNode+=csvDate[i];
    }
  }
  std::vector<int> dateInNodes;
  for (int i=0; i<5; ++i)
    dateInNodes.push_back(std::stoi(tmpDateInNodes[i]));
  return dateInNodes;
}

/*
int main() {
  std::vector<int> intDate = dateInNodes("2/20/2017 20:21");
  std::cout << intDate[0] << " " << intDate[1] << " " << intDate[2] << " " << intDate[3] << " " << intDate[4] << std::endl;
  return 0;
}
*/
