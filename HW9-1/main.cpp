//
//  main.cpp
//  HW9-1
//
//  Created by Alyaev Roman on 05.04.2021.
//

#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <atomic>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

void cin_thread()
{
    using namespace boost::interprocess;
 
    typedef allocator < char, managed_shared_memory::segment_manager > CharAllocator;
    typedef basic_string < char, std::char_traits<char>, CharAllocator > MyShmString;
    typedef allocator < MyShmString, managed_shared_memory::segment_manager > StringAllocator;
    typedef vector < MyShmString, StringAllocator > MyShmStringVector;
    
    const std::string shared_memory_name = "managed_shared_memory";
    shared_memory_object::remove(shared_memory_name.c_str());
    managed_shared_memory shared_memory(open_or_create, shared_memory_name.c_str(), 10000);
    
    //Create allocators
    CharAllocator     charallocator  (shared_memory.get_segment_manager());
    StringAllocator   stringallocator(shared_memory.get_segment_manager());
    
    MyShmStringVector *vector = shared_memory.construct < MyShmStringVector > ("vector")(stringallocator);
    
    auto mutex = shared_memory.construct < interprocess_mutex > ("mutex")();
    auto condition_var = shared_memory.construct < interprocess_condition > ("condition_var")();
    
    MyShmString message(charallocator);
    message = "EXIT_SUCCES";
    
    do
    {
        std::cin >> message;
        
        std::lock_guard < interprocess_mutex > lock(*mutex);
        
        vector->push_back(message);
        
        condition_var->notify_all();
    }
    while(message != "EXIT_SUCCESS");
    
    //проверить счетчик запущенных экземпляров и если 0, то сделать remove
    std::atomic<int> counter_of_examples = 0; //надо как-то грамотно его вписать в ход программы...
    if (counter_of_examples == 0)
    {
        shared_memory_object::remove(shared_memory_name.c_str());
    }
}

void cout_thread()
{
    
}

int main(int argc, const char * argv[])
{
    using namespace boost::interprocess;
 
    typedef allocator<char, managed_shared_memory::segment_manager> CharAllocator;
    typedef basic_string<char, std::char_traits<char>, CharAllocator> MyShmString;
    typedef allocator<MyShmString, managed_shared_memory::segment_manager> StringAllocator;
    typedef vector<MyShmString, StringAllocator> MyShmStringVector;
    
    const std::string shared_memory_name = "managed_shared_memory";

    shared_memory_object::remove(shared_memory_name.c_str());

    managed_shared_memory shared_memory(open_or_create, shared_memory_name.c_str(), 10000);
    
    //Здесь должен быть цикл для обмена сообщениями

    shared_memory_object::remove(shared_memory_name.c_str());
    
    return 0;
}
