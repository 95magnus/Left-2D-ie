// Simple example showing how the game loop works.
// Example written by SFML authors.
#include <SFML/Graphics.hpp>

int main()
{
    // Create a window we can draw to
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    // Enable vertical sync - prevents tearing and locks framerate to display
    window.setVerticalSyncEnabled(true);

    // Create a circle that we will draw later
    sf::CircleShape shape(100.f);

    // Fill the circle with green
    shape.setFillColor(sf::Color::Green);

    // Run the game loop as long as the window is open
    while (window.isOpen())
    {
        sf::Event event;

        // Read all events from the window
        while (window.pollEvent(event))
        {
            // Quit when the user presses 'x', ignore all other events
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window to black
        window.clear();

        // Draw our circle
        window.draw(shape);

        // Flip the back buffer and front buffer, showing what was drawn
        window.display();
    }

    return 0;
}
