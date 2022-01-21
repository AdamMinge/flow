/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/settings_dialog.h"
#include "flow/config.h"
/* ------------------------------------ Ui ---------------------------------- */
#include "ui_settings_dialog.h"
/* -------------------------------------------------------------------------- */

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent),
      m_ui(new Ui::SettingsDialog())
{
  m_ui->setupUi(this);

  retranslateUi();
}

SettingsDialog::~SettingsDialog() = default;

void SettingsDialog::changeEvent(QEvent *event)
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

void SettingsDialog::retranslateUi()
{
  m_ui->retranslateUi(this);

  setWindowTitle(tr("Settings"));
}