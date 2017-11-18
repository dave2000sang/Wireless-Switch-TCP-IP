

#ifndef __S_APP_H__
#define __S_APP_H__

#include "object.h"

#include "message.h"




class s_app_t : public s_object_t
{
public:
    s_app_t();
    ~s_app_t();

public:    
    static s_app_t* get_app();
    virtual int start();
    virtual int stop();
    virtual int run();
    int is_quit();
	
	int light_on();
	int light_off();
private:
	static void * thread_keyboard_entry(void *);
	int run_keyboard();
private:
	int m_run_state;
		
	s_message_t * m_msg;
		

	thread_t m_keyboard_thread;

	int64	m_last_ms;
	int m_exit;


	int m_alpha1;
	int m_alpha2;
	};
	
#endif
	

