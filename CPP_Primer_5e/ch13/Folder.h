

#ifndef __FOLDER_H
#define __FOLDER_H

#include <string>
#include <set>
#include <iostream>

class Folder;

class Message
{
    private:
        friend class Folder;
        friend void swap( Message &, Message & );
        // friend void swap( Folder &, Folder & );

    public:
        
        explicit Message( const std::string &str = "" ) : contents(str) {}

        Message( const Message & );

        Message& operator=( const Message & );

        // 移动构造函数
        Message( Message && ) ;

        // 移动赋值运算符
        Message &operator=( Message && ) ;


        ~Message();

        // 从给定 Folder 集合中添加/删除本 Message
        void save( Folder & );  
        void remove( Folder & );

        void debug_print();


    private:
        std::string contents;   // 消息文本内容
        std::set<Folder*> folders;  // 包含本 Message 的 Folder 集合

        // 将本 Message 添加到指向参数的 Folder 中
        void add_to_Folders( const Message & );     // 拷贝构造和拷贝赋值调用
        // 从 folders 中的 每个 Folder 中删除本 Message
        void remove_from_Folders();   // ~Message() 析构函数调用

        // 从本 Message 移动 Folder 指针
        void move_Folders( Message *m );

        void addFldr( Folder *f ) { folders.insert(f); }
        void remFldr( Folder *f ) { folders.erase(f); }


};

void swap( Message &, Message & );


class Folder
{
    
    private:
        friend class Message;
        // friend void swap( Message &, Message & );
        friend void swap( Folder &, Folder & );

    public:
        

        Folder() = default;
        Folder( const Folder & );
        Folder& operator=( const Folder & );

        Folder( Folder && ) ;
        Folder& operator=( Folder && ) ;
        
        ~Folder();


        void debug_print();


    private:
        std::set<Message*> msgs;
        
        void add_to_Messages( const Folder & );
        void remove_from_Messages();

        // 从本 Folder 中移动 msgs 指针
        void move_Messages( Folder * );

        void addMsg(Message *m) { msgs.insert(m); }
        void remMsg(Message *m) { msgs.erase(m); }
        

};

void swap( Folder &, Folder & );

#endif