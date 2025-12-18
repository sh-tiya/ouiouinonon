#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <mariadb/conncpp.hpp>
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    string a;
    string b;
    cout << "Entrez votre login :" << endl;
    cin >> a;
    cout << "Entrez votre password :" << endl;
    cin >> b;
    try {
        //Connexion à la base
        sql::Driver* driver;
        sql::Connection* conn;
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;
        driver = sql::mariadb::get_driver_instance();
        sql::SQLString url("jdbc:mariadb://172.20.30.253:3306/a.moustakima");
        sql::Properties properties({{"user", "a.moustakima"}, {"password", "a.moustakima"}});
        conn = driver->connect(url, properties);
        if (conn) {
            cout << "Connexion MariaDB reussie!" << endl;
        }
        else if (!conn) {
            cout << "Connexion MariaDB error!" << endl;
        }
        //Préparation de la requête paramétrée
        pstmt = conn->prepareStatement("SELECT id, mdp FROM etudiant where nom=? AND date_naissance=?");
        pstmt->setString(1, a);
        pstmt->setString(2, b);
        //Exécution
        res = pstmt->executeQuery();
        //Lecture des résultats
        while (res->next()) {
            if (res->getString("COUNT(*)")=="1") {
                cout << "bienvenue" << endl;
            }
            else if (res->getString("COUNT(*)")=="0")
            {
                cout << "enfinnnnn pas bienvenue" << endl;
            }



        }

        //Libération manuelle de la mémoire
        delete res;
        delete pstmt;
        delete conn;
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur MariaDB : " << e.what() << std::endl;
        std::cerr << "Code erreur : " << e.getErrorCode() << std::endl;
        std::cerr << "État SQL : " << e.getSQLState() << std::endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
