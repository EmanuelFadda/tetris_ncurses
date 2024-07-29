class Block {
    private: 
        int x;
        int y;

    public: 
        int coords[4][2];
        Block(int x, int y, int type);
        int getX();
        int getY();
        void add(int board[][10]);
        void rotate(int board[][10], int direction);
        void move(int dy, int dx, int board[][10]);
        bool checkCollision(int board[][10]);
        bool checkWall(int board[][10], int side);
        void collided(int board[][10]);
};