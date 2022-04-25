/* ------------------------------------ Qt ---------------------------------- */
#include <QDir>
#include <QEvent>
#include <QMessageBox>
/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/project/new_project_dialog.h"
#include "flow/editor/project/project_format_pro.h"
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/format_helper.h>
#include <flow/libflow/preferences_manager.h>
#include <flow/libflow/project/project.h>
/* ------------------------------------ Ui ---------------------------------- */
#include "project/ui_new_project_dialog.h"
/* -------------------------------------------------------------------------- */

/* -------------------------------- Preferences ----------------------------- */

struct NewProjectDialog::Preferences {
  flow::Preference<QByteArray> new_project_dialog_geometry =
    flow::Preference<QByteArray>("new_project_dialog/geometry");
};

/* ----------------------------- NewProjectDialog -------------------------- */

NewProjectDialog::NewProjectDialog(QWidget *parent)
    : QDialog(parent), m_ui(new Ui::NewProjectDialog()),
      m_preferences(new Preferences)
{
  initUi();
  initConnections();

  readSettings();
  retranslateUi();
}

NewProjectDialog::~NewProjectDialog() { writeSettings(); }

std::unique_ptr<flow::project::Project> NewProjectDialog::create()
{
  if (exec() != QDialog::Accepted) return nullptr;

  auto format_helper =
    flow::FormatHelper<ProjectFormatPro>{flow::FileFormat::Capability::Write};
  auto format = format_helper.getFormats().isEmpty()
                  ? nullptr
                  : format_helper.getFormats().front();

  auto error = tr("Wrong project format");
  if (format)
  {
    auto project = flow::project::Project::create();
    project->setWriterFormat(format);
    project->setWriterFormat(format);

    const auto name = m_ui->m_name_and_path_filler->getName();
    const auto path = m_ui->m_name_and_path_filler->getPath();
    const auto file_name =
      QDir(path).filePath(name + "." + format->getShortName());

    if (project->save(file_name, &error)) return project;
  }

  QMessageBox::critical(this, tr("Error Project Creation"), error);
  return nullptr;
}

void NewProjectDialog::changeEvent(QEvent *event)
{
  QDialog::changeEvent(event);

  switch (event->type())
  {
    case QEvent::LanguageChange:
      retranslateUi();
      break;
    default:
      break;
  }
}

void NewProjectDialog::updateCreateButton()
{
  m_ui->m_create_button->setEnabled(m_ui->m_name_and_path_filler->isValid());
}

void NewProjectDialog::initUi()
{
  m_ui->setupUi(this);

  updateCreateButton();
}

void NewProjectDialog::initConnections()
{
  connect(
    m_ui->m_create_button, &QPushButton::pressed, this,
    &NewProjectDialog::accept);
  connect(
    m_ui->m_name_and_path_filler,
    &utils::QtNameAndPathFiller::validStateChanged, this,
    &NewProjectDialog::updateCreateButton);
}

void NewProjectDialog::retranslateUi()
{
  m_ui->retranslateUi(this);

  setWindowTitle(tr("New Project"));
}

void NewProjectDialog::writeSettings()
{
  m_preferences->new_project_dialog_geometry = saveGeometry();
}

void NewProjectDialog::readSettings()
{
  auto new_project_dialog_geometry =
    m_preferences->new_project_dialog_geometry.get();
  if (!new_project_dialog_geometry.isNull())
    restoreGeometry(new_project_dialog_geometry);
}
