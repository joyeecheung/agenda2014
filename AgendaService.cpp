#include "AgendaService.h"

AgendaService::AgendaService()
{
  storage_ = Storage::getInstance();
}

AgendaService::~AgendaService()
{
  delete storage_;
}

bool AgendaService::
userLogIn(std::string userName, std::string password)
{
  
}

bool AgendaService::
userRegister(std::string userName, std::string password,
                  std::string email, std::string phone)
{

}

std::list<User> AgendaService::listAllUsers(void)
{
    storage_->QueryUser(
        [](const User& user) { return true; }
    );
}

bool AgendaService::
createMeeting(std::string userName, std::string title,
                   std::string participator,
                   std::string startDate, std::string endDate)
{

}

Meeting* AgendaService::meetingQuery(std::string title)
{

}

std::list<Meeting> AgendaService::
meetingQuery(std::string userName, std::string startDate,
                                std::string endDate)
{

}

std::list<Meeting> AgendaService::
listAllMeetings(std::string userName)
{

}

std::list<Meeting> AgendaService::
listAllSponsorMeetings(std::string userName)
{

}

std::list<Meeting> AgendaService::
listAllParticipateMeetings(std::string userName)
{

}

bool AgendaService::
deleteMeeting(std::string userName, std::string title)
{

}

bool AgendaService::deleteAllMeetings(std::string userName)
{

}

void AgendaService::startAgenda(void)
{

}

void AgendaService::quitAgenda(void)
{

}