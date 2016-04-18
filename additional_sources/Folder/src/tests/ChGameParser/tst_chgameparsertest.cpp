#include <QString>
#include <QtTest>

#include "chgameparser.h"
#include "chexception.h"

class ChGameParserTest : public QObject
{
    Q_OBJECT

public:
    ChGameParserTest();

private Q_SLOTS:
    void testLoad();
    void testSave();
};

ChGameParserTest::ChGameParserTest()
{
}

void ChGameParserTest::testLoad()
{
    ChGameParser parser;
    ChGameParser::Moves actual = parser.load(":/good.xml");
    ChGameParser::Moves expected;
    expected.push_back(std::make_pair(ChSquare(12), ChSquare(28)));
    expected.push_back(std::make_pair(ChSquare(52), ChSquare(36)));
    QCOMPARE(actual, expected);

    QVERIFY_EXCEPTION_THROWN(parser.load("/etc"), ChParserException);
    QVERIFY_EXCEPTION_THROWN(parser.load(":/bad_binary.bin"), ChParserException);
    QVERIFY_EXCEPTION_THROWN(parser.load(":/bad_xml.xml"), ChParserException);
    QVERIFY_EXCEPTION_THROWN(parser.load(":/bad_schema.xml"), ChParserException);
    QVERIFY_EXCEPTION_THROWN(parser.load(":/bad_schema1.xml"), ChParserException);
    QVERIFY_EXCEPTION_THROWN(parser.load(":/bad_schema2.xml"), ChParserException);
    QVERIFY_EXCEPTION_THROWN(parser.load(":/bad_schema3.xml"), ChParserException);
    QVERIFY_EXCEPTION_THROWN(parser.load(":/bad_schema4.xml"), ChParserException);
    QVERIFY_EXCEPTION_THROWN(parser.load(":/bad_schema5.xml"), ChParserException);
}

void ChGameParserTest::testSave()
{
    ChGameParser parser;
    ChGameParser::Moves expected;
    expected.push_back(std::make_pair(ChSquare(12), ChSquare(28)));
    expected.push_back(std::make_pair(ChSquare(52), ChSquare(36)));
    parser.save("tmp_test.xml", expected);
    ChGameParser::Moves actual = parser.load("tmp_test.xml");
    QCOMPARE(actual, expected);
    QString fn = "http://www.microsoft.com/default.htm";

#ifdef Q_OS_LINUX
    fn = "/default.htm";
#endif

    QVERIFY_EXCEPTION_THROWN(parser.save(fn, expected),
        ChParserException);

}

QTEST_MAIN(ChGameParserTest)

#include "tst_chgameparsertest.moc"
