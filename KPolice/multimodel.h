#ifndef MULTIMODEL_H
#define MULTIMODEL_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QWidget>
class MultiModel : public QWidget
{
	Q_OBJECT
public:
	explicit MultiModel(QWidget *parent = nullptr);
	bool isLaunch = 0;
	bool isServer = 0;
	//tcp模块
	QTcpServer *tcpServer; //作为服务端
	QTcpSocket *tcpSocket; //作为客户端
	void sendMessage(QTcpSocket *socket, QString &content);
	void GetMessage(QTcpSocket *sender);
	void handleInformation(QString &content);

	//udp模块
	QUdpSocket *udpsocket; //刷新时交流主机信息
	qint64 start;
	void udptoGetHost();
	void udpHandleInfo();

signals:
};

#endif // MULTIMODEL_H
