#include "Storage.h"

Storage* Storage::instance_ = nullptr;

Storage::Storage() {
  if (readFromFile("agenda.data") == false) {
    userList_.clear();
    meetingList_.clear();
  }
}

Storage* Storage::getInstance(void) {
  if (!instance_) {
    instance_ = new Storage();
  }
  return instance_;
}

Storage::~Storage() {
  sync();
}

bool Storage::sync(void) {
  return writeToFile("agenda.data");
}

void Storage::createUser(const User &user_) {
  userList_.push_back(user_);
}

std::list<User> Storage::queryUser(std::function<bool(const User &)> filter) {
  std::list<User> v;
  for (auto i : userList_) {
    if (filter(i))
      v.push_back(i);
  }
  return v;
}

int Storage::updateUser(std::function<bool(const User &)> filter,
                        std::function<void(User &)> switcher) {
  int result = 0;
  for (auto i : userList_) {
    if (filter(i)) {
      switcher(i);
      result++;
    }
  }
  return result;
}

int Storage::deleteUser(std::function<bool(const User &)> filter) {
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

void Storage::createMeeting(const Meeting &meeting_) {
  meetingList_.push_back(meeting_);
}

std::list<Meeting> Storage::queryMeeting(
    std::function<bool(const Meeting &)>filter) {
  std::list<Meeting> v;
  for (auto i : meetingList_) {
    if (filter(i))
      v.push_back(i);
  }
  return v;
}

int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,
                           std::function<void(Meeting &)> switcher) {
  int result = 0;
  for (auto i : meetingList_) {
    if (filter(i)) {
      switcher(i);
      result++;
    }
  }
  return result;
}

int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
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

bool Storage::readFromFile(const char* fpath) {
  ;
}

bool Storage::writeToFile(const char* fpath) {
  ;
}
