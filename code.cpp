// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

	Font font;
	if (!font.loadFromFile("KOMIKAP_.ttf"))
	{
		cerr << "Something wrong with font." << endl;
	}
	
	Text displayCoords; //new object to show the coordinates to user
	displayCoords.setFont(font);
	displayCoords.setCharacterSize(15);
	displayCoords.setFillColor(Color::White);
	displayCoords.setPosition(1500.f, 600.f); // need to change coords
	string completestring = "";
	string displayvertices;


	while (window.isOpen())
	{
        /*
		****************************************
		Handle the players input
		****************************************
		*/
        Event event;
		while (window.pollEvent(event))
		{

		
			if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
				Font font;
            	if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
						displayvertices = "Vertex " + to_string(vertices.size()) + "\nmouse x: " + to_string(event.mouseButton.x) + "\nmouse y: " + to_string(event.mouseButton.y) +"\n";
						completestring = completestring + displayvertices;
						displayCoords.setString(completestring);
                    }
                    else if(points.size() == 0)
                    {
			points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                        ///fourth click
                        ///push back to points vector
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
        /*
		****************************************
		Update
		****************************************
		*/

        if(points.size() > 0)
        {
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
	    	for (int i=0; i<50; i++)
			{
				int index=rand() % vertices.size();
				Vector2f randVertex = vertices[index];

				Vector2f midpoint = (randVertex + points.back())/2.0f;
				points.push_back(midpoint);

				RectangleShape rect(Vector2f(5,5));
				rect.setPosition(midpoint);
				rect.setFillColor(Color::Red);
				window.draw(rect);
			}
        }

        /*
		****************************************
		Draw
		****************************************
		*/
        window.clear();
        for(unsigned long long int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10,10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }
	for (unsigned long long int i=0; i< points.size();i++){
	    RectangleShape rect(Vector2f(5,5));
	    rect.setPosition(Vector2f(points[i].x, points[i].y));
	    rect.setFillColor(Color::Blue);
	    window.draw(rect);
	}

    	Text text;
    	text.setFont(font);
    	text.setCharacterSize(25);
    	text.setFillColor(Color::White);
    	text.setPosition(10.f, 10.f);
    	text.setString("Click on 3 spots to set up triangle vertices. \nThen click for the 4th point to start generating the fractal. ");
		
	window.draw(text);
	window.draw(displayCoords);
	window.display();
    }
}
//Karnpreet Klair and Musa Rana