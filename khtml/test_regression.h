/**
 * This file is part of the KDE project
 *
 * Copyright (C) 2001,2003 Peter Kelly (pmk@post.com)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef TEST_REGRESSION_H
#define TEST_REGRESSION_H

#include <khtml_part.h>
#include <kurl.h>
#include <qobject.h>
#include <kjs/ustring.h>
#include <kjs/object.h>
#include <kjs/interpreter.h>

class RegressionTest;
class QTimer;

/**
 * @internal
 */
class PartMonitor : public QObject
{
  Q_OBJECT
public:
    PartMonitor(KHTMLPart *_part);
    ~PartMonitor();
    void waitForCompletion();
    static PartMonitor* sm_highestMonitor;
    bool m_completed;
    KHTMLPart *m_part;
    int m_timer_waits;
    QTimer *m_timeout_timer;
public slots:
    void partCompleted();
    void timeout();
    void finishTimers();
};

/**
 * @internal
 */
class RegTestObject : public KJS::ObjectImp
{
public:
    RegTestObject(KJS::ExecState *exec, RegressionTest *_regTest);

private:
    RegressionTest *m_regTest;
};

/**
 * @internal
 */
class RegTestFunction : public KJS::ObjectImp
{
public:
    RegTestFunction(KJS::ExecState *exec, RegressionTest *_regTest, int _id, int length);

    bool implementsCall() const;
    KJS::Value call(KJS::ExecState *exec, KJS::Object &thisObj, const KJS::List &args);

    enum { Print, ReportResult, CheckOutput, Quit };

private:
    RegressionTest *m_regTest;
    int id;
};

/**
 * @internal
 */
class KHTMLPartObject : public KJS::ObjectImp
{
public:
    KHTMLPartObject(KJS::ExecState *exec, KHTMLPart *_part);

    virtual KJS::Value get(KJS::ExecState *exec, const KJS::Identifier &propertyName) const;

private:
    KHTMLPart *m_part;
};

/**
 * @internal
 */
class KHTMLPartFunction : public KJS::ObjectImp
{
public:
    KHTMLPartFunction(KJS::ExecState *exec, KHTMLPart *_part, int _id, int length);

    bool implementsCall() const;
    KJS::Value call(KJS::ExecState *exec, KJS::Object &thisObj, const KJS::List &args);

    enum { OpenPage, OpenPageAsUrl, Begin, Write, End, ExecuteScript, ProcessEvents };
private:
    KHTMLPart *m_part;
    int id;
};

namespace KJS {
class ScriptInterpreter;
}

/**
 * @internal
 */
class RegressionTest : public QObject
{
  Q_OBJECT
public:

    RegressionTest(KHTMLPart *part, const QString &baseDir, const QString &outputDir,
		   bool _genOutput, bool runJS, bool runHTML);
    ~RegressionTest();

    enum OutputType { DOMTree, RenderTree };
    QString getPartOutput( OutputType type );
    void getPartDOMOutput( QTextStream &outputStream, KHTMLPart* part, uint indent );
    void dumpRenderTree( QTextStream &outputStream, KHTMLPart* part );
    void testStaticFile(const QString& filename);
    void testJSFile(const QString& filename);
    enum CheckResult { Failure = 0, Success = 1, Ignored = 2 };
    CheckResult checkOutput(const QString& againstFilename);
    CheckResult checkPaintdump( const QString& againstFilename);
    enum FailureType { NoFailure = 0, AllFailure = 1, RenderFailure = 2, DomFailure = 4, PaintFailure = 8, JSFailure = 16};
    bool runTests(QString relPath = QString::null, bool mustExist = false, int known_failure = NoFailure);
    bool reportResult( bool passed, const QString & description = QString::null );
    bool reportResult(CheckResult result, const QString & description = QString::null );
    void createMissingDirs(const QString &path);

    QImage renderToImage();
    bool imageEqual( const QImage &lhs, const QImage &rhs );
    void createLink( const QString& test, int failures );
    void doJavascriptReport( const QString &test );
    void doFailureReport( const QString& test, int failures );

    KHTMLPart *m_part;
    QString m_baseDir;
    QString m_outputDir;
    bool m_genOutput;
    QString m_currentBase;

    QString m_currentOutput;
    QString m_currentCategory;
    QString m_currentTest;
    QPixmap* m_paintBuffer;

    bool m_getOutput;
    bool m_runJS;
    bool m_runHTML;
    int m_passes_work;
    int m_passes_fail;
    int m_failures_work;
    int m_failures_fail;
    int m_errors;
    bool saw_failure;
    bool ignore_errors;
    int m_known_failures;

    static RegressionTest *curr;

private:
    void printDescription(const QString& description);

    static bool svnIgnored( const QString &filename );

private:
    void evalJS( KJS::ScriptInterpreter &interp, const QString &filename, bool report ); // used by testJS

private slots:
    void slotOpenURL(const KURL &url, const KParts::URLArgs &args);
    void resizeTopLevelWidget( int, int );

};

#endif
