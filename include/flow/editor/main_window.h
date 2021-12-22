#ifndef FLOW_MAIN_WINDOW_H
#define FLOW_MAIN_WINDOW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QMainWindow>
#include <QPointer>
#include <QStackedWidget>
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class MainWindow;
}

class LanguageManager;
class ProjectManager;
class ActionManager;
class StyleManager;

class ProjectWindow;
class NoProjectWindow;

class Project;

class AboutDialog;
class SettingsDialog;

class MainWindow final : public QMainWindow
{
  Q_OBJECT

private:
  struct Preferences;

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override;

  [[nodiscard]] LanguageManager &getLanguageManager() const;
  [[nodiscard]] ProjectManager &getProjectManager() const;
  [[nodiscard]] StyleManager &getStyleManager() const;
  [[nodiscard]] ActionManager &getActionManager() const;

protected:
  void closeEvent(QCloseEvent *event) override;
  void changeEvent(QEvent *event) override;

private:
  void initUi();
  void initConnections();

  void writeSettings();
  void readSettings();

  void retranslateUi();

private Q_SLOTS:
  void openSettings();
  void openAbout();

  void currentProjectChanged(Project *project);

  void updateWindowTitle();

private:
  QScopedPointer<Ui::MainWindow> m_ui;
  QScopedPointer<Preferences> m_preferences;

  QStackedWidget *m_stacked_widget;
  ProjectWindow *m_project_window;
  NoProjectWindow *m_no_project_window;

  QAction *m_about_action;
  QAction *m_settings_action;
  QAction *m_exit_action;

  QPointer<AboutDialog> m_about_dialog;
  QPointer<SettingsDialog> m_settings_dialog;
};

#endif//FLOW_MAIN_WINDOW_H
