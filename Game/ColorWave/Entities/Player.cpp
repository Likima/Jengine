#include "Player.hpp"

char *vertexSource = R"glsl(
    #version 330 core
    layout (location = 0) in vec2 position;
    void main() {
        gl_Position = vec4(position, 0.0, 1.0);
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
    if(kh->KeyPressed('D')) {
        std::cout<<"He"<<std::endl;
        x_right+=0.1f;
        setVertices();
    }
}

void Player::onStart()
{

}

void Player::render(Renderer* r)
{
    // Bind the VAO and draw
    std::cout << "Rendering..." << std::endl;
    r->setShaderSource(vertexSource, fragmentSource);
    r->draw(vertices.data(), 8);
}