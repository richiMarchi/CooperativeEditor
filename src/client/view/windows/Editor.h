#ifndef COOPERATIVEEDITOR_EDITOR_H
#define COOPERATIVEEDITOR_EDITOR_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QMenuBar>
#include <QToolBar>
#include <QPlainTextEdit>
#include <QString>
#include <QVBoxLayout>
#include <QAction>

/**
 * Editor application window
 */
class Editor : public QMainWindow {

Q_OBJECT

private:
    QWidget *mainWidget;
    QTextEdit *textEdit;
    QMenuBar *topBar;
    QToolBar *toolBar;

    void createTopBar(QVBoxLayout *layout);
    void createToolBar(QVBoxLayout *layout);
    int getCursorPos();

public:

    explicit Editor(QWidget *parent = nullptr);
    bool eventFilter(QObject *editor, QEvent *event) override ;

public slots:

    ///Slot to notify the editor that a remote op. has been performed
    void onRemoteUpdate(QString text);

signals:
    ///Signal emitted when the user wants to edit his profile
    void openEditProfileFromEditor();

    ///Signal emitted when the user inserts a symbol in the editor
    void symbolInserted(QString character, int position);

    ///Signal emitted when the user deletes a symbol in the editor
    void symbolDeleted(int position);

};

#endif //COOPERATIVEEDITOR_EDITOR_H
