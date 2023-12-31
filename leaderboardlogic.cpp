#include "leaderboardlogic.h"
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <string>
#include <QDebug>

LeaderBoardLogic::LeaderBoardLogic()
{
    try {
        initLeaderBoard();
    } catch (const std::exception& e) {
        leaderBoard.clear();
        QMessageBox::critical(nullptr, "error", "Fail to read leader board from file");
    }

}

QString LeaderBoardLogic::getLeaderBoardString() const {
    QString leaderBoardString;
    for (auto element : leaderBoard) {
        leaderBoardString += element.first + " : " + QString::number(element.second) + "\n";
    }
    return leaderBoardString;
}


void LeaderBoardLogic::initLeaderBoard() {
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(dataPath);
    if (!dir.exists()) {
        dir.mkpath("."); // 创建目录
    }
    QString filePath = dataPath + "/leaderboard.txt";
    QFile file(filePath);
//    qDebug() << filePath;

    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream stream(&file);
        if (file.size() == 0) { // 如果文件是新创建的
            // 写入一些初始数据
            QPair<QString, int> init_data("Yell0wish", 114514);
            leaderBoard.clear(); // 防止有脏数据
            leaderBoard.push_back(init_data);
            stream << "Yell0wish:114514" << endl;
        } else {
            // 读取现有数据
            leaderBoard.clear();
            while(!stream.atEnd() && leaderBoard.size() <= 5) { // 只取前5个
                QStringList line = stream.readLine().split(':');
                if (line.size() != 2) {
                    throw std::runtime_error("Line format is incorrect");
                }
                bool transResult;
                int score = line[1].toInt(&transResult);
                if (!transResult) {
                    throw std::runtime_error("Cannot invert to integer");
                }
                QPair<QString, int> temp(line[0], score);
                leaderBoard.push_back(temp);
            }
        }
        file.close();
    } else {
        throw std::runtime_error("Unable to open file: " + file.errorString().toStdString());
    }
}

void LeaderBoardLogic::insertIntoLeaderBoard(const QString& name, int score, int rank) {
    // 排名从0开始
    if (rank < 0 || rank >= 5 || rank > leaderBoard.size()) {
        return;
    }
    // 排行榜已满
    if (leaderBoard.size() >= 5) {
        leaderBoard.pop_back();
    }
    leaderBoard.insert(leaderBoard.begin() + rank, QPair<QString, int>(name, score));
}

int LeaderBoardLogic::rankInLeaderBoard(int score) const {
    int rank = -1;
    for (int i = 0; i < leaderBoard.size(); i++) {
        if (score >= leaderBoard[i].second) {
            rank = i;
            break;
        }
    }
    if (rank == -1 && leaderBoard.size() < 5) {
        rank = leaderBoard.size();
    }
    return rank;
}

void LeaderBoardLogic::updateLeaderBoardFile() {
    QString dataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(dataPath);
    if (!dir.exists()) {
        dir.mkpath("."); // 创建目录
    }
    QString filePath = dataPath + "/leaderboard.txt";
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        for (auto element : leaderBoard) {
            stream << element.first << ":" << element.second << "\n";
        }
        file.close();
    } else {
        throw std::runtime_error("Unable to open file: " + file.errorString().toStdString());
    }
}
