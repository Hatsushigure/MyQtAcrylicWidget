#include "MyAcrylicWidget.h"
#include <QTimer>
#include <QScreen>
#include <QApplication>
#include <QGraphicsBlurEffect>
#include <QLabel>
#include <QMouseEvent>
#ifdef Q_OS_WINDOWS
#include <Windows.h>
#endif

MyAcrylicWidget::MyAcrylicWidget(QWidget *parent)
	: QWidget(parent)
{
#ifdef Q_OS_WINDOWS
	SetWindowDisplayAffinity((HWND)winId(), WDA_EXCLUDEFROMCAPTURE);
#else
#error Sorry, but currently I cannot support other platform.
#endif
	setWindowFlags(Qt::FramelessWindowHint);

	initTimer();
	initLabel();
	initEffect();
	initConnection();
}

MyAcrylicWidget::~MyAcrylicWidget()
{
}

//初始化 Timer
void MyAcrylicWidget::initTimer()
{
	m_timerBlur = new QTimer(this);
	m_timerBlur->setInterval(timerBlurDuration);
	m_timerBlur->start();
}

//初始化 Label
void MyAcrylicWidget::initLabel()
{
	m_lblBlur = new QLabel(this);
	m_lblBlur->move(0, 0);
	m_lblBlur->resize(size());
}

//初始化效果
void MyAcrylicWidget::initEffect()
{
	m_effectBlur = new QGraphicsBlurEffect(this);
	m_effectBlur->setBlurHints(QGraphicsBlurEffect::BlurHint::AnimationHint);
	m_effectBlur->setBlurRadius(10);
	m_lblBlur->setGraphicsEffect(m_effectBlur);
}

//初始化关联
void MyAcrylicWidget::initConnection()
{
	connect(m_timerBlur, &QTimer::timeout, this, &MyAcrylicWidget::updateBlurBackground);
}

void MyAcrylicWidget::mousePressEvent(QMouseEvent* e)
{
	m_pntStartMove = e->globalPosition().toPoint();
}

void MyAcrylicWidget::mouseMoveEvent(QMouseEvent* e)
{
	QPoint tmpPoint = e->globalPosition().toPoint();
	QPoint dp = tmpPoint - m_pntStartMove;
	move(pos() + dp);
	m_pntStartMove = tmpPoint;
}

void MyAcrylicWidget::mouseReleaseEvent(QMouseEvent* e)
{
	QPoint tmpPoint = e->globalPosition().toPoint();
	QPoint dp = tmpPoint - m_pntStartMove;
	move(pos() + dp);
	m_pntStartMove = tmpPoint;

}

//更新模糊的背景
void MyAcrylicWidget::updateBlurBackground()
{
	QScreen* scr = QApplication::screenAt(rect().center());
	m_pixBlurBackground = scr->grabWindow(0, x(), y(), width(), height());
	m_lblBlur->setPixmap(m_pixBlurBackground);
}
