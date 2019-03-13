#include "filehandler.h"

FileHandler::FileHandler(QObject *parent) : QObject(parent) {}

FileHandler::~FileHandler() {}

bool FileHandler::save(const QString &fileName, const QVector<QPair<int, int> > &moves) {
  const QString fn = FileHandler::cutFileName(fileName);
  QFile file(fn);
  if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    return false;
  }
  QTextStream out(&file);
  for(int i = 0; i < moves.size(); ++i) {
    out << moves[i].first << "\n";
    out << moves[i].second << "\n";
  }
  file.close();

  qDebug() << "data was written to file: " << fn;
  qDebug() << moves << "\n";

  return true;
}

bool FileHandler::load(const QString &fileName, QVector<QPair<int, int> > &moves) {
  QString fn = FileHandler::cutFileName(fileName);
  QFile file(fn);

  if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return false;
  }

  bool trueFile = isFileValid(file);
  if(!trueFile) {
    return false;
  }

  QTextStream in(&file);
  while(!in.atEnd()) {
    moves.append(qMakePair(in.readLine().toInt(), in.readLine().toInt()));
  }
  file.close();

  return true;
}

QString FileHandler::cutFileName(const QString &fileName) {
  QString fn = fileName;
  fn.replace("file://", "");
  return fn;
}

bool FileHandler::isFileValid(QFile &file) {
  qDebug() << "dive into isFileValid()";
  QErrorMessage *errorMessage = new QErrorMessage();

  if(file.exists() == false) {
    errorMessage->showMessage("The file doesn't exist.", "ErrorMessage");
    return false;
  }

  QFileInfo fi = file.fileName();
  if(fi.suffix() != "txt") {
    errorMessage->showMessage("The type of the file isn't '.txt'", "ErrorMessage");
    return false;
  }

  enum QFileDevice::FileError fault = file.error();
  if(fault) {
    switch(fault) {
      case 1: {
                errorMessage->showMessage("An error occurred when reading from the file.", "ErrorMessage");
                return false;
              }
      case 3: {
                errorMessage->showMessage("A fatal error occurred.", "ErrorMessage");
                return false;
              }
      case 4: {
                errorMessage->showMessage("Out of resources (e.g., too many open files, out of memory, etc.)", "ErrorMessage");
                return false;
              }
      case 5: {
                errorMessage->showMessage("The file could not be opened.", "ErrorMessage");
                return false;
              }
      case 6: {
                errorMessage->showMessage("The operation was aborted.", "ErrorMessage");
                return false;
              }
      case 7: {
                errorMessage->showMessage("A timeout occurred.", "ErrorMessage");
                return false;
              }
      case 8: {
                errorMessage->showMessage("An unspecified error occurred.", "ErrorMessage");
                return false;
              }
      default: {
                 errorMessage->showMessage("A \"default\" error occurred.", "ErrorMessage");
                 return false;
               }
    }
  }

  QTextStream in(&file);
  if(in.readLine().toInt() == 0) {
    errorMessage->showMessage("Wrong file. Try to use another one.", "ErrorMessage");
    return false;
  }
  in.seek(0);

  unsigned int sum = 0;
  while(!in.atEnd()) {
    if(in.readLine().toInt() > 63) {
      errorMessage->showMessage("Bad file. Try to use another one.", "ErrorMessage");
      return false;
    }
    ++sum;
  }
  in.seek(0);

  if(sum % 2) {
    errorMessage->showMessage("Something wrong with that file. Try to use another one.", "ErrorMessage");
    return false;
  }

  file.seek(0);

  qDebug() << "isFileValid(): true" << "\n";
  return true;
}
