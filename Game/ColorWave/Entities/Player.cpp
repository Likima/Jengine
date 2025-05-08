#include "Player.hpp"

char *vertexSource = R"glsl(
    #version 330 core
    layout (location = 0) in vec2 position;
    uniform mat4 projection;  // Add projection uniform
    void main() {
        gl_Position = projection * vec4(position, 0.0, 1.0);
    }
)glsl";

char *fragmentSource = R"glsl(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(0.5, 0.8, 1.0, 1.0);  // Light blue color
    }
)glsl";

// called every frame update
void Player::update()
{
    bool changed = false;
    if (kh->KeyPressed('D'))
    {
        moveRight();
        changed = true;
    }
    if (kh->KeyPressed('A'))
    {
        moveLeft();
        changed = true;
    }
    if (kh->KeyPressed('W'))
    {
        moveUp();
        changed = true;
    }
    if (kh->KeyPressed('S'))
    {
        moveDown();
        changed = true;
    }
    if (changed)
    {
        updateVertices();
    }
}

void Player::onStart()
{
    setSpeed(5);
}

void Player::render(Renderer *r)
{
    std::cout << "Rendering..." << std::endl;
    r->setShaderSource(vertexSource, fragmentSource);
    r->draw(vertices.data(), indices.data(), vertices.size());
}