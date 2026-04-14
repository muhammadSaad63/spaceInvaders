#include "backGround.hpp"


// ----- Grid --------------------------------------------------------------------------------

Grid::Grid() 
    : cellSize(40)
    , screenWidth(GetScreenWidth())
    , screenHeight(GetScreenHeight())
    , fullScreened(false)
    , gridColor(ColorAlpha(Color{0, 200, 255, 255}, 0.15f))        // light bluish color with a transparency/alpha of .15
    , backgroundColor(Color{5, 5, 20, 255})                        // dark bluish/black bg 
    {}

void Grid::draw(const bool fullScreen, const bool showGrid){
    ClearBackground(backgroundColor);

    if (fullScreen && !fullScreened){
        fullScreenWidth  = GetScreenWidth();
        fullScreenHeight = GetScreenHeight();
        fullScreened = true;
    }

    if (showGrid){
        int width  = ((fullScreen)? fullScreenWidth  : screenWidth);
        int height = ((fullScreen)? fullScreenHeight : screenHeight);

        // vertical lines
        for (auto x {0}; x < width; x += cellSize)
            DrawLine(x, 0, x, height, gridColor);

        // horizontal lines  
        for (auto y {0}; y < height; y += cellSize)
            DrawLine(0, y, width, y, gridColor);
    }
}


// ----- Stars -------------------------------------------------------------------------------------

Stars::Stars() 
    : screenWidth(GetScreenWidth())
    , screenHeight(GetScreenHeight())
    , numStars(163)
    , baseAlpha(0.2f)
    , maxAlpha(1.0f)
    {
        stars.reserve(numStars);             // reserving spaces for 163 stars beforehand
        generateStars();
    }

void Stars::generateStars(){
    for (auto star {0}; star < numStars; ++star)
    {
        stars.push_back( 
            Star{
                (float) GetRandomValue(0, screenWidth),         // centreX
                (float) GetRandomValue(0, screenHeight),        // centreY
                (float) GetRandomValue(1, 5) * 0.5f,            // radius; 0.5f since func cant have float arguments

                (float) GetRandomValue(1, 10),                  // twinkleSPeed
                (float) GetRandomValue(0, (2*PI)*100) / 100,    // twinkleOffset; just in case; 0 to 628(2pi * 100 ie) which is the max period of a sin wave
                (float) 0.4f,                                   // alpha

                (float) GetRandomValue(1, 100) / 20.0f          // descentSpeed; between 0.05 and 5.0
            }
        );
    }
}

// i think this first time that update() is before draw()... :>
void Stars::update(){
    double currTime = GetTime();            // taking this as the "x" or "theta" here since its constantly changing/increasing
    
    for (auto& star : stars){
        // star.alpha = (baseAlpha + (maxAlpha * (1.0f + sin(currTime * star.twinkleSpeed + star.twinkleOffset))));                         // credits to claude
        star.alpha = (baseAlpha + ((maxAlpha - baseAlpha) * (1.0f + std::sin(currTime * star.twinkleSpeed + star.twinkleOffset))/2));            // sin orig returns -1 to 1; offsetting by +1f to make its range 0 to 2f; sin/2 -> 0 to 1f

        // Move stars downwards
        star.centreY += star.descentSpeed;
        if (star.centreY > screenHeight){
            star.centreY = (-star.radius);
            star.centreX = (float) GetRandomValue(0, screenWidth);
        }
    }
}

void Stars::draw(){
    for (const auto& star : stars){
        // DrawCircle(star.centreX, star.centreY, star.radius, WHITE);
        DrawCircleV({star.centreX, star.centreY}, star.radius, ColorAlpha(WHITE, star.alpha));                  // color alpha to change WHITE's alpha/transparency
    }
}


// ----- BackGround --------------------------------------------------------------------------------

void BackGround::draw(const bool fullScreen, const bool showGrid){
    grid.draw(fullScreen, showGrid);
    stars.draw();
}

void BackGround::update(){
    stars.update();
}