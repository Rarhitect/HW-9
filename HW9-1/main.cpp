//
//  main.cpp
//  HW9-1
//
//  Created by Alyaev Roman on 05.04.2021.
//

#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>

/*
 
 Необходимо создать два потока.
 
 Первый поток будет ожидать ввода сообщения пользователем (на операторе ввода), добавлять сообщение в контейнер и пробуждать все ожидающие сообщений потоки через условную переменную.
 
 Второй поток будет ожидать поступления нового сообщения (на условной переменной), извлекать сообщение и выводить его.
 
 Оба потока выполняют свои действия в цикле до тех пор, пока пользователь не введет сообщение типа exit, означающее завершение работы текущего клиента.
 
 */

std::mutex g_mutex;
std::condition_variable g_condition_var;

void input_thread()
{
    
}

void output_thread()
{
    
}

int main(int argc, const char * argv[])
{
    using allocator = boost::interprocess::allocator < char,
        boost::interprocess::managed_shared_memory::segment_manager > ;

    using string = boost::interprocess::basic_string < char,
        std::char_traits < char >, allocator> ;
    
    const std::string shared_memory_name = "managed_shared_memory";

    boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());

    boost::interprocess::managed_shared_memory shared_memory(
        boost::interprocess::open_or_create, shared_memory_name.c_str(), 1024);
    
    //Здесь должен быть цикл для обмена сообщениями

    boost::interprocess::shared_memory_object::remove(shared_memory_name.c_str());
    
    return 0;
}
