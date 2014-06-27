#include "Storage.h"

Storage::DISALLOW_COPY_AND_ASSIGN(Storage)
{

}

Storage::Storage()
{

}

// File IO
bool Storage::ReadFromFile(char *fpath)
{

}

bool Storage::WriteToFile(char *fpath)
{

}

// singleton
Storage& Storage::GetInstance(void)
{

}

Storage::~Storage()
{

}

// CRUD for User & Meeting using C++11 Lambda Expressions
void Storage::CreateUser(const User&)
{

}

std::list<User> Storage::
QueryUser(std::function<Storage::
bool(const User&)> filter)
{

}

int Storage::
UpdateUser(std::function<Storage::
bool(const User&)> filter, std::function<Storage::
void(User&)> switcher)
{

}

int Storage::
DeleteUser(std::function<Storage::
bool(const User&)> filter)
{

}

void Storage::CreateMeeting(const Meeting&)
{

}

std::list<Meeting> Storage::
QueryMeeting(std::function<Storage::
bool(const Meeting&)> filter)
{

}

int Storage::
UpdateMeeting(std::function<Storage::
bool(const Meeting&)> filter, std::function<Storage::
void(Meeting&)> switcher)
{

}

int Storage::
DeleteMeeting(std::function<Storage::
bool(const Meeting&)> filter)
{

}

// File IO
bool Storage::Sync(void)
{

}

