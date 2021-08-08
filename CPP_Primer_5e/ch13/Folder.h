

#ifndef __FOLDER_H
#define __FOLDER_H

class Folder;

class Message
{

    public:
        friend class Folder;

        explicit Message( const std::string &str = "" ) : contents(str) {}

        Message( const Message & );

        Message& operator=( const Message & );

        ~Message();

        void save( Folder & );  // 从给定 Folder 集合中添加本 Message
        void remove( Folder & );    // 从给定 Folder 集合中删除本 Message


    private:
        std::string contents;   // 消息文本
        std::set<Folder*> folders;  // 包含本 Message 的 Folder

        // 将本 Message 添加到指向参数的 Folder 中
        void add_to_Folders( const Message & );

        // 从 folder 中的 每个 Folder 中删除本 Message
        void remove_to_Folders();   




};


#endif