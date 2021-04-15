module Chat
{
    exception UsernameAlreadyRegisteredException {};
    exception RoomNameAlreadyRegisteredException {};
    exception NoRoomFactoryAvailableException {};

    interface ChatUser
    {
        void sendMessage(ChatUser* from, string message);
        string getName();
        void sendPrivateMessage(ChatUser* from, string message);
    };

    sequence<ChatUser*> UserList;

    interface ChatRoom
    {
        void sendMessage(ChatUser* from, string message);
        void addUser(ChatUser* who);
        void removeUser(ChatUser* who);
        UserList getUsers();
        string getName();
    };

    interface ChatRoomFactory
    {
        ChatRoom* createChatRoom(string name);
        int numOfChatroomsRunning();
    };

    sequence<ChatRoom*> ChatRoomList;

    interface ChatServer
    {
        void registerUser(ChatUser* who) throws UsernameAlreadyRegisteredException;
        void unregisterUser(ChatUser* who);
        ChatRoomList getRooms();
        ChatRoom* createChatRoom(string name) throws NoRoomFactoryAvailableException, RoomNameAlreadyRegisteredException;
        void registerChatRoomFactory(ChatRoomFactory* factory);
        void unregisterChatRoomFactory(ChatRoomFactory* factory);
    };
};

