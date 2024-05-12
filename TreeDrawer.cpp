//
// Created by lkolinko on 4/28/24.
//

#include "TreeDrawer.h"

TreeDrawer::Node::Node(int64_t v) {
    val = v;
    size = 1;
}

void TreeDrawer::Draw() {

    if (fullScreen == 1) {
        if (fabs(pos.x - full_pos.x) < fullStep) {
            SetPos_({ full_pos.x, pos.y });
        } else {
            SetPos_({ pos.x + (float)fullStep * (float)(full_pos.x - pos.x > 0 ? 1 : -1), pos.y });
        }
        if (fabs(pos.y - full_pos.y) < fullStep) {
            SetPos_({ pos.x, full_pos.y });
        } else {
            SetPos_({ pos.x, pos.y + (float)fullStep * (float)(full_pos.y - pos.y > 0 ? 1 : -1) });
        }
        if (fabs(size.x - full_size.x) < fullStep) {
            SetSize_({ full_size.x, size.y });
        } else {
            SetSize_(sf::Vector2u(size.x + fullStep, size.y ));
        }
        if (fabs(size.y - full_size.y) < fullStep) {
            SetSize_(sf::Vector2u(size.x, full_size.y));
        } else {
            SetSize_(sf::Vector2u(size.x, size.y + fullStep));
        }
        if (pos == full_pos && size == full_size) {
            fullScreen = 2;
        }
    }

    if (fullScreen == -1) {
        if (fabs(pos.x - pos_rt.x) < fullStep) {
            SetPos_({ pos_rt.x, pos.y });
        } else {
            SetPos_({ pos.x + (float)fullStep * (float)(pos_rt.x - pos.x > 0 ? 1 : -1), pos.y });
        }
        if (fabs(pos.y - pos_rt.y) < fullStep) {
            SetPos_({ pos.x, pos_rt.y });
        } else {
            SetPos_({ pos.x, pos.y + (float)fullStep * (float)(pos_rt.y - pos.y > 0 ? 1 : -1) });
        }

        if (fabs(size.x - size_rt.x) < fullStep) {
            SetSize_({ size_rt.x, size.y });
        } else {
            SetSize_(sf::Vector2u(size.x - fullStep, size.y ));
        }
        if (fabs(size.y - size_rt.y) < fullStep) {
            SetSize_(sf::Vector2u(size.x, size_rt.y));
        } else {
            SetSize_(sf::Vector2u(size.x, size.y - fullStep));
        }

        if (pos == pos_rt && size == size_rt) {
            fullScreen = 0;
        }
    }

    if (zoom_up->isMouseOver(*Screen::GetInstance()->window, pos)) {
        zoom_up->SetOtherColor();
    } else {
        zoom_up->SetSimpleColor();
    }
    if (zoom_down->isMouseOver(*Screen::GetInstance()->window, pos)) {
        zoom_down->SetOtherColor();
    } else {
        zoom_down->SetSimpleColor();
    }
    if (focus->isMouseOver(*Screen::GetInstance()->window, pos)) {
        focus->SetOtherColor();
    } else {
        focus->SetSimpleColor();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (zoom_up->isMouseOver(*Screen::GetInstance()->window, pos)) {
            if (zoom_up->getColor() != 2) {
                setZoom(-0.05);
            }
            zoom_up->SetPassedColor();
        }
        if (zoom_down->isMouseOver(*Screen::GetInstance()->window, pos)) {
            if (zoom_down->getColor() != 2) {
                setZoom(0.05);
            }
            zoom_down->SetPassedColor();
        }
        if (focus->isMouseOver(*Screen::GetInstance()->window, pos) && Active) {
            if (focus->getColor() != 2) {
                if (fullScreen == 0) {
                    fullScreen = 1;
                }
                if (fullScreen == 2) {
                    fullScreen = -1;
                }
            }
            focus->SetPassedColor();
        }
    }

    sf::Text title;
    title.setString(title_);
    title.setCharacterSize(size.x / 15);
    title.setFillColor(sf::Color::Black);
    title.setFont(font);

    texture.create(size.x, size.y);
    texture.clear(ColActive);

    texture.draw(title);

    back.Draw(*Screen::GetInstance()->window);

    if (root) {
        auto points = AllNodes(root);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            for (auto u : points) {
                int mouseX = sf::Mouse::getPosition(*Screen::GetInstance()->window).x - pos.x;
                int mouseY = sf::Mouse::getPosition(*Screen::GetInstance()->window).y - pos.y;
                sf::Vector2f o = { u->pos.x / zoom + shift.x + RADIUS / zoom, u->pos.y / zoom + shift.y + RADIUS / zoom };
                if ((mouseX - o.x) * (mouseX - o.x) + (mouseY - o.y) * (mouseY - o.y) <= RADIUS / zoom * RADIUS / zoom) {
                    DeleteVertex = u;
                    break;
                }
            }
        }
        Phisic(points);
        for (auto point: points) {
            std::vector<Node *> Child = {point->GetLeft(), point->GetRight()};

            for (auto u: Child) {
                if (u == nullptr) {
                    continue;
                }
                sf::VertexArray lines(sf::Lines, 2);
                lines[0].position = sf::Vector2f(point->pos.x / zoom + RADIUS / zoom + shift.x,
                                                 point->pos.y / zoom + RADIUS / zoom + shift.y);
                lines[1].position = sf::Vector2f(u->pos.x / zoom + RADIUS / zoom + shift.x, u->pos.y / zoom + RADIUS / zoom + shift.y);
                lines[0].color = sf::Color::Black;
                lines[1].color = sf::Color::Black;
                texture.draw(lines);
            }
        }

        for (auto point: points) {
            sf::CircleShape vertex;
            vertex.setPosition({ point->pos.x / (float)zoom + shift.x, point->pos.y / (float)zoom + shift.y });
            vertex.setRadius(RADIUS / zoom);
            vertex.setFillColor(point->color);
            texture.draw(vertex);

            sf::Text text;
            text.setFillColor(sf::Color::White);
            text.setFont(font);
            text.setCharacterSize((int) (RADIUS / zoom / pow(point->GetData().size(), 0.5)));
            text.setString(point->GetData());
            text.setPosition({point->pos.x / zoom + RADIUS / zoom - text.getLocalBounds().width / 2 + shift.x,
                              point->pos.y / zoom + RADIUS / zoom - text.getLocalBounds().height + shift.y});
            texture.draw(text);
        }
    }
    zoom_down->Draw(texture);
    zoom_up->Draw(texture);
    focus->Draw(texture);
    texture.display();
    sf::Sprite sprite(texture.getTexture());
    sprite.setPosition(pos);
    Screen::GetInstance()->window->draw(sprite);
}

std::vector<TreeDrawer::Node*> TreeDrawer::AllNodes(TreeDrawer::Node *v) {
    GetSize(root);
    std::vector<TreeDrawer::Node*> ans;
    std::queue<TreeDrawer::Node*> q;
    q.push(v);
    while (!q.empty()) {
        auto top = q.front();
        q.pop();
        ans.push_back(top);
        if (top->GetLeft() != nullptr) {
            top->GetLeft()->isLeft = true;
            q.push(top->GetLeft());
        }
        if (top->GetRight() != nullptr) {
            top->GetRight()->isLeft = false;
            q.push(top->GetRight());
        }
    }
    return ans;
}

void TreeDrawer::SetRoot(TreeDrawer::Node *vertex) {
    if (root) {
        root->pos = GetPoint();
    }
    if (vertex != nullptr) {
        vertex->pos = sf::Vector2f((size.x / 2 - RADIUS / zoom) * zoom, 40);
    }
    root = vertex;
}

sf::Vector2f TreeDrawer::GetPoint() {
    auto size = Screen::GetInstance()->window->getSize();
    static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    return sf::Vector2f(gen() % size.x, gen() % size.y);
}

void TreeDrawer::Phisic(std::vector<Node*>& points) {
    auto time = std::chrono::steady_clock::now();
    auto time_gone = std::chrono::duration_cast<std::chrono::milliseconds>(time - prev).count();
    time_gone /= 14;

    if (time_gone == 0) {
        return;
    }

    std::vector<Node*> Child = { root->GetLeft(), root->GetRight() };
    for (auto u : Child) {
        if (u == nullptr) {
            continue;
        }

        u->speed.x += K * (root->pos.x - u->pos.x) * time_gone;
        u->speed.y += K * (root->pos.y - u->pos.y) * time_gone;
    }

    for (auto point : points) {
        if (point == root) {
            continue;
        }
        sf::Vector2f Resultant_Force = { 0, GRAVITY };

        if (point->isLeft) {
            Resultant_Force += sf::Vector2f(-Lateral * (float)point->size, (float)point->size);
        } else {
            Resultant_Force += sf::Vector2f(Lateral * (float)point->size, (float)point->size);
        }

        std::vector<Node*> Child = { point->GetLeft(), point->GetRight() };
        for (auto u : Child) {
            if (u == nullptr) {
                continue;
            }
            u->speed.x += K * (point->pos.x - u->pos.x);
            u->speed.y += K * (point->pos.y - u->pos.y);
        }

        for (auto second : points) {
            if (point == second) {
                continue;
            }

            float dist = (point->pos.x - second->pos.x) * (point->pos.x - second->pos.x) +
                              (point->pos.y - second->pos.y) * (point->pos.y - second->pos.y);


            Resultant_Force -= sf::Vector2f((second->pos.x - point->pos.x) / dist * elasticity,
                                            (second->pos.y - point->pos.y) / dist * elasticity);
        }

        point->speed += { Resultant_Force.x, Resultant_Force.y };
        point->speed = point->speed * (float)pow(0.5, time_gone);
        point->pos += { point->speed.x * time_gone, point->speed.y * time_gone };
    }

    prev = time;
}

int64_t TreeDrawer::GetSize(TreeDrawer::Node *root) {
    if (root == nullptr) {
        return 0;
    }
    root->size = 1 + GetSize(root->GetLeft()) + GetSize(root->GetRight());
    return root->size;
}

void TreeDrawer::setZoom(float delta) {
    zoom += delta;
    if (root) {
        root->pos = {(size.x / 2 - RADIUS / zoom) * zoom, 40};
    }
}

TreeDrawer::TreeDrawer(sf::Vector2u size_, sf::Vector2f pos_, std::string title, sf::Vector2f full_p, sf::Vector2u full_s) {
    back = RoundedRectangle(sf::Color(67, 62, 63), { (float)size_.x + 20, (float)size_.y + 20 }, { pos_.x - 10, pos_.y - 10 }, 10);
    font.loadFromFile("Arial.ttf");
    title_ = title;
    size = size_;
    pos = pos_;
    size_rt = size;
    pos_rt = pos;

    zoom_down = new Button(sf::Vector2f(50, 50 ), sf::Vector2f(size.x - 50, size.y - 50),
                           sf::Color(141, 159, 135), sf::Color(111, 146, 131), sf::Color(105, 109, 125),
                           font, "-", size.x / 20);
    zoom_up = new Button(sf::Vector2f(50, 50 ), sf::Vector2f(size.x - 50, size.y - 101),
                                     sf::Color(141, 159, 135), sf::Color(111, 146, 131), sf::Color(105, 109, 125),
                                     font, "+", size.x / 20);
    focus = new Button(sf::Vector2f(70, 30), sf::Vector2f(size.x - 70, 0),
                                     sf::Color(141, 159, 135), sf::Color(111, 146, 131), sf::Color(105, 109, 125),
                                     font, "FS", 10);

    full_pos = full_p;
    full_size = full_s;
}

bool TreeDrawer::isMouseIn() {
    int mouseX = sf::Mouse::getPosition(*Screen::GetInstance()->window).x;
    int mouseY = sf::Mouse::getPosition(*Screen::GetInstance()->window).y;
    int btnPosX = pos.x;
    int btnPosY = pos.y;
    int btnxPosWidth = pos.x + size.x;
    int btnyPosHeight = pos.y + size.y;
    return mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY;
}

void TreeDrawer::SetSize(sf::Vector2u size_) {
    size = size_;
    size_rt = size_;
    back.SetSize({ (float)size_.x + 20, (float)size_.y + 20 });

    zoom_up->SetPosition(sf::Vector2f(size.x - 50, size.y - 101));
    zoom_down->SetPosition(sf::Vector2f(size.x - 50, size.y - 50));
    focus->SetPosition(sf::Vector2f(size.x - 70, 0));
}

void TreeDrawer::SetPos(sf::Vector2f pos_) {
    pos = pos_;
    pos_rt = pos_;
    back.SetPosition({ pos_.x - 10, pos_.y - 10 });
}

void TreeDrawer::SetActive(bool flag, int f) {
    if (f == 1) {
        if (flag) {
            Active = true;
        }
    } else {
        if (flag) {
            Active = false;
        }
    }
    if (Active) {
        ColActive = sf::Color({ 189, 180, 191 });
    } else {
        ColActive = sf::Color::White;
        shift = { 0, 0 };
    }
}

bool TreeDrawer::getActive() {
    return Active;
}

void TreeDrawer::SetSize_(sf::Vector2u size_) {
    size = size_;
    back.SetSize({ (float)size_.x + 20, (float)size_.y + 20 });

    zoom_up->SetPosition(sf::Vector2f(size.x - 50, size.y - 101));
    zoom_down->SetPosition(sf::Vector2f(size.x - 50, size.y - 50));
    focus->SetPosition(sf::Vector2f(size.x - 70, 0));

    if (root != nullptr) root->pos = sf::Vector2f((size.x / 2 - RADIUS / zoom) * zoom, 40);
}

void TreeDrawer::SetPos_(sf::Vector2f pos_) {
    pos = pos_;
    back.SetPosition({ pos_.x - 10, pos_.y - 10 });
}

void TreeDrawer::SetFullSize(sf::Vector2u size_) {
    full_size = size_;
}

void TreeDrawer::SetFullPos(sf::Vector2f pos_) {
    full_pos = pos_;
}

int TreeDrawer::GetFull() {
    return fullScreen;
}

void TreeDrawer::Scroll(std::pair<int, int> a) {
    shift.y += (float)a.first * 5;
    shift.x += (float)a.second * 5;
}

TreeDrawer::Node *TreeDrawer::Delete() {
    auto q = DeleteVertex;
    DeleteVertex = nullptr;
    return q;
}
