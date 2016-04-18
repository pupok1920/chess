#include "chexception.h"

/*! \class ChException
 * \brief Base class for exceptions.
 */

/*!
 * \param file - source file name where exception occurs.
 * \param line - line number where exception occurs.
 * \param description - description of the issue.
 */
ChException::ChException(const char *file, int line, const QString &description) throw()
    :_file(file), _line(line), _description(description)
{

}

ChException::~ChException()  throw()
{

}

/** \class ChLogicException
 * \brief Exception that may happen in case of some data processing (for example, incorrect input)
 *
 * But this exception also may be raised due to bug in application logic.
 */
ChLogicException::ChLogicException(const char *file, int line, const QString &description) throw()
    :ChException(file, line, description)
{

}

/** \class ChParserException
 * \brief Exception that may happen on data parsing.
 */
ChParserException::ChParserException(const char *file, int line, const QString &description) throw()
    :ChLogicException(file, line, description)
{

}

/** \class ChSystemException
 * \brief Exception that should never happen in the system (bug).
 */
ChSystemException::ChSystemException(const char *file, int line, const QString &description) throw()
    :ChException(file, line, description)
{

}
