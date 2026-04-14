






class Alien{
    private:
        int posX;
        int posY;
        int row;
        int col;
        int active;
        Texture alien;
        float scale;

    public:
        Alien() : active(true) {}

        void draw(){
            if (active){
                // DrawTexture(texture, posX,);

            }
        }
        void update(){
            // 
        }
};
class Aliens{
    private:
        vector<vector<Alien>> aliens;               // 2D array of Alien

    public:
        //
        void draw(){
            for (auto& rowOfAliens : aliens){
                for (auto& alien : rowOfAliens){
                    alien.draw();
                }
            }
        }
        void update(){
            for (auto& rowOfAliens : aliens){
                for (auto& alien : rowOfAliens){
                    alien.update();
                }
            }
        }
};