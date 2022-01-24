#ifndef FLOW_TOOLS_ZIP_FILE_H
#define FLOW_TOOLS_ZIP_FILE_H

/* ------------------------------------ Qt ---------------------------------- */
#include <QObject>
#include <QString>
#include <QStringList>
/* ----------------------------------- Local -------------------------------- */
#include "flow/utils/qtzip/export.h"
/* -------------------------------------------------------------------------- */

struct zip_t;

namespace utils
{

  class QTZIP_API QtZipFile : public QObject
  {
    Q_OBJECT

  public:
    static std::unique_ptr<QtZipFile> load(QString file_name, int compression_level = 6);
    static std::unique_ptr<QtZipFile> create(QString file_name, int compression_level = 6);

  public:
    ~QtZipFile() override;

    bool append_entry(const QString &entry_name);
    bool append_entry(const QString &entry_name, const QStringList &entry_names_to_merge);
    bool append_entry(const QString &entry_name, const QByteArray &byteArray);

    bool remove_entry(const QString &entry_name);
    bool remove_entry(const QStringList &entry_names);

    bool extract(const QString &extract_dir);
    bool extract(const QString &entry_name, const QString &extract_entry_name);
    bool extract(const QStringList &entry_names, const QString &extract_dir);

    [[nodiscard]] QStringList getEntryNames() const;
    [[nodiscard]] QString getFileName() const;
    [[nodiscard]] int getCompressionLevel() const;

    [[nodiscard]] bool hasEntryName(const QString &name) const;

  protected:
    explicit QtZipFile(QString file_name, int compression_level = 6);

  private:
    bool execute(char mode, const std::function<bool(zip_t *zip)> &function) const;

  private:
    QString m_file_name;
    int m_compression_level;
  };

}// namespace utils

#endif//FLOW_TOOLS_ZIP_FILE_H
