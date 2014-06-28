#include "AgendaService.h"

AgendaService::AgendaService() {
  storage_ = Storage::GetInstance();
}

AgendaService::~AgendaService() {
  delete storage_;
}

bool AgendaService::
userLogIn(std::string userName, std::string password) {
  return !storage_->QueryUser(
    [&](const User & user) {
      return user.getName() == userName && user.getPassword() == password;
    }
  ).empty();
}

bool AgendaService::
userRegister(std::string userName, std::string password,
             std::string email, std::string phone) {
  User newUser(userName, password, email, phone);

  if (storage_->QueryUser(
        [&](const User & user) { return user.getName() == userName; }
      ).empty()) {
    storage_->CreateUser(newUser);
    return true;
  }

  return false;
}

// a user can only delete itself
bool AgendaService::deleteUser(std::string userName, std::string password) {
  if (!listAllMeetings(userName).empty()) {
    return false;
  }

  return storage_->DeleteUser(
      [&](const User & user) {
        return user.getName() == userName && user.getPassword() == password;
      }
    ) > 0;
}

std::list<User> AgendaService::listAllUsers(void) {
  return storage_->QueryUser(
    [](const User & user) { return true; }
  );
}

bool AgendaService::
createMeeting(std::string userName, std::string title,
              std::string participator,
              std::string startDate, std::string endDate) {
  Date stime = Date::stringToDate(startDate);
  Date etime = Date::stringToDate(endDate);
  bool userNotFound = storage_->QueryUser(
        [&](const User & user) {
          return user.getName() == userName;
        }
       ).empty();
  bool participatorNotFound = storage_->QueryUser(
        [&](const User & user) {
          return user.getName() == participator;
        }
       ).empty();


  // failed if there is only one person in the meeting
  if (userName == participator)
    return false;

  // failed if the sponsor or the query user doesn't exists
  if (userNotFound || participatorNotFound)
    return false;

  // failed if the times are not valid
  if (!(Date::isValid(stime) && Date::isValid(etime) && stime <= etime))
    return false;

  // failed if sponsor or participator is not available
  if (!(meetingQuery(userName, startDate, endDate).empty()
        && meetingQuery(participator, startDate, endDate).empty()))
    return false;

  // failed if the meeting exists
  if (!meetingQuery(title).empty())
    return false;

  Meeting newMeeting(userName, participator, Date::stringToDate(startDate),
                     Date::stringToDate(endDate), title);
  storage_->CreateMeeting(newMeeting);
  return true;
}

std::list<Meeting> AgendaService::meetingQuery(std::string title) {
  return storage_->QueryMeeting(
    [&](const Meeting & meeting) {
      return meeting.getTitle() == title;
    }
  );
}

std::list<Meeting> AgendaService::
meetingQuery(std::string userName, std::string startDate,
             std::string endDate) {
  Date stime = Date::stringToDate(startDate);
  Date etime = Date::stringToDate(endDate);

  // failed if the times are not valid
  if (!(Date::isValid(stime) && Date::isValid(etime) && stime <= etime))
    return std::list<Meeting>();

  // failed if the user doesn't exists
  if (storage_->QueryUser(
        [&](const User & user) {
          return user.getName() == userName;
        }
       ).empty()) {
    return std::list<Meeting>();
  }

  return storage_->QueryMeeting(
    [&](const Meeting & meeting) {
      if (meeting.getSponsor() == userName || meeting.getParticipator() == userName) {
        if (meeting.getStartDate() >= stime && meeting.getEndDate() <= etime)
          return true;
        else if (meeting.getStartDate() <= etime && meeting.getEndDate() >= etime)
          return true;
        else if (meeting.getStartDate() <= stime && meeting.getEndDate() >= stime)
          return true;
        else
          return false;
      }
      return false;
    }
  );
}

std::list<Meeting> AgendaService::
listAllMeetings(std::string userName) {
  return storage_->QueryMeeting(
    [&](const Meeting & meeting) {
      return (meeting.getSponsor() == userName
              || meeting.getParticipator() == userName);
    }
  );
}

std::list<Meeting> AgendaService::
listAllSponsorMeetings(std::string userName) {
  return storage_->QueryMeeting(
    [&](const Meeting & meeting) {
      return meeting.getSponsor() == userName;
    }
  );
}

std::list<Meeting> AgendaService::
listAllParticipateMeetings(std::string userName) {
  return storage_->QueryMeeting(
    [&](const Meeting & meeting) {
      return meeting.getParticipator() == userName;
    }
  );
}

bool AgendaService::
deleteMeeting(std::string userName, std::string title) {
  return storage_->DeleteMeeting(
    [&](const Meeting & meeting) {
      return meeting.getSponsor() == userName && meeting.getTitle() == title;
    }
  ) > 0;
}

bool AgendaService::deleteAllMeetings(std::string userName) {
  return storage_->DeleteMeeting(
    [&](const Meeting & meeting) {
      return meeting.getSponsor() == userName;
    }
  ) > 0;
}

void AgendaService::startAgenda(void) {
  storage_->Sync();
}

void AgendaService::quitAgenda(void) {
  storage_->Sync();
}