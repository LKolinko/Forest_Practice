//
// Created by lkolinko on 4/30/24.
//

#include "App.h"

void App::ReWrite() {
    Screen::GetInstance()->window->clear(sf::Color::White);

    int flag = 0;
    fullInd = -1;
    for (int i = 0; i < (int)drawers_.size(); ++i) {
        if (drawers_[i]->GetFull() != 0) {
            flag = abs(drawers_[i]->GetFull());
            fullInd = i;
            break;
        }
    }

    if (flag != 2) {
        for (int i = 0; i < (int)drawers_.size(); ++i) {
            if (i == fullInd) {
                continue;
            }
            drawers_[i]->Draw();
        }
    }

    if (fullInd != -1) {
        for (int i = 0; i < (int)drawers_.size(); ++i) {
            if (i == fullInd) {
                continue;
            }
            drawers_[i]->SetActive(1, 0);
        }
        drawers_[fullInd]->Draw();
    }

    for (auto u : buttons) {
        u->Draw(*Screen::GetInstance()->window);
    }
    for (auto u : textboxs) {
        u->Draw(*Screen::GetInstance()->window);
    }
    table_->Draw(*Screen::GetInstance()->window);
    Screen::GetInstance()->window->display();
}

void App::Run() {
    ReWrite();
    while (Screen::GetInstance()->window->isOpen()) {
        auto time = std::chrono::steady_clock::now();
        sf::Event event;

        if (Screen::GetInstance()->window->pollEvent(event)) {
            EventHandler(event);
        }

        if (std::chrono::duration_cast<std::chrono::milliseconds>(time - prev).count() >= 15) {
            ReWrite();
            prev = time;
        }
    }
}

void App::EventHandler(sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        Screen::GetInstance()->window->close();
    }

    if (event.type == sf::Event::Resized) {
        sf::Vector2u size = sf::Vector2u(event.size.width, event.size.height);
        Screen::GetInstance()->window->setView(sf::View(sf::Vector2f((float) size.x / 2.f, (float) size.y / 2.f),
                              sf::Vector2f(size)));

        drawers_[0]->SetSize({ (unsigned int)(size.x * (float)0.38), (unsigned int)(size.y * (float)0.45) });
        drawers_[0]->SetPos({ size.x * (float)0.6 - 5, size.y * (float)0.02 + 5 });

        drawers_[0]->SetFullSize(sf::Vector2u(size.x * (float)0.79, size.y * (float)0.945 + 5));
        drawers_[0]->SetFullPos({ size.x * (float)0.19 - 5, size.y * (float)0.02 + 5 });

        drawers_[1]->SetSize({ (unsigned int)(size.x * (float)0.38), (unsigned int)(size.y * (float)0.45) });
        drawers_[1]->SetPos({ size.x * (float)0.6 - 5, size.y * (float)0.52 + 5 });

        drawers_[1]->SetFullSize(sf::Vector2u(size.x * (float)0.79, size.y * (float)0.945 + 5));
        drawers_[1]->SetFullPos({ size.x * (float)0.19 - 5, size.y * (float)0.02 + 5 });

        drawers_[2]->SetSize({ (unsigned int)(size.x * (float)0.38), (unsigned int)(size.y * (float)0.45) });
        drawers_[2]->SetPos({ size.x * (float)0.19 - 5, size.y * (float)0.52 + 5 });

        drawers_[2]->SetFullSize(sf::Vector2u(size.x * (float)0.79, size.y * (float)0.945 + 5));
        drawers_[2]->SetFullPos({ size.x * (float)0.19 - 5, size.y * (float)0.02 + 5 });

        drawers_[3]->SetSize({ (unsigned int)(size.x * (float)0.38), (unsigned int)(size.y * (float)0.45) });
        drawers_[3]->SetPos({ size.x * (float)0.19 - 5, size.y * (float)0.02 + 5 });

        drawers_[3]->SetFullSize(sf::Vector2u(size.x * (float)0.79, size.y * (float)0.945 + 5));
        drawers_[3]->SetFullPos({ size.x * (float)0.19 - 5, size.y * (float)0.02 + 5 });

        for (int i = 0; i < buttons.size(); ++i) {
            buttons[i]->SetSize(sf::Vector2f(size.x * buttons_settings[i].first[0], size.y * buttons_settings[0].first[1]));
            buttons[i]->SetPosition(sf::Vector2f(5, size.y * buttons_settings[i].first[3] + 5));
        }

        for (int i = 0; i < textboxs.size(); ++i) {
            textboxs[i]->SetSize(sf::Vector2f(size.x * textboxs_settings[i].first[0], size.y * textboxs_settings[i].first[1]));
            textboxs[i]->SetPosition(sf::Vector2f(5, size.y * textboxs_settings[i].first[3] + 5));
        }

        table_->SetSize(sf::Vector2f(size.x * 0.17, size.y * 0.67));
        table_->SetPosition(sf::Vector2f(5, size.y * 0.31 + 5));
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        for (int i = 0; i < (int)drawers_.size(); ++i) {
            if (i != fullInd && fullInd != -1) {
                drawers_[i]->SetActive(drawers_[i]->isMouseIn(), 0);
                continue;
            }
            drawers_[i]->SetActive(drawers_[i]->isMouseIn(), 1);
        }

        for (int i = 0; i < buttons.size(); ++i) {
            auto u = buttons[i];
            if (u->isMouseOver(*Screen::GetInstance()->window)) {
                if (u->getColor() != 2) {
                    // do something
                    if (i == 0) {
                        AddVertex(textboxs[0]->get_text());
                    } else if (i == 1) {
                        AddMTVertex();
                    }
                }
                u->SetPassedColor();
            }
        }

        for (auto u : textboxs) {
            if (u->isMousOver(*Screen::GetInstance()->window)) {
                u->SetPressed();
            } else {
                u->SetSimple();
            }
        }
    }

    if (event.type == sf::Event::MouseWheelScrolled) {
        if (table_->isMouseOver(*Screen::GetInstance()->window)) {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                table_->Scroll(std::make_pair((int) event.mouseWheelScroll.delta, 0));
            }
        }
        for (auto u : drawers_) {
            if (u->isMouseIn() && u->getActive()) {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    u->Scroll(std::make_pair((int) event.mouseWheelScroll.delta, 0));
                } else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel) {
                    u->Scroll(std::make_pair(0, (int) event.mouseWheelScroll.delta));
                }
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        for (auto u : buttons) {
            if (u->getColor() == 2) {
                u->SetSimpleColor();
            }
        }
    }

    if (event.type == sf::Event::MouseMoved) {
        for (auto u : buttons) {
            if (u->isMouseOver(*Screen::GetInstance()->window)) {
                u->SetOtherColor();
            } else {
                u->SetSimpleColor();
            }
        }
    }

    if (event.type == sf::Event::TextEntered) {
        for (int i = 0; i < textboxs.size(); ++i) {
            if (textboxs[i]->getColor() == 1) {
                if (event.key.code == 13) {
                    textboxs[i]->SetSimple();
                } else {
                    if (event.key.code == 8 || event.key.code == 127) {
                        textboxs[i]->RemoveSimbol();
                    } else {
                        char c = static_cast<char>(event.key.code);
                        textboxs[i]->AddSimbol(c);
                    }
                }
            }
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        drawers_[0]->SetActive(drawers_[0]->isMouseIn(), 0);
        drawers_[1]->SetActive(drawers_[1]->isMouseIn(), 0);
        drawers_[2]->SetActive(drawers_[2]->isMouseIn(), 0);
        drawers_[3]->SetActive(drawers_[3]->isMouseIn(), 0);
    }
}

App::App() {
    drawers_.resize(4);
    sf::Font font;
    font.loadFromFile("Arial.ttf");

    Screen::GetInstance()->Init();
    prev = std::chrono::steady_clock::now();
    auto size = Screen::GetInstance()->window->getSize();
    drawers_[0] = new TreeDrawer({ (unsigned int)(size.x * (float)0.38), (unsigned int)(size.y * (float)0.45) },
                                { size.x * (float)0.6 - 5, size.y * (float)0.02 + 5 }, "AVL-Tree", { size.x * (float)0.19 - 5, size.y * (float)0.02 + 5 },
                                sf::Vector2u(size.x * (float)0.98 - 5, size.y * (float)0.97 + 5));
    drawers_[1] = new TreeDrawer({ (unsigned int)(size.x * (float)0.38), (unsigned int)(size.y * (float)0.45) },
                               { size.x * (float)0.6 - 5, size.y * (float)0.52 + 5 }, "Treap", { size.x * (float)0.19 - 5, size.y * (float)0.02 + 5 },
                               sf::Vector2u(size.x * (float)0.8, size.y * (float)0.9));
    drawers_[2] = new TreeDrawer({ (unsigned int)(size.x * (float)0.38), (unsigned int)(size.y * (float)0.45) },
                               { size.x * (float)0.19 - 5, size.y * (float)0.52 + 5 }, "Splay-tree", { size.x * (float)0.19 - 5, size.y * (float)0.02 + 5 },
                               sf::Vector2u(size.x * (float)0.8, size.y * (float)0.9));
    drawers_[3] = new TreeDrawer({ (unsigned int)(size.x * (float)0.38), (unsigned int)(size.y * (float)0.45) },
                                { size.x * (float)0.19 - 5, size.y * (float)0.02 + 5 }, "RB-Tree", { size.x * (float)0.19 - 5, size.y * (float)0.02 + 5 },
                               sf::Vector2u(size.x * (float)0.8, size.y * (float)0.9));

    for (auto u : buttons_settings) {
        auto button = new Button(sf::Vector2f(size.x * u.first[0], size.y * u.first[1]), sf::Vector2f(5, size.y * u.first[3] + 5),
                                 sf::Color(141, 159, 135), sf::Color(111, 146, 131), sf::Color(105, 109, 125),
                                 font, u.second, 10);
        buttons.push_back(button);
    }

    for (auto u : textboxs_settings) {
        auto Textbox = new TextBox(sf::Vector2f(size.x * u.first[0], size.y * u.first[1]), sf::Vector2f(5, size.y * u.first[3] + 5),
                                   sf::Color(205, 198, 165), sf::Color(233, 198, 165), font, u.second, 10);
        textboxs.push_back(Textbox);
    }

    table_ = new Table(sf::Vector2f(size.x * 0.17, size.y * 0.67), sf::Vector2f(5, size.y * 0.31 + 5), sf::Color(58, 183, 149),
        sf::Color(152, 193, 217), 5, 10, { 100, 30 }, font);

//    for (ll i = 0; i < 19; ++i) {
//        AVL.Add(i);
//        treap.Insert(i);
//    }
//    drawers_[1]->SetRoot(treap.GetRoot());
//    drawers_[0]->SetRoot(AVL.getRoot());
}

void App::AddVertex(std::string value) {
    if (value.empty()) {
        return;
    }
    if (drawers_[0]->getActive()) {
        AVL.Add(std::stol(value));
        drawers_[0]->SetRoot(AVL.getRoot());
    }
    if (drawers_[1]->getActive()) {
        treap.Insert(std::stol(value));
        drawers_[1]->SetRoot(treap.GetRoot());
    }
    if (drawers_[2]->getActive()) {
        splay.Insert(std::stol(value));
        drawers_[2]->SetRoot(splay.GetRoot());
    }
    if (drawers_[3]->getActive()) {

    }
}

void App::AddMTVertex() {
    std::mt19937 rng(std::chrono::high_resolution_clock().now().time_since_epoch().count());
    int cnt = 0;
    auto u = textboxs[1]->get_text();
    if (!u.empty()) {
        cnt = std::stoi(u);
    }
    std::vector<std::string> added;
    for (int i = 0; i < cnt; ++i) {
        auto value = std::to_string(rng());
        added.push_back(value);
        AddVertex(value);
    }
    table_->SetGata(added);
}
