#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    main = new QWidget();
    _main = new QWidget();
    mainLayout = new QVBoxLayout();
    _mainLayout = new QHBoxLayout();
    loginWidget = new Login(this);

    mainLayout->addWidget(new QWidget);
    mainLayout->addWidget(_main);
    mainLayout->addWidget(new QWidget);
    main->setLayout(mainLayout);

    setWidget(loginWidget);

    this->setCentralWidget(main);
    this->loadStyles();

    connect(loginWidget, &Login::Register,this,&MainWindow::setSignupWidget);
    connect(loginWidget, &Login::LoginAcc, this, &MainWindow::login);
}

void MainWindow::loadStyles(){
    QFile css("../SIS_GUI/theme.css");
    css.open(QFile::ReadOnly);
    QString Styles = css.readAll();
    this->setStyleSheet(Styles);
}

void MainWindow::setWidget(QWidget *w){
    delete _mainLayout;
    _mainLayout = new QHBoxLayout();
    _mainLayout->addWidget(new QWidget);
    _mainLayout->addWidget(w);
    _mainLayout->addWidget(new QWidget);
    _main->setLayout(_mainLayout);
}

void MainWindow::setSignupWidget(){
    regWidget = new Register();
    delete loginWidget;
    setWidget(regWidget);
    connect(regWidget,&Register::back,this,&MainWindow::setLoginWidget);
}

void MainWindow::setLoginWidget(){
    loginWidget = new Login();
    delete regWidget;
    setWidget(loginWidget);
    connect(loginWidget, &Login::Register,this,&MainWindow::setSignupWidget);
    connect(loginWidget, &Login::LoginAcc, this, &MainWindow::login);
}

void MainWindow::adminSignout(){
    loginWidget = new Login();
//    delete studentDashboard;
    delete adminDashboard;
    setWidget(loginWidget);
    connect(loginWidget, &Login::Register,this,&MainWindow::setSignupWidget);
    connect(loginWidget, &Login::LoginAcc, this, &MainWindow::login);
}

void MainWindow::login(QString usr, QString pass){
    // TODO check here for usr name and passowrd
//    studentDashboard = new Dashboard();
    adminDashboard = new AdminDashboard();
    delete loginWidget;
//    setWidget(studentDashboard);
    setWidget(adminDashboard);
    connect(adminDashboard, &AdminDashboard::Signout, this, &MainWindow::adminSignout);
    connect(adminDashboard, &AdminDashboard::addStudent, this, &MainWindow::adminAddStudent);
//    connect(studentDashboard,&Dashboard::Signout,this,&MainWindow::Signout);
}

void MainWindow::adminAddStudent(){
    regWidget = new Register();
    delete adminDashboard;
    setWidget(regWidget);
    connect(regWidget,&Register::back,this,&MainWindow::adminDash);
}

void MainWindow::adminDash(){
    adminDashboard = new AdminDashboard();
    delete regWidget;
//    setWidget(studentDashboard);
    setWidget(adminDashboard);
    connect(adminDashboard, &AdminDashboard::Signout, this, &MainWindow::adminSignout);
    connect(adminDashboard, &AdminDashboard::addStudent, this, &MainWindow::adminAddStudent);
//    connect(studentDashboard,&Dashboard::Signout,this,&MainWindow::Signout);
}

void MainWindow::Signout(){
    loginWidget = new Login();
//    delete studentDashboard;
    delete adminDashboard;
    setWidget(loginWidget);
    connect(loginWidget, &Login::Register,this,&MainWindow::setSignupWidget);
    connect(loginWidget, &Login::LoginAcc, this, &MainWindow::login);
}

MainWindow::~MainWindow(){
}

