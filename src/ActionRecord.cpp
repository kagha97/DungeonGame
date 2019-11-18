#include "ActionRecord.h"

std::vector<std::string> ActionRecord::record;

void ActionRecord::addRecord(std::string text) {
  record.insert(record.begin(), text);
  if (record.size() > MAXRECORDS) {
    record.pop_back();
  }
}

std::string ActionRecord::getRecords() {
  std::stringstream ss;
  for (int i = record.size(); i --> 0; ) {
    ss << record[i] << std::endl;
  }
  return ss.str();
}

std::string ActionRecord::getLatest() {
  return record[0];
}

std::vector<std::string> ActionRecord::getFullRecord() {
  return record;
}
