#include "webbrowser.h"
#include <QLineEdit>
#include <QWebEngineView>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>
#include <QWebEngineHistory>

WebBrowser::WebBrowser(QWidget *wgt) : QWidget(wgt){
    m_ptxt = new QLineEdit("http://google.com");
    m_pwv = new QWebEngineView;
    m_pcmdBack = new QPushButton("<");
    m_pcmd_Forward = new QPushButton(">");

    m_pcmdBack->setEnabled(false);
    m_pcmd_Forward->setEnabled(false);

    QProgressBar *pprb = new QProgressBar;
    QPushButton *pcmdGo = new QPushButton("&Go");
    QPushButton *pcmdStop = new QPushButton("&Stop");
    QPushButton *pcmdRefresh = new QPushButton("&Refresh");

    connect(pcmdGo,SIGNAL(clicked()),SLOT(slotGo()));
    connect(m_ptxt,SIGNAL(returnPressed()),SLOT(slotGo()));
    connect(m_pcmdBack,SIGNAL(clicked()),m_pwv,SLOT(back()));
    connect(m_pcmd_Forward,SIGNAL(clicked()),m_pwv,SLOT(forward()));
    connect(pcmdRefresh,SIGNAL(clicked()),m_pwv,SLOT(reload()));
    connect(pcmdStop,SIGNAL(clicked()),m_pwv,SLOT(stop()));
    connect(m_pwv,SIGNAL(loadProgress(int)),pprb,SLOT(setValue(int)));
    connect(m_pwv,SIGNAL(LoadFinished(bool)),m_pwv,SLOT(slotFinished(bool)));

    QHBoxLayout *phbx = new QHBoxLayout;
    phbx->addWidget(m_pcmdBack);
    phbx->addWidget(m_pcmd_Forward);
    phbx->addWidget(pcmdStop);
    phbx->addWidget(pcmdRefresh);
    phbx->addWidget(m_ptxt);
    phbx->addWidget(pcmdGo);

    QVBoxLayout *playaout = new QVBoxLayout;
    playaout->addLayout(phbx);
    playaout->addWidget(m_pwv);
    playaout->addWidget(pprb);
    setLayout(playaout);

    slotGo();
}

void WebBrowser::slotGo(){
    if(!m_ptxt->text().startsWith("ftp://") && !m_ptxt->text().startsWith("http://") && !m_ptxt->text().startsWith("gother://") && !m_ptxt->text().startsWith("https://"))
        m_ptxt->setText("https://"+  m_ptxt->text());
    m_pwv->load(QUrl(m_ptxt->text()));


    m_pcmdBack->setEnabled(m_pwv->page()->history()->canGoBack());
    m_pcmd_Forward->setEnabled(m_pwv->page()->history()->canGoForward());
}

void WebBrowser::slotFinished(bool bok){
    if(!bok)
        m_pwv->setHtml("<CENTER>An error has occured while loading the web page </CENTER>");
    m_ptxt->setText(m_pwv->url().toString());

    m_pcmdBack->setEnabled(m_pwv->page()->history()->canGoBack());
    m_pcmd_Forward->setEnabled(m_pwv->page()->history()->canGoForward());
}
