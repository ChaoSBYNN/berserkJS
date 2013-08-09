#include "mywebpage.h"

MyWebPage::MyWebPage()
{
    defaultUserAgent = QWebPage::userAgentForUrl(this->mainFrame()->url()) + " berserkJS";
    // 开启开发者工具
    settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    // 其他设置
    settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, true);
    settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    settings()->setAttribute(QWebSettings::JavascriptEnabled, true);
    settings()->setAttribute(QWebSettings::AutoLoadImages, true);
    settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    settings()->setAttribute(QWebSettings::JavascriptCanAccessClipboard, true);
    settings()->setAttribute(QWebSettings::OfflineStorageDatabaseEnabled, true);
    settings()->setAttribute(QWebSettings::OfflineWebApplicationCacheEnabled, true);
    settings()->setAttribute(QWebSettings::LocalStorageEnabled, true);

    // 开启，功能待测。
    settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls, true);
    // 启用后台渲染将导致操作渲染错误
    //page->settings()->setAttribute(QWebSettings::TiledBackingStoreEnabled, true);
}

bool MyWebPage::supportsExtension(Extension extension) const {
    return extension == ChooseMultipleFilesExtension;
}

QString MyWebPage::chooseFile(QWebFrame *originatingFrame, const QString &oldFile) {
    Q_UNUSED(originatingFrame);
    Q_UNUSED(oldFile);
    return uploadFile;
}

bool MyWebPage::extension(Extension extension, const ExtensionOption* option, ExtensionReturn* output)
{
    Q_UNUSED(option);

    if (extension == ChooseMultipleFilesExtension) {
        static_cast<ChooseMultipleFilesExtensionReturn*>(output)->fileNames = QStringList() << uploadFile;
        return true;
    } else {
        return false;
    }
}

QString MyWebPage::setUserAgent(const QString & userAgent)
{
    myUserAgent = userAgent;
    return myUserAgent;
}

QString MyWebPage::userAgent()
{
    if (!myUserAgent.isNull() || !myUserAgent.isEmpty()) {
      return myUserAgent;
    }
    return defaultUserAgent;
}

QString MyWebPage::userAgentForUrl(const QUrl & url) const
{
    if (!myUserAgent.isNull() || !myUserAgent.isEmpty()) {
      return myUserAgent;
    }
    return defaultUserAgent;
}


void MyWebPage::javaScriptConsoleMessage(const QString & message, int lineNumber, const QString & sourceID)
{
    emit pageConsoleMessage(message, lineNumber, sourceID);
}

bool MyWebPage::javaScriptPrompt(QWebFrame* frame, const QString & msg, const QString & defaultValue, QString* result)
{
    emit pagePrompt(msg, defaultValue);
    return false;
}


void MyWebPage::javaScriptAlert(QWebFrame* frame, const QString& msg)
{
    emit pageAlert(msg);
}


bool MyWebPage::javaScriptConfirm(QWebFrame* frame, const QString & msg)
{
    emit pageConfirm(msg);
    return false;
}

