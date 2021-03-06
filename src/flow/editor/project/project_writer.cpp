/* ----------------------------------- Local -------------------------------- */
#include "flow/editor/project/project_writer.h"
/* ------------------------------------ Qt ---------------------------------- */
#include <QFile>
#include <QXmlStreamWriter>
/* ---------------------------------- LibFlow ------------------------------- */
#include <flow/libflow/project/project.h>
/* -------------------------------------------------------------------------- */

/* ----------------------------- ProjectWriterImpl -------------------------- */

class ProjectWriter::ProjectWriterImpl
{
public:
  explicit ProjectWriterImpl() = default;
  ~ProjectWriterImpl() = default;

  void writeProject(const flow::project::Project &project, QIODevice &device);

private:
  void
  writeProject(QXmlStreamWriter &writer, const flow::project::Project &project);
};

void ProjectWriter::ProjectWriterImpl::writeProject(
  const flow::project::Project &project, QIODevice &device)
{
  QXmlStreamWriter writer(&device);

  writer.writeStartDocument();
  writeProject(writer, project);
  writer.writeEndDocument();
}

void ProjectWriter::ProjectWriterImpl::writeProject(
  QXmlStreamWriter &writer, const flow::project::Project &project)
{
  writer.writeStartElement(QStringLiteral("project"));

  writer.writeEndElement();
}

/* ------------------------------- ProjectWriter ---------------------------- */

ProjectWriter::ProjectWriter() : m_impl(std::make_unique<ProjectWriterImpl>())
{}

ProjectWriter::~ProjectWriter() = default;

void ProjectWriter::write(
  const flow::project::Project &project, QIODevice &device)
{
  m_impl->writeProject(project, device);
}

bool ProjectWriter::write(
  const flow::project::Project &project, const QString &file_name,
  QString *error)
{
  QFile file(file_name);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    if (error) *error = QObject::tr("Failed to open file = %1").arg(file_name);
    return false;
  }

  m_impl->writeProject(project, file);

  if (file.error() != QFileDevice::NoError)
  {
    if (error) *error = file.errorString();
    return false;
  }

  file.close();
  return true;
}