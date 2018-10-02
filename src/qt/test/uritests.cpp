// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2017 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "uritests.h"

#include "guiutil.h"
#include "walletmodel.h"

#include <QUrl>

void URITests::uriTests()
{
    SendCoinsRecipient rv;
    QUrl uri;
    uri.setUrl(QString("obsr:obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj?req-dontexist="));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("obsr:obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj?dontexist="));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("obsr:obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj?label=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj"));
    QVERIFY(rv.label == QString("Some Example Address"));
    QVERIFY(rv.amount == 0);

    uri.setUrl(QString("obsr:obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj?amount=0.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100000);

    uri.setUrl(QString("obsr:obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj?amount=1.001"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj"));
    QVERIFY(rv.label == QString());
    QVERIFY(rv.amount == 100100000);

    uri.setUrl(QString("obsr:obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj?amount=100&label=Some Example"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj"));
    QVERIFY(rv.amount == 10000000000LL);
    QVERIFY(rv.label == QString("Some Example"));

    uri.setUrl(QString("obsr:obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj?message=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));
    QVERIFY(rv.address == QString("obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj"));
    QVERIFY(rv.label == QString());

    QVERIFY(GUIUtil::parseBitcoinURI("obsr://obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj?message=Some Example Address", &rv));
    QVERIFY(rv.address == QString("obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj"));
    QVERIFY(rv.label == QString());

    uri.setUrl(QString("obsr:obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj?req-message=Some Example Address"));
    QVERIFY(GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("obsr:obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj?amount=1,000&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));

    uri.setUrl(QString("obsr:obn4DFJFvYXMDk1WHssWJKxPXfacdeSoCj?amount=1,000.0&label=Some Example"));
    QVERIFY(!GUIUtil::parseBitcoinURI(uri, &rv));
}
