
#include "Folder.h"

void Message::save( Folder &f )
{

    // 将给定的 Folder 添加到我们的 Folder 集合中
    folders.insert(&f);

    // 同时将本 Message 添加到 f 的 Message 集合中
    f.addMsg(this);

}

void Message::remove( Folder &f )
{

    folders.erase(&f);
    f.remMsg(this);

}

// 将本 Message 添加到指向 rhs 的 folders 集合中
void Message::add_to_Folders( const Message &rhs )
{

    for( auto f : rhs.folders )
    {
        f->addMsg(this);    
    } 

}


// 拷贝构造函数
Message::Message( const Message &rhs ) : contents(rhs.contents), folders(rhs.folders)
{

    add_to_Folders(rhs);

}


void Message::remove_from_Folders()
{

    for( auto f : folders )    // 对于 folders 集合中的每个指针
        f->remMsg(this);

}


Message::~Message()
{

    remove_from_Folders();

}


Message& Message::operator=( const Message &rhs )
{

    remove_from_Folders();
    contents = rhs.contents;
    folders = rhs.folders;

    add_to_Folders(rhs);

    return *this;

}

void swap( Message &lhs, Message &rhs )
{
    using std::swap;

    // 1. 先删除
    lhs.remove_from_Folders();
    
    rhs.remove_from_Folders();
    
    // 2. 交换内容
    swap( lhs.folders, rhs.folders );   // swap( set&, set& )
    swap( lhs.contents, rhs.contents ); // swap( string&, string& )

    // 3. 添加
    lhs.add_to_Folders(lhs);
    
    lhs.add_to_Folders(rhs);

}

void Message::debug_print()
{
    std::cout << "Message : " << contents << "\n"; 
    std::cout << "Appears in : " << folders.size() << " Folders\n"; 
}



///////***********Folder implement**********************///////////

void swap( Folder &lhs, Folder &rhs )
{

    using std::swap;

    for( auto m : lhs.msgs )
        m->remFldr(&lhs); 
    
    // lhs.remove_from_Messages();
    // rhs.remove_from_Messages();


    for( auto m : rhs.msgs )
        m->remFldr(&rhs);

    swap( lhs.msgs, rhs.msgs );

    for( auto m : lhs.msgs )
        m->addFldr(&lhs);
    
    for( auto m : rhs.msgs )
        m->addFldr(&rhs);

    // lhs.add_to_Messages(lhs);
    // rhs.add_to_Messages(rhs);

}



void Folder::add_to_Messages( const Folder &f )
{

    for( auto m : f.msgs )
        m->addFldr(this);

}

Folder::Folder( const Folder &rhs ) : msgs(rhs.msgs)
{
    add_to_Messages(rhs);
}


void Folder::remove_from_Messages()
{
    for( auto m : msgs )
        m->remFldr(this);
}

Folder::~Folder()
{
    remove_from_Messages();

}


Folder& Folder::operator=( const Folder &rhs )
{

    remove_from_Messages();

    msgs = rhs.msgs;
    add_to_Messages(rhs);

    return *this;

}

void Folder::debug_print()
{
    std::cout << "Folder contains : " << msgs.size() << " messages\n";

    int n = 1;
    for( auto m : msgs )
        std::cout << "Message " << n++ << " : " << m->contents << "\n";

}