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

    Q_PROPERTY(int nRows READ rowCount NOTIFY dataReady)
    Q_PROPERTY(int nColumns READ columnCount NOTIFY dataReady)
    /**
     * Display the change of account and whose move
     */
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


    GameBoard(QObject* pobj = 0);
    ~GameBoard();
    /**
     * @brief Returns the number of rows in the model
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    /**
     * @brief Returns the number of columns in the model
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const override; ////////

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int,QByteArray> roleNames() const override;
    bool setData(const QModelIndex& index, const QVariant& value, int nRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /**
     * getters
     */
    int firstPlayerAccount() const;
    int secondPlayerAccount() const;
    int state() const;

    /**
     * Methods for communicating with qml
     */
    Q_INVOKABLE void commit(int row, int column);
    /**
     * @brief boardCreation Sends data to create a board
     * @param size Board size
     */
    Q_INVOKABLE void boardCreation(int size, QColor colorPlayer1, QColor colorPlayer2, int numberOfColors);
    Q_INVOKABLE void stepDown();
private:
    enum WhoseMove
    {
        FIRST_PLAYER,
        SECOND_PLAYER
    };

    /** Pointer to data */
    Data *m_pDataClass;
    /** Point to the class that records the moves */
    MoveRecorder *m_pRecorder;

    /** Player colors */
    std::vector<QColor> m_playersColors;
    /** Players account */
    std::vector<int> m_playersAccount;

    int m_nRows;
    int m_nColumns;

    /**  */
    WhoseMove m_state;
    /**  */
    QColor color;

    bool helper(int x, int y);

    /**
     * @brief Checks if the data is ready
     */
    bool dataReadyForWork() const;

    QList<QModelIndex> forCheck(int x, int y);
    void takeAll(const QModelIndex&, bool isFirstEntering);
    void changeFieldOwner();

    QList<QModelIndex> pretendent;

    int m_firstPlayerAccount;
    int m_secondPlayerAccount;

    bool isFirstEntering = true;

    std::vector<Recorder> vectorToReverse;
    void addingAreasToPlayerTerritories(size_t row, size_t column, WhoseMove move);

signals:
    void gameEndSignal();
    void accountChanged();
    void playerChanged();
    void dataReady();
//    void animation(QColor color1, QColor color2);
};

#endif // GAMEBOARD_H
