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

	// Make a tree sprite
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");

	Sprite spriteTree(textureTree);
	//spriteTree.setTexture(textureTree);
	spriteTree.setPosition(Vector2f(810, 0));

	// Prepare the bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");

	Sprite spriteBee(textureBee);
	//spriteBee.setTexture(textureBee);
	spriteBee.setPosition(Vector2f(0, 800));

	// Is the bee currently moving?
	bool beeActive = false;

	// How fast can the bee fly
	float beeSpeed = 0.0f;

	// make 3 cloud sprites from 1 texture
	Texture textureCloud;

	// Load 1 new texture
	textureCloud.loadFromFile("graphics/cloud.png");

	// 3 New sprites with the same texture
	Sprite spriteCloud1(textureCloud);
	Sprite spriteCloud2(textureCloud);
	Sprite spriteCloud3(textureCloud);
	//spriteCloud1.setTexture(textureCloud);
	//spriteCloud2.setTexture(textureCloud);
	//spriteCloud3.setTexture(textureCloud);
	
	// Position the clouds on the left of the screen at different heights
	spriteCloud1.setPosition(Vector2f(0, 0));
	spriteCloud2.setPosition(Vector2f(0, 250));
	spriteCloud3.setPosition(Vector2f(0, 500));

	// Are the clouds currently on screen?
	bool cloud1Active = false;
	bool cloud2Active = false;
	bool cloud3Active = false;

	// How fast is each cloud?
	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	// Variables to control time itself
	Clock clock;

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

		/* The clock.restart() function, as you might expect, restarts the clock. We want to restart the clock every frame
		so that we can time how long each and every frame takes. In addition, however, it returns the amount of time that
		has elapsed since the last time we restarted the clock */

		// Measure time
		Time dt = clock.restart();

		// Setup the bee
		if (!beeActive)
		{
			// How fast is the bee
			srand((int)time(0)); // Seed the random number generator

			// Get a random number between 200 and 399 and assign the result to beeSpeed
			beeSpeed = (rand() % 200) + 200;

			// How high is the bee
			srand((int)time(0) * 10); // Seed the random number generator again

			// Get a random number between 500 and 999 and assign the result to a new float variable called height
			float height = (rand() % 500) + 500;

			/* Set the position of the bee to 2000 on the x axis (just off - screen to the right) and to whatever height
			equals on the y axis */
			spriteBee.setPosition(Vector2f(2000, height));

			beeActive = true; // Set bee active to true afterwards
		}

		else // Move the bee
		{
			spriteBee.setPosition(Vector2f(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), 
				spriteBee.getPosition().y));

			// Has the bee reached the left-hand edge of the screen?
			if (spriteBee.getPosition().x < -100)
			{
				// Set it up ready to be a whole new bee next frame
				beeActive = false;
			}
		}

		// Manage the clouds
		// Cloud 1
		if (!cloud1Active)
		{
			// How fast is the cloud
			srand((int)time(0) * 10);
			cloud1Speed = (rand() % 200);

			// How high is the cloud
			srand((int)time(0) * 10);
			float height = (rand() % 150);
			spriteCloud1.setPosition(Vector2f(-200, height));

			cloud1Active = true;
		}

		else
		{
			spriteCloud1.setPosition(Vector2f(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()),
				spriteCloud1.getPosition().y));

			// Has the cloud reached the right hand edge of the screen?
			if (spriteCloud1.getPosition().x > 1920)
			{
				// Set it up ready to be a whole new cloud next frame
				cloud1Active = false;
			}
		}

		// Cloud 2
		if (!cloud2Active)
		{
			// How fast is the cloud
			srand((int)time(0) * 20);
			cloud2Speed = (rand() % 200);

			// How high is the cloud
			srand((int)time(0) * 20);
			float height = (rand() % 300) - 150;
			spriteCloud2.setPosition(Vector2f(-200, height));

			cloud2Active = true;
		}

		else
		{
			spriteCloud2.setPosition(Vector2f(spriteCloud2.getPosition().x +(cloud2Speed * dt.asSeconds()),
				spriteCloud2.getPosition().y));

			// Has the cloud reached the right hand edge of the screen?
			if (spriteCloud2.getPosition().x > 1920)
			{
				// Set it up ready to be a whole new cloud next frame
				cloud2Active = false;
			}
		}

		if (!cloud3Active)
		{
			// How fast is the cloud
			srand((int)time(0) * 30);
			cloud3Speed = (rand() % 200);

			// How high is the cloud
			srand((int)time(0) * 30);
			float height = (rand() % 450) - 150;
			spriteCloud3.setPosition(Vector2f(-200, height));

			cloud3Active = true;
		}

		else
		{
			spriteCloud3.setPosition(Vector2f(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()),
				spriteCloud3.getPosition().y));

			// Has the cloud reached the right hand edge of the screen?
			if (spriteCloud3.getPosition().x > 1920)
			{
				// Set it up ready to be a whole new cloud next frame
				cloud3Active = false;
			}
		}

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

		// Draw the clouds
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		// Draw the tree
		window.draw(spriteTree);

		// Draw the insect
		window.draw(spriteBee);

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