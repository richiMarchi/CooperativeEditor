#include "Login.h"

Login::Login(QWidget *parent) : QMainWindow(parent) {

  this->setWindowTitle("CooperativeEditor - Login");
  this->setFixedSize(this->minimumSize());

  auto mainWidget = new QWidget(this);
  auto layout = new QGridLayout(mainWidget);

  setCentralWidget(mainWidget);
  mainWidget->setLayout(layout);

  auto loginBox = new QGroupBox("Insert your Personal Data:", mainWidget);
  loginBox->setLayout(new QVBoxLayout());
  layout->addWidget(loginBox, 1, 0, 1, 2);

  auto usernameLabel = new QLabel("Username:", loginBox);
  loginBox->layout()->addWidget(usernameLabel);

  usernameTextField = new QLineEdit(loginBox);
  loginBox->layout()->addWidget(usernameTextField);

  auto passwordLabel = new QLabel("Password:", loginBox);
  loginBox->layout()->addWidget(passwordLabel);

  passwordTextField = new QLineEdit(loginBox);
  passwordTextField->setEchoMode(passwordTextField->Password);
  passwordTextField->setStyleSheet("lineedit-password-character: 42");
  loginBox->layout()->addWidget(passwordTextField);

  auto buttonEnter = new QPushButton("Log In", loginBox);
  buttonEnter->setAutoDefault(true);
  loginBox->layout()->addWidget(buttonEnter);

  auto registerBox = new QGroupBox("New to the Editor? Create an account",
                              mainWidget);
  registerBox->setLayout(new QVBoxLayout());
  layout->addWidget(registerBox, 4, 0, 1, 2);

  auto buttonRegister = new QPushButton("Sign Up", registerBox);
  buttonRegister->setAutoDefault(true);
  registerBox->layout()->addWidget(buttonRegister);

  auto buttonExit = new QPushButton("Exit", mainWidget);
  buttonExit->setAutoDefault(true);
  layout->addWidget(buttonExit, 5, 0, 1, 2);


  buttonExit->setFocus();

  QObject::connect(buttonExit, &QAbstractButton::clicked, this,
                   [this]() {
                       int result = QMessageBox::question(this, "CooperativeEditor", "Are you sure you want to exit?", QMessageBox::Yes, QMessageBox::No);

                       if(result == QMessageBox::Yes) {
                         this->close();
                       }
                   });

  QObject::connect(buttonEnter, &QAbstractButton::clicked, this,
                   [this]() {
                       if (!usernameTextField->text().isEmpty() &&
                           !passwordTextField->text().isEmpty()) {
                         emit loginRequest(User(usernameTextField->text(),
                                           passwordTextField->text()));
                       } else {
                         QMessageBox::information(this, "CooperativeEditor", "Please insert username and password.");
                       }
                   });

  QObject::connect(buttonRegister, &QAbstractButton::clicked, this,
                   [this]() {
                       emit signUp();
                       this->hide();
                   });
}
