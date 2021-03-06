#ifndef FLOW_DOCUMENT_FORMAT_H
#define FLOW_DOCUMENT_FORMAT_H

/* ----------------------------------- Local -------------------------------- */
#include "flow/libflow/export.h"
#include "flow/libflow/file_format.h"
/* -------------------------------------------------------------------------- */

namespace flow::document
{

  class Document;

  class LIB_FLOW_API DocumentFormat : public FileFormat
  {
    Q_OBJECT
    Q_INTERFACES(flow::FileFormat)

  public:
    explicit DocumentFormat(QObject *parent = nullptr);
    ~DocumentFormat() override;

    virtual std::unique_ptr<Document>
    load(const QString &file_name, QString *error) = 0;
    virtual bool save(
      const Document &document, const QString &file_name, QString *error) = 0;
  };

}// namespace flow::document

Q_DECLARE_INTERFACE(flow::document::DocumentFormat, "org.flow.DocumentFormat")

namespace flow::document
{

  class ReadableDocumentFormat : public DocumentFormat
  {
    Q_OBJECT
    Q_INTERFACES(flow::document::DocumentFormat)

  public:
    explicit ReadableDocumentFormat(QObject *parent = nullptr);
    ~ReadableDocumentFormat() override;

    bool save(
      const Document &document, const QString &file_name,
      QString *error) override;
    [[nodiscard]] Capabilities getCapabilities() const override;
  };

  class WritableDocumentFormat : public DocumentFormat
  {
    Q_OBJECT
    Q_INTERFACES(flow::document::DocumentFormat)

  public:
    explicit WritableDocumentFormat(QObject *parent = nullptr);
    ~WritableDocumentFormat() override;

    std::unique_ptr<Document>
    load(const QString &file_name, QString *error) override;
    [[nodiscard]] Capabilities getCapabilities() const override;
  };

}// namespace flow::document

Q_DECLARE_INTERFACE(
  flow::document::ReadableDocumentFormat, "org.flow.ReadableDocumentFormat")
Q_DECLARE_INTERFACE(
  flow::document::WritableDocumentFormat, "org.flow.WritableDocumentFormat")

#endif//FLOW_DOCUMENT_FORMAT_H
