#pragma once
#include <QWidget>

class QGraphicsBlurEffect;
class QLabel;

class MyAcrylicWidget : public QWidget
{
	Q_OBJECT
private:
	const int timerBlurDuration = 20;
private:
	QTimer* m_timerBlur;
	QGraphicsBlurEffect* m_effectBlur;
	QLabel* m_lblBlur;
	QPixmap m_pixBlurBackground;
	QPoint m_pntStartMove;
public:
	MyAcrylicWidget(QWidget *parent = nullptr);
	~MyAcrylicWidget();
private:
	//初始化 Timer
	void initTimer();
	//初始化 Label
	void initLabel();
	//初始化效果
	void initEffect();
	//初始化关联
	void initConnection();
private:
	void mousePressEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* e) override;
	void mouseReleaseEvent(QMouseEvent* e) override;
private slots:
	//更新模糊的背景
	void updateBlurBackground();
};
