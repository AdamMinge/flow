/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/node/base/boolean_node_data.h"
/* -------------------------------------------------------------------------- */

namespace flow::node::base
{

  BooleanNodeData::BooleanNodeData(bool value) : m_value(value) {}

  BooleanNodeData::~BooleanNodeData() = default;

  void BooleanNodeData::setValue(bool value) { m_value = value; }

  bool BooleanNodeData::getValue() const { return m_value; }

  void BooleanNodeData::assign(const NodeData &data)
  {
    auto &boolean_node_data = dynamic_cast<const BooleanNodeData &>(data);
    setValue(boolean_node_data.getValue());
  }

}// namespace flow::node::base
