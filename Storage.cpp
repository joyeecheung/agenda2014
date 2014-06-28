#include "Storage.h"

Storage* Storage::instance_ = nullptr;

Storage::Storage() {
  if (ReadFromFile("agenda.data") == false) {
    userList_.clear();
    meetingList_.clear();
  }
}

Storage* Storage::GetInstance(void) {
  if (!instance_) {
    instance_ = new Storage();
  }
  return instance_;
}

Storage::~Storage() {
  WriteToFile("agenda.data");
}

bool Storage::Sync(void) {
  return WriteToFile("agenda.data");
}

void Storage::CreateUser(const User& user_) {
  userList_.push_back(user_);
}

std::list<User> Storage::QueryUser(std::function<bool(const User&)> filter) {
  std::list<User> v;
  for (auto i : userList_) {
    if (filter(i))
      v.push_back(i);
  }
  return v;
}

int Storage::UpdateUser(std::function<bool(const User&)> filter, std::function<void(User&)> switcher) {
  int result = 0;
  for (auto i : userList_) {
    if (filter(i)) {
      switcher(i);
      result++;
    }
  }
  return result;
}

int Storage::DeleteUser(std::function<bool(const User&)> filter) {
  int result = 0;
  for (auto i = userList_.begin(); i != userList_.end(); ++i) {
    if (filter(*i)) {
      auto tmpit = i;
      --i;
      userList_.erase(tmpit);
      result++;
    }
  }
  return result;
}

void Storage::CreateMeeting(const Meeting& meeting_) {
  meetingList_.push_back(meeting_);
}

std::list<Meeting> Storage::QueryMeeting(std::function<bool(const Meeting&)> filter) {
  std::list<Meeting> v;
  for (auto i : meetingList_) {
    if (filter(i))
      v.push_back(i);
  }
  return v;
}

int Storage::UpdateMeeting(std::function<bool(const Meeting&)> filter, std::function<void(Meeting&)> switcher) {
  int result = 0;
  for (auto i : meetingList_) {
    if (filter(i)) {
      switcher(i);
      result++;
    }
  }
  return result;
}

int Storage::DeleteMeeting(std::function<bool(const Meeting&)> filter) {
  int result = 0;
  for (auto i = meetingList_.begin(); i != meetingList_.end(); ++i) {
    if (filter(*i)) {
      auto tmpit = i;
      --i;
      meetingList_.erase(tmpit);
      result++;
    }
  }
  return result;
}

bool Storage::ReadFromFile(char *filename) {
  ;
}

bool Storage::WriteToFile(char *filename) {
  ;
}
