#include <iostream>
#include <string>
#include <vector>

vector<int> dateInNodes(string csvDate) {
  vector<string> tmpDateInNodes;
  string tmpNode="";
  for (int i=0; i<=csvDate.size(); ++i) {
    if (csvDate[i]=='/' || csvDate[i]==':' || csvDate[i]==' ' || csvDate[i]=='\000') {
      tmpDateInNodes.push_back(tmpNode);
      tmpNode="";
    }
    else {
      tmpNode+=csvDate[i];
    }
  }
  vector<int> dateInNodes;
  for (int i=0; i<5; ++i)
    dateInNodes.push_back(stoi(tmpDateInNodes[i]));
  return dateInNodes;
}

/*
int main() {
  vector<int> intDate = dateInNodes("2/20/2017 20:21");
  cout << intDate[0] << " " << intDate[1] << " " << intDate[2] << " " << intDate[3] << " " << intDate[4] << endl;
  return 0;
}
*/
