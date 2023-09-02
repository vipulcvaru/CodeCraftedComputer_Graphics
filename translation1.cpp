#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

class Transform {
private:
    int n;
    std::vector<sf::Vector2f> originalVertices;
    std::vector<sf::Vector2f> transformedVertices;
    sf::RenderWindow window;

public:
    Transform() : n(0), window(sf::VideoMode(600, 600), "2D Transformations") {}

    void getInput() {
        std::cout << "Enter the number of vertices: ";
        std::cin >> n;

        originalVertices.resize(n);
        transformedVertices.resize(n);

        for (int i = 0; i < n; ++i) {
            std::cout << "Enter vertex " << i + 1 << " (x y): ";
            std::cin >> originalVertices[i].x >> originalVertices[i].y;
        }
    }

    void draw() {
        window.clear();

        // Draw the original shape
        for (int i = 0; i < n; ++i) {
            int next = (i + 1) % n;
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(300 + originalVertices[i].x, 300 - originalVertices[i].y)),
                sf::Vertex(sf::Vector2f(300 + originalVertices[next].x, 300 - originalVertices[next].y))
            };
            window.draw(line, 2, sf::Lines);
        }

        // Draw the transformed shape
        for (int i = 0; i < n; ++i) {
            int next = (i + 1) % n;
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(300 + transformedVertices[i].x, 300 - transformedVertices[i].y)),
                sf::Vertex(sf::Vector2f(300 + transformedVertices[next].x, 300 - transformedVertices[next].y))
            };
            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }

    void translate() {
        float tx, ty;
        std::cout << "Enter translation values (tx ty): ";
        std::cin >> tx >> ty;

        for (int i = 0; i < n; ++i) {
            transformedVertices[i].x = originalVertices[i].x + tx;
            transformedVertices[i].y = originalVertices[i].y + ty;
        }
    }

    void scale() {
        float sx, sy;
        std::cout << "Enter scaling factors (sx sy): ";
        std::cin >> sx >> sy;

        for (int i = 0; i < n; ++i) {
            transformedVertices[i].x = originalVertices[i].x * sx;
            transformedVertices[i].y = originalVertices[i].y * sy;
        }
    }

    void rotate() {
        float deg;
        std::cout << "Enter rotation angle (degrees): ";
        std::cin >> deg;
        float theta = deg * (M_PI / 180);

        float cosTheta = std::cos(theta);
        float sinTheta = std::sin(theta);

        for (int i = 0; i < n; ++i) {
            transformedVertices[i].x = originalVertices[i].x * cosTheta - originalVertices[i].y * sinTheta;
            transformedVertices[i].y = originalVertices[i].x * sinTheta + originalVertices[i].y * cosTheta;
        }
    }

    void run() {
        getInput();
        window.setFramerateLimit(60);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            int choice;
            std::cout << "\nChoose Transformation:\n";
            std::cout << "1. Translate\n2. Rotate\n3. Scale\n4. Quit\n";
            std::cin >> choice;

            switch (choice) {
                case 1:
                    translate();
                    break;
                case 2:
                    rotate();
                    break;
                case 3:
                    scale();
                    break;
                case 4:
                    window.close();
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
            }

            draw();
        }
    }
};

int main() {
    Transform transformer;
    transformer.run();
    return 0;
}
