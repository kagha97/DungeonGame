#include "ActionRecord.h"

ActionRecord::ActionRecord()
{
  //ctor
}

std::vector<std::string> ActionRecord::record;

void ActionRecord::addRecord(std::string text)
{
  record.insert(record.begin(), text);
  if(record.size() > MAXRECORDS) {
    record.pop_back();
  }
}

std::string ActionRecord::getRecords()
{
  std::stringstream ss;
for (int i = record.size(); i --> 0; )
{
    ss << record[i] << std::endl;
}
  return ss.str();
}


ActionRecord::~ActionRecord()
{

}
