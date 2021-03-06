/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/node/base/character_node_data.h"
/* -------------------------------------------------------------------------- */

namespace flow::node::base
{

  CharacterNodeData::CharacterNodeData(QChar value) : m_value(value) {}

  CharacterNodeData::~CharacterNodeData() = default;

  void CharacterNodeData::setValue(QChar value) { m_value = value; }

  QChar CharacterNodeData::getValue() const { return m_value; }

  void CharacterNodeData::assign(const NodeData &data)
  {
    auto &character_node_data = dynamic_cast<const CharacterNodeData &>(data);
    setValue(character_node_data.getValue());
  }

}// namespace flow::node::base
