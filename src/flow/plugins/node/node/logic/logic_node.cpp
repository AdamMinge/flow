/* ----------------------------------- Local -------------------------------- */
#include "flow/plugins/node/node/logic/logic_node.h"
/* ------------------------------------ Node -------------------------------- */
#include "flow/modules/node/base/boolean_node_data.h"
/* -------------------------------------------------------------------------- */

/* --------------------------- LogicNodeWithOneParam ------------------------ */

LogicNodeWithOneParam::LogicNodeWithOneParam()
{
  auto in_pin = std::make_unique<::node::Pin>(
    std::make_unique<node::base::BooleanNodeData>(false),
    ::node::Pin::Policy::ConnectionOne, "A");

  auto out_pin = std::make_unique<::node::Pin>(
    std::make_unique<node::base::BooleanNodeData>(false),
    ::node::Pin::Policy::ConnectionOne, "Q");

  insertPin(::node::Pin::Type::In, std::move(in_pin), 0);
  insertPin(::node::Pin::Type::Out, std::move(out_pin), 0);
}

LogicNodeWithOneParam::~LogicNodeWithOneParam() = default;

/* -------------------------- LogicNodeWithTwoParams ------------------------ */

LogicNodeWithTwoParams::LogicNodeWithTwoParams()
{
  auto in_pin = std::make_unique<::node::Pin>(
    std::make_unique<node::base::BooleanNodeData>(false),
    ::node::Pin::Policy::ConnectionOne, "B");

  insertPin(::node::Pin::Type::In, std::move(in_pin), 1);
}

LogicNodeWithTwoParams::~LogicNodeWithTwoParams() = default;