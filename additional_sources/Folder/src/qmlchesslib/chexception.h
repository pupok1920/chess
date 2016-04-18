#ifndef CHEXCEPTION_H
#define CHEXCEPTION_H

#include <QString>

#include "chlib.h"

class QMLCHESSLIB_COMMON_DLLSPEC ChException
{
public:
    ChException(const char* file, int line, const QString& description) throw();
    QString file() const throw() {
        return _file;
    }
    int line() const throw() {
        return _line;
    }
    QString description() const throw() {
        return _description;
    }
    virtual ~ChException() throw();

private:
    const QString _file;
    const int _line;
    const QString _description;
};

class QMLCHESSLIB_COMMON_DLLSPEC ChLogicException: public ChException
{
public:
    ChLogicException(const char* file, int line, const QString& description) throw();
};

class QMLCHESSLIB_COMMON_DLLSPEC ChSystemException: public ChException
{
public:
    ChSystemException(const char* file, int line, const QString& description) throw();
};

class QMLCHESSLIB_COMMON_DLLSPEC ChParserException: public ChLogicException
{
public:
    ChParserException(const char* file, int line, const QString& description) throw();
};

#define CH_THROW_LOGIC_EX(descr) (throw ChLogicException(__FILE__, __LINE__, descr))
#define CH_LOGIC_ASSERT(cond, descr) if (!(cond)) CH_THROW_LOGIC_EX(descr);

#define CH_THROW_PARSER_EX(descr) (throw ChParserException(__FILE__, __LINE__, descr))
#define CH_PARSER_ASSERT(cond, descr) if (!(cond)) CH_THROW_PARSER_EX(descr);

#define CH_THROW_SYSTEM_EX(descr) (throw ChSystemException(__FILE__, __LINE__, descr))
#define CH_SYSTEM_ASSERT(cond, descr) if (!(cond)) CH_THROW_SYSTEM_EX(descr);

#endif // CHEXCEPTION_H
