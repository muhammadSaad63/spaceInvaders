class Laser{
    private:
        float posX;
        float posY;
        float width;
        float height;

        int speed;
        bool active;
        
    public:
        Laser(int posX, int posY){
            this->posX = posX;
            this->posY = posY;

            width = 5;
            height = 25;
            speed = 9;
            active = true;
        }
        void update(Player playerType){
            switch (playerType)
            {
                case USER:                                         
                    posY -= speed;                                  // if the user fired the laser, decrease its posX by speed (ie move it up)
                    if (posY <= 0){
                        deActivate();
                        // cout << "[GAME] Laser deactivated!\n";
                    }
                    break;     
                case ALIEN: 
                    posY += speed;                                  // if the aliens fired the laser, increase its posX by speed (ie move it down)
                    if ((posY + height) >= GetScreenHeight()){
                        deActivate();
                    }
                    break;    
            }
        }
        void draw(){
            DrawRectangle(posX, posY, width, height, ORANGE);
        }
        Rectangle getRect(){
            return Rectangle{posX, posY, width, height};
        }
        bool isActive(){
            return active;
        }
        void deActivate(){
            active = false;
        }
};