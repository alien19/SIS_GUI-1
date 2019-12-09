#include "student.h"
#include "sqliteclass.h"
#include "globalDbObject.h"

/*static QString students_table = "students";
static QStringList students_columns = {"first_name","last_name", "gendre", "picture",
                                "birth_date", "address", "college_id", "academic_year", "department"};
*/
Student::Student() : Person()
{
    this-> academic_year = "0";
    this->department = "";
}

Student::Student(QString first_name, QString last_name, QString gendre, QString picture, QString birth_date, QString address, QString college_id,
                 QString academic_year, QString department) : Person(first_name, last_name, gendre, picture, birth_date, address, college_id) {
    this-> academic_year = academic_year;
    this->department = department;
}

void Student::setAcademicYear(QString academic_year){
    this->academic_year = academic_year;
}

void Student::setDepartment(QString department) {
    this->department = department;
}

QString Student::getDepartment() {
    return this->department;
}

QString Student::getAcademicYear(){
    return this-> academic_year;
}

QVector<Course> Student::getCourses() {
    return this->courses;
}

void Student::addCourse(QString course_name) {
    int index = -1;
    for(int i = 0; i < this->courses.size(); i++) {
        if(this->courses[0].getName() == course_name) {
            index = i;
            break;
        }
    }
    if(index == -1)
        this->courses.push_back(Course(course_name));
}

void Student::deleteCourse(QString course_name) {
    int index = -1;
    for(int i = 0; i < this->courses.size(); i++) {
        if(this->courses[0].getName() == course_name) {
            index = i;
            break;
        }
    }
    if(index != -1)
        this->courses.remove(index);
}

QVector<Student> Student::all() {
    QSqlQuery query;
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbPath = QDir::currentPath();

    dbPath += "/" + QString("db.sqlite");

    qDebug() << dbPath;

    db.setDatabaseName(dbPath);

    if(!db.open()){
        qDebug() << "Problem while opening the database";
    }


    QVector<Student> students;
    Student temp;
    query.exec("SELECT * FROM students");
    QSqlQuery query1;
    while(query.next()) {
        long long id = query.value(0).toLongLong();
        QString first_name = query.value(1).toString();
        QString last_name = query.value(2).toString();
        QString gendre = query.value(3).toString();
        QString picture = query.value(4).toString();
        QString birth_date = query.value(5).toString();
        QString address = query.value(6).toString();
        QString college_id = query.value(7).toString();
        QString academic_year = query.value(8).toString();
        QString department = query.value(9).toString();


        Student temp(first_name, last_name, gendre, picture, birth_date, address, college_id, academic_year, department);
        temp.setId(id);
        temp.setIsSaved(true);

        query1.exec("SELECT * FROM courses_students WHERE course_id = " + QString::number(id));
        while(query1.next()) {
            temp.addCourse(Course::find(query1.value(1).toLongLong()).getName());
        }
        students.push_back(temp);
    }


    db.close();
    return students;
}

bool Student::save(){
    SQLiteDb.sql_select("*", students_table, "id = " + QString::number(getId()));
    QSqlQuery query = SQLiteDb.sql_getQuery();
    if(query.next()){
        return true;
    }
    QStringList values = {getFirstName(),  getLastName(), getGendre(), getPicture(),
                          getBirthDate(), getAddress(), getCollegeId(), getAcademicYear(),  getDepartment()};
    SQLiteDb.sql_insert(students_table, students_columns, values);
    return false;
}

void Student::delete1(){
    SQLiteDb.sql_delete(students_table, "ID = " + QString::number(getId()));
}

Student Student::find(long long id) {
    QSqlQuery query;
    QSqlDatabase db;

    db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbPath = QDir::currentPath();

    dbPath += "/" + QString("db.sqlite");

    qDebug() << dbPath;

    db.setDatabaseName(dbPath);

    if(!db.open()){
        qDebug() << "Problem while opening the database";
    }

    query.exec("SELECT * FROM students");
    QSqlQuery query1;
    query.next();
    QString first_name = query.value(1).toString();
    QString last_name = query.value(2).toString();
    QString gendre = query.value(3).toString();
    QString picture = query.value(4).toString();
    QString birth_date = query.value(5).toString();
    QString address = query.value(6).toString();
    QString college_id = query.value(7).toString();
    QString academic_year = query.value(8).toString();
    QString department = query.value(9).toString();

    Student student(first_name, last_name, gendre, picture, birth_date, address, college_id, academic_year, department);
    student.setId(id);
    student.setIsSaved(true);

    query1.exec("SELECT * FROM courses_students WHERE course_id = " + QString::number(id));
    while(query1.next()) {
        student.addCourse(Course::find(query1.value(1).toLongLong()).getName());
    }


    db.close();
    return student;
}

QVector<Student> Student::where(QString column, QString value){
    SQLiteDb.sql_select("*", students_table, column + " = " +  value);
    QSqlQuery query = SQLiteDb.sql_getQuery();
    QVector<Student> students;
    while (query.next()) {
        int id = query.value(0).toInt();
        students.push_back(find(id));
    }
    return students;
}





