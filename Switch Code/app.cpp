
#include "app.h"
#include "message.h"
#include "log.h"
#include "utilities.h"
#include <math.h>
#include <wiringPi.h>

using namespace s_log;
using namespace s_utilities;

#define GPIO_1 17

s_app_t::s_app_t()
{
	m_msg = s_message_t::get_inst();

		
    CREATE_THREAD(m_keyboard_thread, thread_keyboard_entry, 0x8000, this, 1);         // Reserve 32KB stack

	m_last_ms = 0;

	m_exit = 0;
	
	m_msg->start();

}

s_app_t::~s_app_t()
{
	m_msg->stop();

}

s_app_t* s_app_t::get_app()
{
	static s_app_t * g_app = NULL;
	if( !g_app )
		g_app = new s_app_t();

	return g_app;
}

int s_app_t::start()
{
	if( is_started() )
		return 0;
	s_object_t::start();


	m_run_state = 0;
	return 0;
}

int s_app_t::stop()
{
	s_log_info("app stop\n");
	if( !is_started() )
		return 0;
	s_object_t::stop();

	return 0;
}

int s_app_t::light_on()
{
	digitalWrite (GPIO_1, HIGH); 
	return 0;
}

int s_app_t::light_off()
{
 	digitalWrite (GPIO_1, LOW); 
	return 0;
}

int s_app_t::run_keyboard()
{
	char ch;

	while(1)
	{
		ch = getchar();
		s_log_info("ch=%c\n", ch);
		switch(ch)
		{
			case 'a':
				break;
			case 'A':
				break;					
			case '0':
				break;
			case '1':
				break;
			case '2':
				break;
			case '3':
				break;
			case '4':
				break;
			case '5':
				break;				
			case '6':
				break;

			case 'm':

				break;
			case 'q':				

				break;

		}
		if( ch == 'q')
			break;
	}
	m_exit = 1;
	if( m_quit) 
		m_exit = 2;
	return 0;
}

int s_app_t::is_quit()
{
	return (m_exit == 2);
}

void * s_app_t::thread_keyboard_entry(void * pval)
{
   	s_app_t *papp = (s_app_t*)pval;

	papp->run_keyboard();
	return NULL;
}

int s_app_t::run()
{
	while(!this->m_quit)
	{
		if( m_exit == 1)
			break;
	 	switch( m_run_state )
		{
	 	}
		s_sleep_ms(50);
	}
	m_quit = 1;
	s_log_info("s_app_t::run EXIT quit:%d\n", this->m_quit);
	if( m_exit == 1 )
	{
		stop();
		m_exit = 2;
	}

	return 0;
}


