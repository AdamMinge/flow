/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/issue_table_model.h"
#include "flow/editor/issue_manager.h"
/* -------------------------------------------------------------------------- */

IssueTableModel::IssueTableModel(QObject *parent) : QAbstractTableModel(parent)
{
  auto issue_manager = &IssueManager::getInstance();

  connect(
    issue_manager, &IssueManager::onErrorReport, this,
    &IssueTableModel::addIssue);
  connect(
    issue_manager, &IssueManager::onWarningReport, this,
    &IssueTableModel::addIssue);

  connect(
    issue_manager, qOverload<const QVariant &>(&IssueManager::onClear), this,
    &IssueTableModel::removeIssues);
  connect(
    issue_manager, qOverload<>(&IssueManager::onClear), this,
    &IssueTableModel::removeAllIssues);
}

IssueTableModel::~IssueTableModel() = default;

QVariant IssueTableModel::data(const QModelIndex &index, int role) const
{
  if (index.row() < 0 || index.row() >= rowCount(index.parent()))
    return QVariant{};

  if (role == Qt::DisplayRole)
  {
    const auto issue = m_issues[index.row()].first;
    const auto issue_occurrences = m_issues[index.row()].second;
    switch (index.column())
    {
      case Column::Severity:
        return getIssueSeverityName(index);

      case Column::Description:
        return issue.getText();

      case Column::Occurrences:
        return issue_occurrences;
    }
  } else if (role == Qt::DecorationRole)
  {
    switch (index.column())
    {
      case Column::Severity:
        return getIssueIcon(index);
    }
  } else if (role == Role::IssueRole)
  {
    return QVariant::fromValue(m_issues[index.row()].first);
  }

  return QVariant{};
}

int IssueTableModel::rowCount(const QModelIndex &parent) const
{
  return static_cast<int>(m_issues.size());
}

int IssueTableModel::columnCount(const QModelIndex &parent) const { return 3; }

QVariant IssueTableModel::headerData(
  int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
  {
    switch (section)
    {
      case Column::Severity:
        return tr("Severity");

      case Column::Description:
        return tr("Description");

      case Column::Occurrences:
        return tr("Occurrences");

      default:
        return QVariant{};
    }
  }
  return QVariant{};
}

void IssueTableModel::addIssue(const Issue &issue)
{
  auto found_issue_iter =
    std::find_if(m_issues.begin(), m_issues.end(), [&issue](auto &issue_pair) {
      return issue_pair.first == issue;
    });

  if (found_issue_iter == m_issues.end())
  {
    beginInsertRows(
      QModelIndex{}, rowCount(QModelIndex{}), rowCount(QModelIndex{}));
    found_issue_iter =
      m_issues.insert(m_issues.end(), std::make_pair(issue, 1));
    endInsertRows();
  } else
  {
    found_issue_iter->second += 1;

    auto changed_row =
      static_cast<int>(std::distance(m_issues.begin(), found_issue_iter));
    dataChanged(
      index(changed_row, Column::Occurrences),
      index(changed_row, Column::Occurrences));
  }
}

void IssueTableModel::removeIssues(const QVariant &context)
{
  auto erased_elements = std::erase_if(m_issues, [&context](auto &issue_pair) {
    return issue_pair.first.getContext() == context;
  });

  if (erased_elements > 0)
  {
    beginResetModel();
    endResetModel();
  }
}

void IssueTableModel::removeAllIssues()
{
  if (!m_issues.empty())
  {
    beginResetModel();
    m_issues.clear();
    endResetModel();
  }
}

QIcon IssueTableModel::getIssueIcon(const QModelIndex &index) const
{
  const auto issue = m_issues[index.row()].first;

  switch (issue.getSeverity())
  {
    case Issue::Severity::Error:
      return QIcon(":/editor/images/32x32/error_issue.png");

    case Issue::Severity::Warning:
      return QIcon(":/editor/images/32x32/warning_issue.png");
  }

  return QIcon{};
}

QString IssueTableModel::getIssueSeverityName(const QModelIndex &index) const
{
  const auto issue = m_issues[index.row()].first;

  switch (issue.getSeverity())
  {
    case Issue::Severity::Error:
      return tr("Error");

    case Issue::Severity::Warning:
      return tr("Warning");
  }

  return QString{};
}