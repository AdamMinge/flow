#ifndef FLOW_FLOATING_POINT_TO_INTEGER_COVERTER_H
#define FLOW_FLOATING_POINT_TO_INTEGER_COVERTER_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/modules/node/export.h"
#include "flow/modules/node/type_converter.h"
/* -------------------------------------------------------------------------- */

class NODE_API FloatingPointToIntegerConverter : public node::TypeConverter
{
public:
  explicit FloatingPointToIntegerConverter() = default;
  ~FloatingPointToIntegerConverter() override = default;

  [[nodiscard]] std::unique_ptr<node::NodeData>
  convert(const node::NodeData &data) override;
};

#endif//FLOW_FLOATING_POINT_TO_INTEGER_COVERTER_H