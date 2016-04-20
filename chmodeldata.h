#ifndef CHMODELDATA
#define CHMODELDATA
#include <QAbstractItemModel>

#endif // CHMODELDATA

class ChModelData: public QAbstractItemModel
{
  Q_OBJECT

public:

  ChModelData();
 ~ChModelData();

  int rowCount(const QModelIndex & parent) const override;
  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;
}
