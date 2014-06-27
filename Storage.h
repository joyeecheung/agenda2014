#ifndef AGENDA_STORAGE_H
#define AGENDA_STORAGE_H

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&); \
  void operator=(const TypeName&)

#include <list>
#include <string>
#include <functional>

#include "User.h"
#include "Meeting.h"

class Storage {
  private:
  	static Storage* instance_;
	DISALLOW_COPY_AND_ASSIGN(Storage);
    Storage();
    // storage structure, or you have better structures e.g. balanced tree
    std::list<User> userList_;
    std::list<Meeting> meetingList_;
	// File IO
    bool ReadFromFile(char *fpath);
	bool WriteToFile(char *fpath);
	// log [choice]
	// TODO:...
  public:
    // singleton
    Storage& GetInstance(void);
	~Storage();
	// CRUD for User & Meeting using C++11 Lambda Expressions
	void CreateUser(const User&);
	std::list<User> QueryUser(std::function<bool(const User&)> filter); // return found users
	int UpdateUser(std::function<bool(const User&)> filter, std::function<void(User&)> switcher); // return the number of updated users
	int DeleteUser(std::function<bool(const User&)> filter); // return the number of deleted users
	void CreateMeeting(const Meeting&);
	std::list<Meeting> QueryMeeting(std::function<bool(const Meeting&)> filter); // return found meetings
	int UpdateMeeting(std::function<bool(const Meeting&)> filter, std::function<void(Meeting&)> switcher); // return the number of updated meetings
	int DeleteMeeting(std::function<bool(const Meeting&)> filter); // return the number of deleted meetings
	// File IO
	bool Sync(void);
};

#endif