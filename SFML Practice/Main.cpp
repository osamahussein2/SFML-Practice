// Include important libraries here
#include <SFML/Graphics.hpp>

// Make code easier to type with "using namespace"
using namespace sf;

/* I'm trying to learn SFML through this PDF (APA references):

	
	Horton. J. (2019). Beginning C++ Game Programming (Second Edition). Packt Publishing Ltd.
*/

// Visual Studio integrated development environment (IDE)

// This is where our game starts from
int main()
{
	// Create a video mode object
	VideoMode vm(Vector2u(1920, 1080));

	// Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", State::Fullscreen);

	/* A texture is a graphic stored in memory, on the graphics processing unit(GPU). An object that's made from the
	Sprite class needs an object made from the Texture class in order to display itself as an image */

	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	/* Textures take up graphics memory, and this memory is a finite resource. Furthermore, the process of loading a
	graphic into the GPU's memory is very slow – not so slow that you can watch it happen or that you will see your PC
	noticeably slow down while it is happening, but slow enough that you can't do it every frame of the game loop */

	// Load a graphic into the texture
 	textureBackground.loadFromFile("graphics/background.png");

	// Create a sprite
	Sprite spriteBackground(textureBackground);

	// Attach the texture to the sprite
	//spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(Vector2f(0, 0));


	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/

		/* This code checks whether the Esc key is currently being pressed. If it is, the highlighted code uses the window
		object to close itself. Now, the next time the while loop begins, it will see that the window object is closed and
		jump to the code immediately after the closing curly brace of the while loop and the game will exit */
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		{
			window.close();
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/

		/*
		****************************************
		Draw the scene
		****************************************
		*/

		// Clear everything from the last frame
		window.clear();

		/* Use the window object to draw the spriteBackground object, in between clearing the display and showing the
		newly drawn scene */

		// Draw our game scene here
		window.draw(spriteBackground);

		// Draw our game scene here
		// Show everything we just drew

		/* When we draw all the game objects, we are drawing them to a hidden surface ready to be displayed.
		The window.display() code flips from the previously displayed surface to the newly updated (previously hidden)
		one. This way, the player will never see the drawing process as the surface has all the sprites added to it. It
		also guarantees that the scene will be complete before it is flipped. This prevents a graphical glitch known as
		tearing. This process is called double buffering */
		window.display();
	}

	return 0;
}