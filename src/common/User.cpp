#include "User.h"

#include <utility>

User::User(QString icon, QString username, QString name,
           QString surname, QString email, QString password) : icon(
        std::move(icon)),
                                                               username(
                                                                       std::move(
                                                                               username)),
                                                               name(std::move(
                                                                       name)),
                                                               password(
                                                                       std::move(
                                                                               password)),
                                                               surname(std::move(
                                                                       surname)),
                                                               email(std::move(
                                                                       email)) {
}


User::User(QString icon, QString username, QString name, QString surname,
           QString email) : User(std::move(icon), std::move(username),
                                 std::move(name), std::move(surname),
                                 std::move(email),
                                 {}) {
}

User::User(QString username, QString password) : User({}, std::move(username),
                                                      {}, {}, {},
                                                      std::move(password)) {
}

QString &User::getUsername() {
  return username;
}

QString &User::getName() {
  return name;
}

QString &User::getSurname() {
  return surname;
}

QString &User::getEmail() {
  return email;
}

QString &User::getIcon() {
  return icon;
}

QString &User::getPassword() {
  return password;
}

QDataStream &operator<<(QDataStream &stream, const User &val) {
  stream << val.username << val.email << val.name << val.surname << val.icon
         << val.password;
  return stream;
}

QDataStream &operator>>(QDataStream &stream, User &val) {
  stream >> val.username >> val.email >> val.name >> val.surname >> val.icon
         >> val.password;
  return stream;
}

std::string User::toStdString(int level) {
  return std::string(std::string(level, '\t') + "User{\n" +
                     std::string(level + 1, '\t') + "username: " +
                     username.toStdString() + "\n" +
                     std::string(level + 1, '\t') + "password: " +
                     password.toStdString() + "\n" +
                     std::string(level + 1, '\t') + "name: " +
                     name.toStdString() + "\n" +
                     std::string(level + 1, '\t') + "surname: " +
                     surname.toStdString() + "\n" +
                     std::string(level + 1, '\t') + "email: " +
                     email.toStdString() + "\n" +
                     std::string(level + 1, '\t') + "icon: " +
                     icon.toStdString() + "\n" + std::string(level + 1, '\t') +
                     "}");
}