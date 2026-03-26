#include "multimodel.h"
#include <QHostInfo>
#include <QNetworkDatagram>
#include <qdatetime.h>
MultiModel::MultiModel(QWidget *parent)
	: QWidget{parent}
{
	tcpServer = new QTcpServer(this); //作为服务端

	tcpSocket = new QTcpSocket(this); //作为客户端

	udpsocket = new QUdpSocket(this); //刷新时交流主机信息
	udpsocket->bind(9999);
	connect(udpsocket, &QUdpSocket::readyRead, this, &MultiModel::udpHandleInfo);
}
//下一步写出hostinfolist,参照setup中的QListWidget，借助豆包之力setitemwidget
//设置界面显示相反操作，客户端禁用操作，各自负责逻辑操作，相互之间发送信息确认位置和速度//有影子对局风险，但是能够使对局解耦
//完成链接后就是处理两种信号，pos和speed0.5秒更新一次，还有setup的时候一次性传四个设置
void MultiModel::udptoGetHost()
{
	if (this->isLaunch && !this->isServer)
	{
		udpsocket->writeDatagram("FindHost", QHostAddress::Broadcast, 9999);
	}
}
void MultiModel::udpHandleInfo()
{
	if (this->isLaunch)
	{
		if (this->isServer) //主机端
		{
			while (udpsocket->hasPendingDatagrams())
			{
				QNetworkDatagram datagram = udpsocket->receiveDatagram();
				if (datagram.data() == "FindHost")
				{
					QString hostInfo = QHostInfo::localHostName() + "|" + QHostAddress(QHostAddress::LocalHost).toString();
					udpsocket->writeDatagram(hostInfo.toUtf8(), datagram.senderAddress(), 9999);
				}
				else if (datagram.data() == "ping")
				{
					udpsocket->writeDatagram("pong", datagram.senderAddress(), 9999);
				}
			}
		}
		else if (!this->isServer) //客户端
		{
			while (udpsocket->hasPendingDatagrams())
			{
				QNetworkDatagram datagram = udpsocket->receiveDatagram();
				if (datagram.data() != "pong")
				{
					QNetworkDatagram datagram = udpsocket->receiveDatagram();
					QStringList hostInfo = QString(datagram.data()).split("|");
					//利用这三个值搞一行
					QString hostList = hostInfo[0]; //这两个还没用
					QString hostIP = hostInfo[1];
					start = QDateTime::currentMSecsSinceEpoch();
					udpsocket->writeDatagram("ping", datagram.senderAddress(), 9999);
				}
				else
				{
					qint64 rtt = QDateTime::currentMSecsSinceEpoch() - start;
					QString pingLabel = (QString::number(rtt) + "ms");
				}
			}
		}
	}
}
void MultiModel::sendMessage(QTcpSocket *socket, QString &content)
{
	if (!socket || !socket->isOpen())
	{
		return;
	}
	int length = content.size();
	socket->write((char *) &length, sizeof(length));
	socket->write(content.toUtf8());
	socket->flush();
}

//收到信息
void MultiModel::GetMessage(QTcpSocket *sender)
{
	if (!sender || !sender->isOpen())
	{
		//QMessageBox::information(this, "提示", "无法完成信息发送，请检查链接");
		return;
	}
	int length = 0;
	while (sender->bytesAvailable() >= sizeof(int))
	{ // 至少能读取长度字段时才处理
		int length = 0;
		sender->read((char *) &length, sizeof(length));
		QByteArray data = sender->read(length);
		QString content = QString::fromUtf8(data);
		this->handleInformation(content);
	}
}
void MultiModel::handleInformation(QString &content) {}
