#ifndef FLOW_TOOLS_UNSELECTABLE_VIEW_H
#define FLOW_TOOLS_UNSELECTABLE_VIEW_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QAbstractItemView>
#include <QListView>
#include <QMouseEvent>
#include <QTableView>
#include <QTreeView>
/* -------------------------------------------------------------------------- */

namespace tools
{

  template<typename VIEW>
  requires std::derived_from<VIEW, QAbstractItemView>
  class TOOLS_SHARED_API QtUnselectableView : public VIEW
  {
  public:
    explicit QtUnselectableView(QWidget *parent = nullptr);
    ~QtUnselectableView() override;

  private:
    void mousePressEvent(QMouseEvent *event) override;
  };

  template<typename VIEW>
  requires std::derived_from<VIEW, QAbstractItemView>
  QtUnselectableView<VIEW>::QtUnselectableView(QWidget *parent) : VIEW(parent)
  {
  }

  template<typename VIEW>
  requires std::derived_from<VIEW, QAbstractItemView>
    QtUnselectableView<VIEW>::~QtUnselectableView() = default;

  template<typename VIEW>
  requires std::derived_from<VIEW, QAbstractItemView>
  void QtUnselectableView<VIEW>::mousePressEvent(QMouseEvent *event)
  {
    auto item = VIEW::indexAt(event->pos());
    auto selected = VIEW::selectionModel()->isSelected(VIEW::indexAt(event->pos()));

    if ((item.row() == -1 && item.column() == -1) || selected)
    {
      VIEW::clearSelection();
      VIEW::selectionModel()->setCurrentIndex(QModelIndex(), QItemSelectionModel::Select);
    }

    VIEW::mousePressEvent(event);
  }

  using QtUnselectableTreeView = QtUnselectableView<QTreeView>;
  using QtUnselectableListView = QtUnselectableView<QListView>;
  using QtUnselectableTableView = QtUnselectableView<QTableView>;

}// namespace tools

#endif//FLOW_TOOLS_UNSELECTABLE_VIEW_H
