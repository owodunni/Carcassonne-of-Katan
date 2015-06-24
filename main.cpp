/* 
 * File:   main.cpp
 * Author: Oskar och Milton
 * 
 * Beskrivning
 * Startar upp själva spelet, 
 * dvs initierar alla delar och skapar själva fönstret (GUI), 
 * och har sedan en huvudloop som körs kontinuerligt. 
 * Där hanteras event från användaren och grafiken uppdateras. 
 * se funktionen main() längst ner i filen. 
 * 
 * Själva GUI:t är väldigt enkelt. Grundläggande konstanter och statusflaggor
 * finns definerade i simpleGUI.h
 * Kortfattat så består GUI:t av en spelplan där alla spelkortetn kan placeras 
 * ut. Detta sköts via ett objekt av klassen Gamepad. Till vänster om spelplanen
 * i fönstret finns en panel med info om spelarstatus och nästa bricka, detta 
 * sköts via ett objekt av klassen Info_Panel
 * 
 * TODO 
 *      hjälpruta, about-ruta?
 *      bild till mini-ikonen i windows
 *      fönster för välkomstmeddelande?
 */

#include "global.h"
#include "main.h"
#include "simpleGUI.h"
#include "Card.h"
#include "Gamepad.h"
#include "Gamepiece.h"
#include "Player.h"
#include "Info_Panel.h"
#include <iostream>
#include <string>
#include <math.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>



using namespace std;


/*
 * --------------------------- Initiera ----------------------------------------
 */

/*
 * welcome_ message
 * 
 * Visar ett välkomstmedelande i terminalen och läser in spelarnamnen
 */
void welcome_message(string& name1, string& name2) {
    cout << "VÄLKOMNA TILL Carcassonne OF KATAN\n\n";

    // läsa in namn
    cout << "Namn splelare 1:\n";
    //cin >> name1;
    cout << "Du skrev: " << name1 << endl;
    cout << "Namn splelare 2:\n";
    //cin >> name2;
    cout << "Du skrev: " << name2 << endl;
}

/*
 * end game
 * 
 * funktionen körs då spelet är slut, skapar engentligen en textsträng som kan 
 * ritas ut på spelplanen
 */
void end_game(Gamepad& gamepad) {
    cout << "spelet slut\n";
    gamepad.give_points();
    game_ended = true;

    string message = "Winner: ";

    if (global_player1->get_score() > global_player2->get_score())
        message += global_player1->get_name();
    else if (global_player1->get_score() < global_player2->get_score())
        message += global_player2->get_name();
    else
        message += "BOTH!!";

    font.loadFromFile("BEBAS___.ttf");

    victory_message.setFont(font);
    victory_message.setCharacterSize(30);
    victory_message.setString(message);
    victory_message.setPosition(100, 200);
    victory_message.setColor(sf::Color::Black);
}


/*
 * change_current_player
 * 
 * uppdatera aktuell spelare
 */
void change_current_player(Info_Panel& panel, Gamepad& gamepad) {
    current_player = (current_player + 1) % 2;
    placing_card = true;
    panel.set_current_card(gamepad.make_random_card());
}

/*
 * attempt_card_placement
 * 
 * hjälpfunktion för att placera ut ett kort på spelplanen om möjligt
 */
void attempt_card_placement(sf::Event event, Gamepad& gamepad, Info_Panel& panel, Player& current_player) {//, const Gamepiece& current_piece) {
    int x_coord = event.mouseButton.x;
    int y_coord = event.mouseButton.y;
    if (GAMEPAD_RECT.contains(x_coord, y_coord)) {
        Card* card = panel.get_current_card();
        if (gamepad.place_card(card, x_coord, y_coord)) {
            //kortet har placerats ut
            card->set_color(sf::Color(255, 255, 255, 255));
            ++num_of_cards;
            if (num_of_cards == NUM_OF_CARDS) {
                end_game(gamepad);
            }
            //ska spelpjäs få placeras ut?
            if (current_player.has_gamepieces())
                placing_card = false; //ska få placera ut spelpjäs
            else {
                //får inte placera spelpjäs
                change_current_player(panel, gamepad);
            }
        } else {//kortet gick ej att placera ut
            incorrect_card_placement = true;
            my_clock.restart();
        }
    }
}

/*
 * attempt_gamepiece_placement
 */
void attempt_gamepiece_placement(sf::Event event, Gamepad& gamepad, Info_Panel& panel, Player& current_player) {
    int x_coord = event.mouseButton.x;
    int y_coord = event.mouseButton.y;
    if (GAMEPAD_RECT.contains(x_coord, y_coord)) {
        Gamepiece current_gamepiece = Gamepiece(current_player);
        current_gamepiece.set_center_position(x_coord, y_coord);
        if (gamepad.place_gamepiece(current_gamepiece, x_coord, y_coord)) {
            current_player.decrease_gamepieces();
            change_current_player(panel, gamepad);
        } else
            cout << "Gamepiece place NOT ok\n";
    }
}

/*
 * check_events
 * 
 * Huvudfunktionen för att kolla events, körs alltid
 * Endast ett fåtal events ger effekt, nämligen följande
 *      stänga fönstret - programmet avslutas
 *      vänsterklick med musknappen - förska placera ut ett kort (spelpläs)
 *      Return - försöker byta aktuell spelare (om kort har placerats ut)
 *      vänsterpil - rotera kortet
 *      högerpil - rotera kortet
 *      N - slumpa nytt kort
 * 
 * För att försöka placera ut ett kort på spelplanen anropas funktionen attempt_card_placement
 */
void check_events(sf::RenderWindow& window, Gamepad& gamepad, bool& running, Info_Panel& panel, Player& current_player) { //Card& next_card, 
    sf::Event event;
    while (window.pollEvent(event)) {

        //stänga
        if (event.type == sf::Event::Closed)
            running = false;

        else if (!game_ended) {

            //musklick
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (placing_card)
                    attempt_card_placement(event, gamepad, panel, current_player);
                else
                    attempt_gamepiece_placement(event, gamepad, panel, current_player);

                //tangenttryckning
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Return) {
                    if (!placing_card) {
                        change_current_player(panel, gamepad);
                    }
                }
                if (event.key.code == sf::Keyboard::Left) {
                    panel.rotate_card_left();
                } else if (event.key.code == sf::Keyboard::Right) {
                    panel.rotate_card_right();
                } else if (event.key.code == sf::Keyboard::H)
                    cout << "Display help!\n";
                else if (event.key.code == sf::Keyboard::N) {
                    panel.set_current_card(gamepad.make_random_card());
                }
            }
        }
    }
}



/*
 * -------------------------- Grafik -------------------------------------------
 */

/*
 * draw_cursor_image
 * 
 * Ritar ut den nya spelbrickan eller spelpjäsen vid muspekaren
 */
void draw_cursor_image(sf::RenderWindow& window, Card* card, Gamepiece gamepiece) { 
    //hämta musen koord, inuti spelytan?, färg?, rita ut
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    if (GAMEPAD_RECT.contains(mouse_pos)) {

        if (placing_card) {
            //Card cursor_card = card;
            card->set_center_position(mouse_pos.x, mouse_pos.y);
            sf::Color color = sf::Color(255, 255, 255, 128);
            if (incorrect_card_placement) {
                if (my_clock.getElapsedTime().asMilliseconds() < 300) {
                    color = sf::Color(255, 0, 0, 128); // röd bild
                } else
                    incorrect_card_placement = false;
            }
            card->set_color(color);
            card->draw(window);
        } else {
            //rita ut
            gamepiece.set_center_position(mouse_pos.x, mouse_pos.y);
            gamepiece.draw(window);
        }
    }
}

/*
 * ------------------------- MAIN ----------------------------------------------
 */

/*
 * MAIN
 */
int main(int argc, char* argv[]) {

    // initiera: skapa spelare, spelplan och infopanel
    string player1_name = "Spelare 1";
    string player2_name = "Spelare 2";
    welcome_message(player1_name, player2_name);

    Player players[2] = {Player(sf::Color::Magenta, player1_name, 1), Player(sf::Color::Cyan, player2_name, 2)};
    global_player1 = &players[0];
    global_player2 = &players[1];
    Gamepad gamepad;
    Info_Panel panel(players[0], players[1]);
    panel.set_current_card(gamepad.make_random_card());

    //spelstatus
    bool running = true;
    placing_card = true;
    current_player = 0;
    game_ended = false;

    //skapa fönster
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Carcassonne OF KATAN");
    window.setKeyRepeatEnabled(false);

    // Huvudloop
    while (running) {

        //kolla event
        check_events(window, gamepad, running, panel, players[current_player]);

        //grafiken: clear, draw, display
        window.clear(sf::Color::White);
        gamepad.draw(window);
        panel.draw(window, current_player, placing_card);
        if (!game_ended) draw_cursor_image(window, panel.get_current_card(), Gamepiece(players[current_player]));
        if (game_ended) {
            window.draw(victory_message);
        }
        window.display();
    }

    window.close();
    return 0;
}

