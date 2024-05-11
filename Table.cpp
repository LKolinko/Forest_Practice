#include "Table.h"

#include <iostream>

Table::Table(sf::Vector2f size, sf::Vector2f pos, sf::Color Frame, sf::Color Cin,
             float FrameThickness, float radius, sf::Vector2f CellSZ, sf::Font& f) {
    out = RoundedRectangle(Frame, size, pos, radius);
    in = RoundedRectangle(Cin, sf::Vector2f({ size.x - FrameThickness * 2, size.y - FrameThickness * 2 }),
              sf::Vector2f({ pos.x + FrameThickness, pos.y + FrameThickness }), radius / 2);
    CellSize = CellSZ;
    ft = FrameThickness;
    font = f;
    maxSize = 0;

    position = { pos.x + ft / 2, pos.y + ft / 2 };
}

void Table::Draw(sf::RenderWindow &wnd) {

    sf::RenderTexture table;
    sf::RenderTexture Up;
    table.create(static_cast<unsigned int>(in.horisont.getLocalBounds().width - ft),
        static_cast<unsigned int>(in.vertic.getLocalBounds().height - ft - CellSize.y));
    Up.create(static_cast<unsigned int>(in.horisont.getLocalBounds().width - ft),
        static_cast<unsigned int>(CellSize.y));
    Up.clear(in.getColor());
    table.clear(in.getColor());

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(CellSize.y);
    text.setFillColor(sf::Color::Black);
    text.setString("Added:");
    text.setPosition(sf::Vector2f(in.horisont.getSize().x / 2 - text.getLocalBounds().width / 1.5, CellSize.y / 2 - text.getLocalBounds().height / 1.2));
    Up.draw(text);

    out.Draw(wnd);
    in.Draw(wnd);

    sf::RectangleShape line(sf::Vector2f(2, in.vertic.getSize().y));
    line.setFillColor(sf::Color::Black);

    int cnt = int(Start.y / CellSize.y);
    line.setSize(sf::Vector2f(in.horisont.getSize().x, 2));

    line.setPosition({ 0, CellSize.y - 2 });
    Up.draw(line);

    for (int i = cnt + 1; (float)(i - cnt - 2) * CellSize.y < (float)table.getSize().y; ++i) {

        if (std::find(fill.begin(), fill.end(), i - 1) != fill.end()) {
            sf::RectangleShape blr({(float)table.getSize().x, CellSize.y - 2});
            blr.setPosition({ 0, (float) (i - cnt - 1) * CellSize.y - (Start.y - CellSize.y * cnt) + 2} );
            blr.setFillColor(sf::Color(118, 152, 179));
            table.draw(blr);
        }

        if (i <= data.size()) {
            sf::Text text;
            text.setFont(font);
            text.setCharacterSize(CellSize.y * 0.7);
            text.setFillColor(sf::Color::Black);
            text.setString(data[i - 1]);
            text.setPosition(sf::Vector2f(-Start.x,(float)(i - cnt) * CellSize.y -
                                          text.getLocalBounds().height / 1.5 -
                                          (Start.y - CellSize.y * cnt) - CellSize.y / 2));
            table.draw(text);
        }

        line.setPosition(sf::Vector2f({ 0, (float)(i - cnt) * CellSize.y - (Start.y - CellSize.y * cnt) }));
        table.draw(line);
    }

    table.display();
    sf::Sprite sprite(table.getTexture());
    sprite.setPosition(position.x + ft, position.y + ft + CellSize.y);
    wnd.draw(sprite);

    Up.display();
    sf::Sprite spr(Up.getTexture());
    spr.setPosition(position.x + ft, position.y + ft);
    wnd.draw(spr);
}

bool Table::isMouseOver(sf::RenderWindow &window) {
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;
    int btnPosX = out.position.x;
    int btnPosY = out.position.y;
    int btnxPosWidth = btnPosX + out.horisont.getSize().x;
    int btnyPosHeight = btnPosY + out.vertic.getSize().y;
    return (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY);
}

void Table::Scroll(std::pair<int, int> a) {
    Start.y -= (float)a.first * 5;
    Start.y = std::max(Start.y, (float)0);
}

std::vector<std::string> Table::get_data() {
    return data;
}

std::string Table::getCell(int i) {
    return data[i];
}

void Table::SetSize(sf::Vector2f size) {
    out.SetSize(size);
    in.SetSize(sf::Vector2f({ size.x - ft * 2, size.y - ft * 2 }));
}

void Table::SetPosition(sf::Vector2f pos) {
    position = { pos.x + ft / 2, pos.y + ft / 2 };
    out.SetPosition(pos);
    in.SetPosition(sf::Vector2f({ pos.x + ft, pos.y + ft }));
}

void Table::SetGata(std::vector<std::string> &data_) {
    data = data_;
}
