/* ------------------------------------ Qt ---------------------------------- */
#include <QFileInfo>
/* ----------------------------------- Local -------------------------------- */
#include "flow/api/document/document.h"
/* -------------------------------------------------------------------------- */

namespace api::document
{

  IDocument::IDocument(Type type, QObject *parent)
      : QObject(parent), m_type(type)
  {}

  IDocument::~IDocument() = default;

  IDocument::Type IDocument::getType() const { return m_type; }

}// namespace api::document