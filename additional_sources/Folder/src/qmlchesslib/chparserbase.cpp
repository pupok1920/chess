#include "chparserbase.h"

#include <QFile>
#include <QXmlSchemaValidator>
#include <QBuffer>
#include <QFileInfo>
#include <QDir>

#include "chmessagehandler.h"
#include "chexception.h"

enum {
    CH_XML_SAVE_INDENT = 4,
};

/** \class ChParserBase
 * \brief Base class for XML file parser.
 *
 * Provides validation with XML Schema.
 *
 * Supports data in file and in memory (QByteArray).
 */

ChParserBase::~ChParserBase()
{

}

/** \brief Loads XML file into QDomDocument object.

  No XML Schema validation in this function. Just DOM parsing.

  \param fileName - XML file to load.
  \return DOM document.
  \exception ChParserException in case of any file access or parser error.
*/
QDomDocument ChParserBase::loadToDom(const QString &fileName) const
{
    QDomDocument doc;
    QFile f(fileName);

    // Open file
    CH_PARSER_ASSERT(f.exists(), tr("File '%1' does not exist").arg(fileName));
    CH_PARSER_ASSERT(f.open(QIODevice::ReadOnly),
        tr("Cannot open file '%1' for read").arg(fileName)
    );

    // Parse using DOM
    QString message;
    int line;
    int column;
    CH_PARSER_ASSERT(doc.setContent(&f, &message, &line, &column),
        tr("Cannot load file '%1'. Line %2, column %3, message '%4'")
            .arg(fileName).arg(line).arg(column).arg(message)
    );

    return doc;
}

/** \brief Loads XML data into QDomDocument object.

  No XML Schema validation in this function. Just DOM parsing.

  \param data - XML data.
  \return DOM document.
  \exception ChParserException in case of any parser error.
*/
QDomDocument ChParserBase::loadToDom(const QByteArray &data)
{
    QDomDocument doc;

    // QBuffer accepts only non-const QByteArray. So, create a copy.
    // QByteArray is a shared class, no large data blocks are duplicated
    // on this operation.
    QByteArray ba(data);
    QBuffer buffer(&ba);
    // Do not modify data.
    buffer.open(QIODevice::ReadOnly);

    // Parse using DOM
    QString message;
    int line;
    int column;
    CH_PARSER_ASSERT(doc.setContent(&buffer, &message, &line, &column),
        tr("Cannot load data. Line %1, column %2, message '%3'")
            .arg(line).arg(column).arg(message)
    );

    return doc;
}

/** \brief Validate XML file with XML Schema file.
    \param schemaFileName - XML Schema file to use for validation.
    May be internal resource (like ":/schema/file/name").
    \param fileName - XML file to load.
    \exception ChParserException in case of any file access or parser error.
*/
void ChParserBase::validate(const QString &schemaFileName,
    const QString &fileName) const
{
    // Load Schema
    QXmlSchema schema = loadSchema(schemaFileName);

    // Setup Message Handler
    ChMessageHandler messageHandler;
    schema.setMessageHandler(&messageHandler);

    // Open file
    QFile file1(fileName);
    CH_PARSER_ASSERT(file1.open(QIODevice::ReadOnly | QIODevice::Text),
        tr("Cannot open XML file '%1' for read").arg(fileName)
    );

    // Validate
    QXmlSchemaValidator validator(schema);
    CH_PARSER_ASSERT(
        validator.validate(&file1, QUrl::fromLocalFile(file1.fileName())),
        tr("File '%1': validation failed at line '%2' column '%3'. Reason: %4")
            .arg(fileName).arg(messageHandler.line()).arg(messageHandler.column())
            .arg(messageHandler.statusMessage()
        )
    );
}

/** \brief Loads XML schema from file.
    \param schemaFileName - schema file name. May be internal resource
    (like ":/schema/file/name").
    \return XML Schema object.
    \exception ChParserException in case of any file access or parser error.
*/
QXmlSchema ChParserBase::loadSchema(const QString &schemaFileName) const
{
    QFile file(schemaFileName);

    // Open file
    CH_PARSER_ASSERT(file.open(QIODevice::ReadOnly | QIODevice::Text),
        tr("Cannot open schema file '%1' for read").arg(schemaFileName)
    );

    QXmlSchema schema;
    // Load Schema
    CH_PARSER_ASSERT(schema.load(&file, QUrl::fromLocalFile(file.fileName())),
        tr("Cannot load schema from file '%1'").arg(schemaFileName)
    );

    // Validate result of loading
    CH_PARSER_ASSERT(schema.isValid(),
        tr("Schema in file '%1' is not valid.").arg(schemaFileName)
    );

    return schema;
}

/** \brief Validate XML using XML Schema.

    \param data - XML data.
    \param schemaFileName - XML Schema file to use for validation.
    May be internal resource (like "qrc:/schema/file/name").
    \exception ChParserException in case of any file access or parser error.
*/
void ChParserBase::validateByteArray(const QString &schemaFileName, QByteArray &data) const
{
    // Load Schema
    QXmlSchema schema = loadSchema(schemaFileName);

    // Setup Message Handler
    ChMessageHandler messageHandler;
    schema.setMessageHandler(&messageHandler);

    // QBuffer accepts only non-const QByteArray.
    QBuffer buffer(&data);
    buffer.open(QIODevice::ReadOnly);

    // Validate
    QXmlSchemaValidator validator(schema);
    CH_PARSER_ASSERT(validator.validate(&buffer),
        tr("Validation failed at line '%1' column '%2'. Reason: %3")
            .arg(messageHandler.line()).arg(messageHandler.column())
            .arg(messageHandler.statusMessage()
        )
    );

}

/** \brief Saves XML data to file.

Validates XML data in \a doc using XML Schema \a schemaFileName
before saving to \a fileName.

Not effective for large files.

\exception ChParserException in case of any file access or parser error.
*/
void ChParserBase::saveFile(const QString &fileName, const QDomDocument &doc,
    const QString &schemaFileName) const
{
    // Convert DOM to QByteArray.
    // This operation will be time- and memory-consuming on
    // large files.
    QByteArray ba = doc.toByteArray(CH_XML_SAVE_INDENT);

    // Validate
    validateByteArray(schemaFileName, ba);

    // Backup existing file
    backupFile(fileName);

    // Create path if it does not exist
    QFileInfo fi(fileName);
    if (!QFile::exists(fi.absolutePath())) {
        QDir().mkpath(fi.absolutePath());
    }
    CH_PARSER_ASSERT(QFile::exists(fi.absolutePath()),
        tr("Cannot create directory '%1'").arg(fi.absolutePath())
    );

    // Save data and check result
    QFile f(fileName);
    CH_PARSER_ASSERT(f.open(QFile::WriteOnly), tr("Cannot save file '%1'").arg(fileName));
    CH_PARSER_ASSERT(f.write(ba) == ba.size(),
        tr("Cannot save all data to file '%1'").arg(fileName)
    );
}

/** \brief Creates a backup file.

".bak" added to the \a fileName.

No error reporting.
*/
void ChParserBase::backupFile(const QString& fileName) const {
    if (QFile::exists(fileName)) {
      QFile::remove(fileName + ".bak");
      QDir d;
      d.rename(fileName, fileName + ".bak");
    }
}
