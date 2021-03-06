#ifndef FLOW_NODES_TREE_DELEGATE_H
#define FLOW_NODES_TREE_DELEGATE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QStyledItemDelegate>
/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/document/flow/export.h"
/* -------------------------------------------------------------------------- */

class FLOW_DOCUMENT_API FlowNodesTreeDelegate : public QStyledItemDelegate
{
  Q_OBJECT

public:
  explicit FlowNodesTreeDelegate(QObject *parent = nullptr);
  ~FlowNodesTreeDelegate() override;

  void paint(
    QPainter *painter, const QStyleOptionViewItem &option,
    const QModelIndex &index) const override;
  [[nodiscard]] QSize sizeHint(
    const QStyleOptionViewItem &option,
    const QModelIndex &index) const override;

private:
  const QSize m_icon_size;
  const int m_spacing;
};

#endif//FLOW_NODES_TREE_DELEGATE_H
