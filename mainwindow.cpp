#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sha256.h"
#include "MapEncrypt.h"
#include "RSA.h"
#include <sstream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->SHA256, &QRadioButton::clicked, this, &MainWindow::onRadioButtonClicked);
    connect(ui->MAP, &QRadioButton::clicked, this, &MainWindow::onRadioButtonClicked);
    connect(ui->RSA, &QRadioButton::clicked, this, &MainWindow::onRadioButtonClicked);
    connect(ui->DEMAP,&QRadioButton::clicked,this,&MainWindow::onRadioButtonClicked);
    connect(ui->DERSA,&QRadioButton::clicked,this, &MainWindow::onRadioButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}
std::string  SHA256_run(std::string word) {
    sha256 words;
    words.update(word);
    return words.final();
}
//@detail 映射加密函数
std::string Encrypt_run(std::string word,int shift) {
    MapEncrypt words(word, shift);
    words.encrypt();
    return words.show();
}
//@detail 映射函数解密
std::string decrypt_run(std::string word) {
    MapEncrypt words(word,7);
    words.decrypt();
    return words.show();
}
//@detail RSA加密函数
std::string rsa_run(std::string plaintext) {
    RSA rsa;
    rsa.genKey(17, 19);
    std::vector<int> ciphertext = rsa.encrypt(plaintext);
    std::string res;
    for (int num : ciphertext) {
        res+=" "+std::to_string(num);
    }
    return res;
}
//RSA 解密函数
std::string de_rsa(const std::string& ciphertext_str) {
    std::vector<int> ciphertext;
    std::stringstream ss(ciphertext_str);  // 使用stringstream来分割字符串
    int num;
    while (ss >> num) {  // 从stringstream中按空格分割读取整数
        ciphertext.push_back(num);
    }

    RSA rsa;
    rsa.genKey(17, 19);
    std::string decryptedText = rsa.decrypt(ciphertext);
    return decryptedText;
}

void MainWindow::onRadioButtonClicked()
{
    if (ui->SHA256->isChecked()) {
        QString inputText = ui->lineEdit->text();
        if (inputText.isEmpty()) {
            ui->label->setText("你还没有输入任何内容哦，请输入后再点击提交。");
        } else {
            std::string input = inputText.toStdString();
            QString res = QString::fromStdString(SHA256_run(input));
            QString encryptedText = "SHA256加密结果: " + res;
            ui->label->setText(encryptedText);
        }
    } else if (ui->MAP->isChecked()) {
        QString inputText = ui->lineEdit->text();
        if (inputText.isEmpty()) {
            ui->label->setText("你还没有输入任何内容哦，请输入后再点击提交。");
        } else {
            std::string input = inputText.toStdString();
            QString res = QString::fromStdString(Encrypt_run(input,7));
            QString encryptedText = "MAP映射加密结果: " + res;
            ui->label->setText(encryptedText);
        }
    } else if (ui->RSA->isChecked()) {
        QString inputText = ui->lineEdit->text();
        if (inputText.isEmpty()) {
            ui->label->setText("你还没有输入任何内容哦，请输入后再点击提交。");
        } else {
            std::string input = inputText.toStdString();
            QString res = QString::fromStdString(rsa_run(input));
            QString encryptedText = "RSA加密结果: " + res;
            ui->label->setText(encryptedText);
        }
    }else if(ui->DERSA->isChecked()){
        QString ciperText = ui->lineEdit2->text();
        if(ciperText.isEmpty()){
            ui->label_2->setText("你还没有输入任何内容哦，请输入后再点击提交。");
        }else{
            std::string input = ciperText.toStdString();
            QString res =  QString::fromStdString(Encrypt_run(input,17));
            QString plainText = "MAP解密结果: "+ res;
            ui->label_2->setText(plainText);
        }
    }else if(ui->DEMAP->isChecked()){
        QString ciperText = ui->lineEdit2->text();
        if(ciperText.isEmpty()){
            ui->label_2->setText("你还没有输入任何内容哦，请输入后再点击提交。");
        }else{
            std::string input = ciperText.toStdString();
            QString res =  QString::fromStdString(decrypt_run(input));
            QString plainText = "MAP解密结果: "+ res;
            ui->label_2->setText(plainText);
        }
    }
}
