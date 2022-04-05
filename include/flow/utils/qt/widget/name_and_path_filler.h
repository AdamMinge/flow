#ifndef FLOW_NAME_AND_PATH_FILLER_H
#define FLOW_NAME_AND_PATH_FILLER_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QDir>
#include <QWidget>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qt/widget/export.h"
/* -------------------------------------------------------------------------- */

namespace Ui
{
  class QtNameAndPathFiller;
}

namespace utils
{

  class WIDGET_API QtNameAndPathFiller : public QWidget
  {
    Q_OBJECT

  public:
    enum class NameValidation;
    enum class PathValidation;

    Q_DECLARE_FLAGS(NameValidations, NameValidation);
    Q_DECLARE_FLAGS(PathValidations, PathValidation);

  public:
    explicit QtNameAndPathFiller(QWidget *parent = nullptr);
    ~QtNameAndPathFiller() override;

    void setNameValidations(NameValidations validations);
    [[nodiscard]] NameValidations getNameValidations() const;

    void setPathValidations(PathValidations validations);
    [[nodiscard]] PathValidations getPathValidations() const;

    void setBrowserDir(const QDir &dir);
    [[nodiscard]] QDir getBrowserDir() const;

    [[nodiscard]] QString getName() const;
    [[nodiscard]] QString getPath() const;

    [[nodiscard]] bool isValid() const;

  Q_SIGNALS:
    void nameChanged(const QString &name);
    void pathChanged(const QString &name);
    bool validStateChanged(bool isValid);

  protected:
    void changeEvent(QEvent *event) override;

  private Q_SLOTS:
    void nameChanged();
    void pathChanged();

  private:
    void initUi();
    void initConnections();

    void retranslateUi();

    [[nodiscard]] QString getNameErrorMessage() const;
    [[nodiscard]] QString getPathErrorMessage() const;

  private:
    QScopedPointer<Ui::QtNameAndPathFiller> m_ui;
    NameValidations m_name_validations;
    PathValidations m_path_validations;
  };

  enum class QtNameAndPathFiller::NameValidation
  {
    NotEmpty = 1 << 0,
    All = NotEmpty
  };

  enum class QtNameAndPathFiller::PathValidation
  {
    NotEmpty = 1 << 0,
    DirExists = 1 << 1,
    DirIsEmpty = 1 << 2,
    All = NotEmpty | DirExists | DirIsEmpty
  };

  Q_DECLARE_OPERATORS_FOR_FLAGS(QtNameAndPathFiller::NameValidations)
  Q_DECLARE_OPERATORS_FOR_FLAGS(QtNameAndPathFiller::PathValidations)

}// namespace utils

#endif//FLOW_NAME_AND_PATH_FILLER_H
