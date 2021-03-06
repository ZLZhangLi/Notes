/*
 * 代码完成时间： 2015-4-12 03：07 AM
 * Unix Socket通信，采用TCP方式
 * 服务端程序
 * 主要功能：使用IO复用(select)同时接受多个用户请求。
 * 每登录一个用户，系统会给予提示。
 * 每一个用发送的消息都能够显示在服务端并注明发送者。
 * 当用户发送close消息时关闭服务端和其它所有与服务端相连的客户端。
 */

/**
 *
 * @author dainslef
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>

#define USER_MAX 10						//定义最大用户数量
#define MSG_SIZE 50						//定义单次发送字符串最大长度

int sock_fd = 0;
int max_fd = 0;							//设置最大描述符大小
int user_count = 0;						//用户数量计数
int client_fd[USER_MAX];				//用一个数组来保存所有用户的连接socket描述符

void* get_accept(void* arg)
{
	while (1)
	{
		if ((client_fd[user_count] = accept(sock_fd, NULL, NULL)) == -1)
			break;			//BSD系列在关闭socket时可能会产生新的请求
		else
		{
			//最大文件描述符值为监听文件描述符集合中的最大值加1
			if (client_fd[user_count] >= max_fd)
				max_fd = client_fd[user_count] + 1;

			write(client_fd[user_count], &user_count, 4);
			printf("有用户加入socket！当前用户数量为：%d人。\n", ++user_count);
		}
	}

	return NULL;
}

int main(void)
{
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd == -1)
	{
		perror("初始化socket失败");
		return 0;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9999);			//当主机端与客户端数据类型兼容时，端口号可以不做转换
	addr.sin_addr.s_addr = INADDR_ANY;		//代表接收任意地址的数据

	if (bind(sock_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
	{
		perror("绑定端口失败");
		close(sock_fd);
		return 0;
	}

	if (listen(sock_fd, USER_MAX) == -1)
	{
		perror("监听端口失败");
		close(sock_fd);
		return 0;
	}

	//记录接收数据次数
	int msg_count = 0;
	//描述符集合
	fd_set read_set;

	//创建独立线程来接收请求
	pthread_t thread_fd;
	pthread_create(&thread_fd, NULL, get_accept, NULL);

	while (1)
	{
		//select()调用每次运行前都需要置空，之后重设需要监听的文件描述符
		FD_ZERO(&read_set);
		for (int i = 0; i < user_count; i++)
			FD_SET(client_fd[i], &read_set);

		//设置select()超时时间，全部为0则不阻塞
		struct timeval time;
		time.tv_sec = 2;
		time.tv_usec = 0;

		//select()返回变动的文件描述符数目
		if (select(max_fd, &read_set, NULL, NULL, &time) > 0)
			for (int i = 0; i < user_count; i++)
				if (FD_ISSET(client_fd[i], &read_set))
				{
					char message[MSG_SIZE];
					memset(message, 0, MSG_SIZE);

					if (read(client_fd[i], message, MSG_SIZE) == -1)
						perror("接收消息失败");
					else
					{
						if (!strcmp(message, ""))
							continue;
						if (!strcmp(message, "close"))
						{
							printf("收到关闭命令！\n关闭socket端口监听！\n");
							for (int i = 0; i < user_count; i++)		//收到关闭信息之后向所有客户端发送关闭消息
								write(client_fd[i], message, MSG_SIZE);
							goto END;
						}
						printf("第%d次接收，接收到来自用户[%d]的消息：%s\n", ++msg_count, i, message);
					}
				}
	}

END:
	for (int i = 0; i < user_count; i++)
		close(client_fd[i]);
	close(sock_fd);
	return 0;
}
