/* ------------------------------------ Qt ---------------------------------- */
#include <QApplication>
#include <QCommandLineParser>
/* ----------------------------------- Local -------------------------------- */
#include "flow/tools/editor/main_window.h"
#include "flow/tools/editor/meta_types.h"
#include "flow/config.h"
/* -------------------------------------------------------------------------- */

/* ----------------------------- messagesToConsole -------------------------- */

static const QtMessageHandler QT_DEFAULT_MESSAGE_HANDLER = qInstallMessageHandler(nullptr); // NOLINT(cert-err58-cpp)

static void messagesToConsole(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
  switch (type)
  {
    case QtInfoMsg:
    case QtDebugMsg:
      // TODO : implementation //
      break;

    case QtWarningMsg:
      // TODO : implementation //
      break;

    case QtCriticalMsg:
      // TODO : implementation //
      break;

    default:
      break;
  }

  (*QT_DEFAULT_MESSAGE_HANDLER)(type, context, msg);
}

/* ----------------------------- CommandLineParser -------------------------- */

class CommandLineParser
{
public:
  explicit CommandLineParser();
  ~CommandLineParser() = default;

  void process(const QCoreApplication &app);
};

CommandLineParser::CommandLineParser() = default;

void CommandLineParser::process(const QCoreApplication &app)
{
  QCommandLineParser parser;
  parser.setApplicationDescription("Engine Editor");
  parser.addHelpOption();
  parser.addVersionOption();

  parser.process(app);
}

/* ----------------------------------- main --------------------------------- */

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  QApplication::setApplicationName(QStringLiteral("Flow-Editor"));
  QApplication::setApplicationVersion(QLatin1String(FLOW_VERSION_STR));
  QApplication::setApplicationDisplayName(QStringLiteral("Flow-Editor"));
  QApplication::setOrganizationName(QStringLiteral("Flow"));

  registerMetaTypes();

  qInstallMessageHandler(messagesToConsole);

  CommandLineParser parser;
  parser.process(app);

  MainWindow mainWindow;
  mainWindow.show();

  return QApplication::exec();
}
