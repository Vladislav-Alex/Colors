#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QAbstractTableModel>
#include <vector>

#include "data.h"
#include "moverecorder.h"
#include "timer.h"

class GameBoard : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(int nRows READ nRows NOTIFY dataReady)
    Q_PROPERTY(int nColumns READ nColumns NOTIFY dataReady)
    Q_PROPERTY(int firstPlayerAccount READ firstPlayerAccount NOTIFY accountChanged)
    Q_PROPERTY(int secondPlayerAccount READ secondPlayerAccount NOTIFY accountChanged)
    Q_PROPERTY(int state READ state NOTIFY playerChanged)
    Q_ENUMS(MyRoles)

public:
    enum MyRoles
    {
        COLOR_ROLE = Qt::UserRole + 1,
        OWNER_ROLE
    };

    static constexpr size_t defaultPuzzleDimension {0};
//    static constexpr size_t colorCount {4};
    GameBoard(int nRows = defaultPuzzleDimension, int nColumns = defaultPuzzleDimension, QObject* pobj = 0);
    ~GameBoard();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex&) const override; ////////
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    int nColumns() const;
    int nRows() const;
    QHash<int,QByteArray> roleNames() const override;
    bool setData(const QModelIndex& index, const QVariant& value, int nRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    Q_INVOKABLE void commit(int row, int column);
    Q_INVOKABLE void test(int size, QColor colorPlayer1, QColor colorPlayer2, int numberOfColors);
    Q_INVOKABLE void stepDown();


    int firstPlayerAccount() const;
    int secondPlayerAccount() const;
    int state() const;

private:
    Data *m_pDataClass;
    MoveRecorder *m_pRecorder;

    std::vector<QColor> m_playersColors;
    std::vector<int> m_playersAccount;

    int m_nRows;
    int m_nColumns;

    enum WhoseMove
    {
        FIRST_PLAYER,
        SECOND_PLAYER
    };

    WhoseMove m_state;
    QColor color;

    bool helper(int x, int y);

    bool dataReadyForWork() const;

    QList<QModelIndex> forCheck(int x, int y);
    void takeAll(const QModelIndex&, bool isFirstEntering);
    void changeFieldOwner();

    QList<QModelIndex> pretendent;

    int m_firstPlayerAccount;
    int m_secondPlayerAccount;

    bool isFirstEntering = true;

    std::vector<Recorder> vectorToReverse;


signals:
    void someSignal();
    void accountChanged();
    void playerChanged();
    void dataReady();
    void animation(QColor color1, QColor color2);
};

#endif // GAMEBOARD_H
