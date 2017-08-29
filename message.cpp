

#include "message.h"
#include "app.h"
#include "log.h"
#include "utilities.h"

using namespace s_log;
using namespace s_utilities;

#define TCP_PORT 4000

s_message_t::s_message_t()
{
	m_tcp = new s_tcp_t(TCP_PORT);
	
	m_tcp_buf = new s_msg_buf_t;
	m_tcp_buf->m_addr = new char[1024*8];
	m_tcp_buf->m_size = 1024*8;
	m_tcp_buf->m_wpos = 0;
	m_tcp_buf->m_rpos = 0;
}

s_message_t::~s_message_t()
{
	if( m_tcp )
		delete m_tcp;

	delete m_tcp_buf->m_addr;
	delete m_tcp_buf;
}
s_message_t * s_message_t::get_inst()
{
	static s_message_t * g_message = NULL;
	if ( !g_message )
		g_message = new s_message_t();

	return g_message;
}

int s_message_t::start()
{
	m_tcp->set_callback(tcp_recv_callback, (void*)this);
	m_tcp->start();
	return 0;
}

int s_message_t::stop()
{
	m_tcp->stop();
	return 0;
}

int s_message_t::tcp_recv_callback(void * parent,void * para)
{
	s_message_t * msg;
	s_buffer_t * buf;
	msg = (s_message_t*)parent;
	buf = (s_buffer_t*)para;

//RINT_INFO("tcp_recv_callback len:%d %s\n", buf->m_length, buf->m_buffer);
	memcpy(msg->m_tcp_buf->m_addr + msg->m_tcp_buf->m_wpos, buf->m_buffer, buf->m_length + 1);
	msg->m_tcp_buf->m_wpos += buf->m_length;

	msg->tcp_parser();
	return 0;	
}

int s_message_t::tcp_parser()
{
#if 1
	s_app_t * s_app = s_app_t::get_app();
	int cmd = 0;
	PRINT_INFO("tcp_parser %s\n", m_tcp_buf->m_addr);
	if( strstr(m_tcp_buf->m_addr, "LIGHTON") != 0 )
		cmd = S_CMD_LIGHT_ON;
	else if( strstr(m_tcp_buf->m_addr, "LIGHTOFF") != 0)
		cmd = S_CMD_LIGHT_OFF;

	
	switch ( cmd )
	{

		case S_CMD_LIGHT_ON:
			s_app->light_on();
			break;
		case S_CMD_LIGHT_OFF:
			s_app->light_off();
			break;
	}
	// just clear all, need to improvement
	m_tcp_buf->m_wpos = 0;
	m_tcp_buf->m_addr[0] = 0;
#endif	
	return 0;
}
