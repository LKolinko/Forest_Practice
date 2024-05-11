#include "RoundedRectangle.h"
RoundedRectangle::RoundedRectangle(sf::Color color, sf::Vector2f size, sf::Vector2f pos, float radius) {
    LU.setRadius(radius);
    LD.setRadius(radius);
    RU.setRadius(radius);
    RD.setRadius(radius);

    LU.setPosition(pos);
    LU.setFillColor(color);

    RU.setPosition({ pos.x + size.x - RU.getRadius() * 2, pos.y });
    RU.setFillColor(color);

    LD.setPosition({ pos.x, pos.y + size.y - RU.getRadius() * 2 });
    LD.setFillColor(color);

    RD.setPosition({ pos.x + size.x - RU.getRadius() * 2, pos.y + size.y - RU.getRadius() * 2 });
    RD.setFillColor(color);

    horisont.setPosition({ pos.x, pos.y + RU.getRadius() });
    horisont.setSize({ size.x, size.y - RU.getRadius() * 2 });
    horisont.setFillColor(color);

    vertic.setPosition({ pos.x + RU.getRadius(), pos.y });
    vertic.setSize({ size.x - RU.getRadius() * 2, size.y });
    vertic.setFillColor(color);

    position = pos;
    size_ = size;
}

void RoundedRectangle::Draw(sf::RenderWindow &wnd) {
    wnd.draw(LU);
    wnd.draw(LD);
    wnd.draw(RU);
    wnd.draw(RD);
    wnd.draw(horisont);
    wnd.draw(vertic);
}
void RoundedRectangle::SetColor(sf::Color color) {
    LU.setFillColor(color);
    LD.setFillColor(color);
    RU.setFillColor(color);
    RD.setFillColor(color);
    horisont.setFillColor(color);
    vertic.setFillColor(color);
}
sf::Color RoundedRectangle::getColor() {
    return horisont.getFillColor();
}

void RoundedRectangle::Draw(sf::RenderTexture &wnd) {
    wnd.draw(LU);
    wnd.draw(LD);
    wnd.draw(RU);
    wnd.draw(RD);
    wnd.draw(horisont);
    wnd.draw(vertic);
}

void RoundedRectangle::SetSize(sf::Vector2f size) {
    RU.setPosition({ position.x + size.x - RU.getRadius() * 2, position.y });
    LD.setPosition({ position.x, position.y + size.y - RU.getRadius() * 2 });
    RD.setPosition({ position.x + size.x - RU.getRadius() * 2, position.y + size.y - RU.getRadius() * 2 });
    horisont.setSize({ size.x, size.y - RU.getRadius() * 2 });
    vertic.setSize({ size.x - RU.getRadius() * 2, size.y });
    size_ = size;
}

void RoundedRectangle::SetPosition(sf::Vector2f pos) {
    position = pos;
    LU.setPosition(pos);
    RU.setPosition({ pos.x + size_.x - RU.getRadius() * 2, pos.y });
    LD.setPosition({ pos.x, pos.y + size_.y - RU.getRadius() * 2 });
    RD.setPosition({ pos.x + size_.x - RU.getRadius() * 2, pos.y + size_.y - RU.getRadius() * 2 });
    horisont.setPosition({ pos.x, pos.y + RU.getRadius() });
    vertic.setPosition({ pos.x + RU.getRadius(), pos.y });
}

void RoundedRectangle::SetRadius(float radius) {
    LU.setRadius(radius);
    LD.setRadius(radius);
    RU.setRadius(radius);
    RD.setRadius(radius);
}

