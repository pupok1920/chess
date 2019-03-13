#ifndef __NJDFKVFJNKDVNDFJKVNDLFVNDKVNDFVNDFVNKD__
#define __NJDFKVFJNKDVNDFJKVNDLFVNDKVNDFVNDFVNKD__
#include <QFile>
#include <QFileDevice>
#include <QFileInfo>
#include <QErrorMessage>
#include <QTextStream>
#include <QPair>
#include <QVector>
#include <QDebug>

class FileHandler: public QObject {

  FileHandler(QObject *parent = nullptr);
  ~FileHandler();

public:
  static bool save(const QString &fileName, const QVector<QPair<int, int> > &moves);
  static bool load(const QString &fileName, QVector<QPair<int, int> > &moves);

private:
  static QString cutFileName(const QString &fileName);
  static bool isFileValid(QFile &file);
};
#endif // __NJDFKVFJNKDVNDFJKVNDLFVNDKVNDFVNDFVNKD__
