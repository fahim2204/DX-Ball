#ifndef BRICK_H
#define BRICK_H


class Brick
{
    public:
        float brickPosX, brickPosY;
        bool isDead = false;

        Brick(float x, float y);
        CreateBrick();
        virtual ~Brick();

    protected:

    private:
};

#endif // BRICK_H
