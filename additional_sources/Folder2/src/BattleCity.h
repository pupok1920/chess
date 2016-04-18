#pragma once

#include <QAbstractListModel>
#include <memory>

class QKeyEvent;

class BattleCity: public QAbstractListModel
{
  Q_OBJECT

public:

  BattleCity();
 ~BattleCity();

  int rowCount(const QModelIndex & parent) const override;
  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

public:

  void event(QKeyEvent &);

  Q_INVOKABLE void start();

  Q_PROPERTY(int worldSize READ worldSize CONSTANT);
  int worldSize() const;

  Q_PROPERTY(bool gameOver READ gameOver NOTIFY gameOverChanged);
  bool gameOver() const;

  Q_PROPERTY(int enemyLeft READ enemyLeft NOTIFY enemyLeftChanged);
  int enemyLeft() const;

signals:

  void enemyLeftChanged();
  void gameOverChanged();

private slots:

  void tickUpdate();

private:

  void publishModel();

  class Implementation;
  std::unique_ptr<Implementation> impl;

  template<typename> friend class ListPublisher;
};

