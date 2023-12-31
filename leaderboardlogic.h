#ifndef LEADERBOARDLOGIC_H
#define LEADERBOARDLOGIC_H

#include <QVector>
#include <QPair>

class LeaderBoardLogic // 设计为单例模式
{
public:

    ~LeaderBoardLogic() {
        updateLeaderBoardFile();
    }

    static LeaderBoardLogic& getInstance() {
        static LeaderBoardLogic instance;
        return instance;
    }

    QVector<QPair<QString, int>> getLeaderBoard() const{return leaderBoard;}
    QString getLeaderBoardString() const;

    void insertIntoLeaderBoard(const QString& name, int score, int rank);
    int rankInLeaderBoard(int score) const;
    void updateLeaderBoardFile();

private:
    LeaderBoardLogic();
    LeaderBoardLogic(const LeaderBoardLogic&) = delete;
    LeaderBoardLogic(LeaderBoardLogic&&) = delete;
    LeaderBoardLogic& operator=(const LeaderBoardLogic&) = delete;
    LeaderBoardLogic& operator=(LeaderBoardLogic&&) = delete;

    void initLeaderBoard();

    QVector<QPair<QString, int>> leaderBoard;
};

#endif // LEADERBOARDLOGIC_H
