### TODO
---

todo
  >  get rid of todo lists in .cpp file
  >  break down .cpp into seperate .cpp files
  >  

chats
    [ebbi] Rename Src/ to src/ and update it in CMakeLists.txt, build.sh and build.bat
    [saad] dont 👆 
    [saad] kia zaroorat parhi thi aapko meray merge say pehlay merge karnay ki?!
           karna teh hi toh apni merge saad say banatay, main say nhi...
           ab meri puri commit history chali gayi: 21 in main vs 31ish in saad...
    [saad] btw, hamaray paas koi teesra banda nhi teh kia?
           dunno y kuch yaad arha hai
    [saad] cant we put .bat, .sh, and cmake.txt in a sep dir? main page mai ho kar 
           they cluttering it

[saad]
 instead of making it 3d, imma make it 2d. i alr got 2d spaceship loaded up. i will have the spaceship at the bottom of the screen and it can fire lasers up. there will be 5 menu icons/buttons: play, settings, shop, history, leaderboards.

how should i design the ui. use rectangles? also should ihave al of these 5 buttons in the mainmenu or combine some together in a submenu like... idk
Gemini said

Moving to 2D for the menu is a great call—it gives you that crisp, "pixel-perfect" arcade feel. Using Rectangles is the industry standard for UI because they are mathematically the easiest to check for collisions (using CheckCollisionPointRec).

Regarding your 5 buttons: for a Space Invaders style game, keep all 5 on the main screen. It makes the world feel "fuller" and gives the player a clear view of everything they can do.
1. The "Arcade Command" UI Layout

Since your ship is at the bottom, your buttons should be arranged in the top two-thirds of the screen. I recommend a V-Shape or Arc layout. This makes it feel like the ship is aiming at targets.
The Proposed Setup:

    Play: Center-top (The biggest target).

    Shop & Leaderboards: Mid-height, flanking the center.

    Settings & History: Lower-height, near the corners.

2. Using Rectangles vs. Rectangle Objects

In Raylib, don't just call DrawRectangle. Instead, define your buttons as Rectangle variables. This allows you to use the same variable for drawing and collision detection.
C++

// Define the buttons
Rectangle playBtn = { 300, 100, 200, 60 };
Rectangle shopBtn = { 150, 250, 150, 50 };
Rectangle leadBtn = { 500, 250, 150, 50 };

// In your Draw Loop:
DrawRectangleRec(playBtn, DARKGRAY);
DrawText("PLAY", playBtn.x + 60, playBtn.y + 15, 25, GREEN);

3. Interaction Design (The "Laser" Menu)

Since you're firing lasers to select options, here is how to handle the logic:

    Hover Effect: When the ship is lined up horizontally with a button, make that button glow (use DrawRectangleLinesEx for a border).

    The Hit: When a laser is active, check:
    C++

    if (CheckCollisionRecs(laserBox, playBtn)) {
        currentScreen = GAMEPLAY;
    }

    Visual Feedback: When a button is hit, don't just switch screens instantly. Make the button flash White or Yellow for 0.1 seconds so the player feels the "impact."

4. Why keep them all on one screen?
Button	Why it stays on Main Menu
Play	Obvious necessity.
Shop	Encourages the player to see what they can buy before they start.
Leaderboards	High-score games are all about competition; seeing this button motivates the player.
History	Great for "One more game" syndrome—seeing your last 5 runs makes you want to beat them.
Settings	Usually hidden, but in a retro game, a "Settings" box in the corner fits the aesthetic perfectly.
5. Visual "Space" Polish

    The Grid: Draw a very faint 2D grid behind the buttons (using DrawLine). It makes the UI look like a tactical radar.

    Floating: Give the buttons a tiny bit of "float" logic. Use sin(GetTime()) to make them bob up and down by 5 pixels. It makes the menu feel alive.

Would you like me to write the code for a "Laser" struct that handles moving the laser up the screen and checking for these button hits?



