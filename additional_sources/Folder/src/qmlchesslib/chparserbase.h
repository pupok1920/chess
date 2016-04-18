#ifndef CHPARSERBASE_H
#define CHPARSERBASE_H

#include <QCoreApplication>
#include <QDomDocument>
#include <QXmlSchema>

#include "chlib.h"

class QMLCHESSLIB_COMMON_DLLSPEC ChParserBase
{
    Q_DECLARE_TR_FUNCTIONS(ChParserBase)
public:
    virtual ~ChParserBase();

protected:
    QDomDocument loadToDom(const QString &fileName) const;
    QDomDocument loadToDom(const QByteArray &data);
    void validate(const QString &schemaFileName, const QString &fileName) const;
    QXmlSchema loadSchema(const QString &schemaFileName) const;
    void validateByteArray(const QString &schemaFileName, QByteArray &data) const;
    void saveFile(const QString &fileName, const QDomDocument &doc,
        const QString &schemaFileName) const;
    void backupFile(const QString &fileName) const;
};

#endif // CHPARSERBASE_H
