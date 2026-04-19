
class Game{
  public:
  
  int figures[7][4][4][2] = {
    
    // квадрат 
    {
    {{4, 2}, {5, 2}, {4, 3}, {5, 3}},
    {{4, 2}, {5, 2}, {4, 3}, {5, 3}},
    {{4, 2}, {5, 2}, {4, 3}, {5, 3}},
    {{4, 2}, {5, 2}, {4, 3}, {5, 3}},
    },
    
    
    // т 
    //вверх
    {
    {{4, 2}, {3, 3}, {4, 3}, {5, 3}},
    // влево
    {{4, 1}, {3, 2}, {4, 2}, {4, 3}},
    // вниз       
    {{3, 2}, {4, 2}, {5, 2}, {4, 3}},
    // вправо
    {{4, 1}, {4, 2}, {5, 2}, {4, 3}},
    },
    
    
    // г 
    //вверх
    {
    {{3, 2}, {3, 3}, {4, 3}, {5, 3}},
    // влево
    {{4, 1}, {4, 2}, {3, 3}, {4, 3}},
    // вниз
    {{3, 2}, {4, 2}, {5, 2}, {5, 3}},
    // вправо
    {{4, 1}, {5, 1}, {4, 2}, {4, 3}},
    },

    
    // L 
    //вверх
    {
    {{5, 2}, {3, 3}, {4, 3}, {5, 3}},
    // влево
    {{3, 1}, {4, 1}, {4, 2}, {4, 3}},
    // вниз
    {{3, 2}, {4, 2}, {5, 2}, {3, 3}},
    // вправо
    {{4, 1}, {4, 2}, {4, 3}, {5, 3}},
    },


    // зигзаг 
    {
    //горизонтально
    {{3, 2}, {4, 2}, {4, 3}, {5, 3}},
    // вертикально
    {{4, 1}, {3, 2}, {4, 2}, {3, 3}},
    //горизонтально
    {{3, 2}, {4, 2}, {4, 3}, {5, 3}},
    // вертикально
    {{4, 1}, {3, 2}, {4, 2}, {3, 3}},
    },
    
    
    // зиг ререрс 
    {
    //горизонтально
    {{4, 2}, {5, 2}, {3, 3}, {4, 3}},
    // зиг реверс вертикально
    {{3, 1}, {3, 2}, {4, 2}, {4, 3}},
    //горизонтально
    {{4, 2}, {5, 2}, {3, 3}, {4, 3}},
    // зиг реверс вертикально
    {{3, 1}, {3, 2}, {4, 2}, {4, 3}},
    },
    
    // I
    {
    // вертикально
    {{4, 0}, {4, 1}, {4, 2}, {4, 3}},
    // горизонтально
    {{3, 3}, {4, 3}, {5, 3}, {6, 3}},
    // вертикально
    {{4, 0}, {4, 1}, {4, 2}, {4, 3}},
    // горизонтально
    {{3, 3}, {4, 3}, {5, 3}, {6, 3}},
    },
  };
  
  char big_game_field[18][10] = {};
  
  // заполняет игровое поле пустыми ячейками. используеься при инициализации класса и при очистке поля после игры.
  void void_big_game_field(){
    for (int i = 0; i < 18; i++){
      for (int o = 0; o < 10; o++){
        big_game_field[i][o] = 'v';
      };
    };
  };
  
  char figure_simbol[7] = {
      's', // квадрат
      't', // т фигура
      'g', // г фигура
      'l', // L фигура
      'z', // зигзаг
      'w', // зигзаг реверс
      'i', // палка
  };
  
  
  int start_figure_x = 0;
  int start_figure_y = 0;
  int current_figure_x = 0;
  int current_figure_y = 0;
  // переменная индекса стартовых индексов фигуры
  int current_figure_index = 0;
  // переменная, отвечающая за угол наклона пвдвющей фигуры. обновляется перед каждой инициализацией новой фигуры в hidden field
  int current_figure_angle = 0;
  
    // массив, в котором хранятся текущие индексы в игровом поле падающей фигуры
  int falling_figure[4][2] = {};    
  
  
  // функция обновления фигуры(сброс переменных, инициализация новой)
  void start_figure(){
    current_figure_x = start_figure_x;
    current_figure_y = start_figure_y;
    current_figure_angle = 0;
  };
  
  bool have_active_figure = false;
  int figure_round = 0;
  int speed_interval = 0;
  int random_current_figure_num = 0;
  int random_next_figure_num = 0;


  // сброс поля, отрисовка нового поля. Возвращает true, если прлисходит смена раунда. возвращаемое знвчение используется в классе RGB для отрисовки анимации смены раунда
  void start_round(){
      //bool result = false;
     // if (end_or_not() == END){
    void_big_game_field();
    start_figure();
       // result = true;
     // };
     // return result;
    figure_round = 0;
    speed_interval = 0;
  };
  
  
  // функция принимает индекс координат фигуры из массива-списка фигур figures. и записывает стартовые координаты фигуры в falling_figure
  void init_figure_into_falling_figure(int figure_type){
    for (int i = 0; i < 4; i++){
      falling_figure[i][0] = figures[figure_type][0][i][0];
      falling_figure[i][1] = figures[figure_type][0][i][1];
    };
  };
  
  // добавляет символы фигуры на поле. принимает индекс фигуры. берет символ по индексу из массива figure_simbol 
  void fix_figure_position(){
    for (int i = 0; i < 4; i++){
      big_game_field[falling_figure[i][1]][falling_figure[i][0]] = figure_simbol[current_figure_index];
    };
    figure_round += 1;
    if (figure_round % 5 == 0){
      if (speed_interval < 740){
        speed_interval += 20;
      };
    };
  };
  
  
  // двигает фигуру вниз до тех пор пока это возможно, а затем фиксирует ее, возвращает true если фигура зафиксировалась и false если пока нет 
  bool figure_one_step_down(){
    bool is_fixed = false;
    bool can_go_down = true;
    for (int i = 0; i < 4; i++){
      if (falling_figure[i][1] >= 17 || big_game_field[falling_figure[i][1] + 1][falling_figure[i][0]] != 'v'){
          can_go_down = false;
      };
    };
    if (can_go_down == true){
      for (int i = 0; i < 4; i++){
        falling_figure[i][1] += 1;
      };
        current_figure_y += 1;
    };
    if (can_go_down == false){
      fix_figure_position();
      is_fixed = true; 
    };
    return is_fixed;
  };
  
  
  bool end_or_not(){
    bool end = false;
    for (int i = 0; i < 4; i++){
      if (falling_figure[i][1] < 4){
        end = true;
      };
    };
    return end;
  };
  
  void combination_collapse(){
    int combinations[4] = {};
    int combinations_index = 0;
    for (int i = 0; i < 18; i++){
      int simbol_quantity = 0;
      for (int o = 0; o < 10; o++){
          if (big_game_field[i][o] != 'v'){
            simbol_quantity += 1;
          };
      };
      if (simbol_quantity == 10){
        combinations[combinations_index] = i;
        combinations_index += 1;
        for (int z = i; z > 0; z--){
          for (int el = 0; el < 10; el++){
            big_game_field[z][el] = big_game_field[z - 1 ][el];
          };
          
        };
      };
    };
    
  };
  
  
  void figure_one_step_left(){
    bool can_go_left = true;
    for (int i = 0; i < 4; i++){
      if (falling_figure[i][0] <= 0 || big_game_field[falling_figure[i][1]][falling_figure[i][0] - 1] != 'v'){
          can_go_left = false;
      };
    };
    if (can_go_left == true){
      for (int i = 0; i < 4; i++){
        falling_figure[i][0] -= 1;
      };
      current_figure_x -= 1;
    };
  };
  
  void figure_one_step_right(){
    bool can_go_right = true;
    for (int i = 0; i < 4; i++){
      if (falling_figure[i][0] >= 9 || big_game_field[falling_figure[i][1]][falling_figure[i][0] + 1] != 'v'){
          can_go_right = false;
      };
    };
    if (can_go_right == true){
      for (int i = 0; i < 4; i++){
        falling_figure[i][0] += 1;
      };
        current_figure_x += 1;
    };
  };


  // функция поворота фигуры(дописать адаптацию под разное количество поворотов)
  void change_figure_angle(){
    bool can_change_angle = true;
    int new_figure[4][2] = {};
    int next_figure_angle = current_figure_angle + 1;
    if (next_figure_angle == 4){
      next_figure_angle = 0;
    };
    for (int i = 0; i < 4; i++){
      new_figure[i][0] = figures[current_figure_index][next_figure_angle][i][0] + current_figure_x;
      new_figure[i][1] = figures[current_figure_index][next_figure_angle][i][1] + current_figure_y;
      if (new_figure[i][0] < 0 || new_figure[i][0] > 9 || big_game_field[new_figure[i][1]][new_figure[i][0]] != 'v' ){
        can_change_angle = false;
        break;
      };
    };
    if (can_change_angle == true){
      for (int i = 0; i < 4; i++){
        falling_figure[i][0] = new_figure[i][0];
        falling_figure[i][1] = new_figure[i][1];
      };
      current_figure_angle = next_figure_angle;
    };
  };
  
};



class Buttons{
  public:
  int left_last = 0;
  int left_current = 0;
  
  bool left_button(bool electro){
    bool to_switch = false;
    if (electro){
      left_current = electro;
    } else {
      left_current = 0;
    };
    if (left_current == 1 && left_last == 0){
      to_switch = true;
    };
    left_last = left_current;
    return to_switch;
  };
  
  
  
  int right_last = 0;
  int right_current = 0;
  
  bool right_button(bool electro){
    bool to_switch = false;
    if (electro){
      right_current = electro;
    } else {
      right_current = 0;
    };
    if (right_current == 1 && right_last == 0){
      to_switch = true;
    };
    right_last = right_current;
    return to_switch;
  };
  
  
  
  int spin_last = 0;
  int spin_current = 0;
  
  bool spin_button(bool electro){
    bool to_switch = false;
    if (electro){
      spin_current = electro;
    } else {
      spin_current = 0;
    };
    if (spin_current == 1 && spin_last == 0){
      to_switch = true;
    };
    spin_last = spin_current;
    return to_switch;
  }; 
  
  int go_down_last = 0;
  int go_down_current = 0;

  bool go_down_button(bool electro){
    bool to_switch = false;
    if (electro){
      go_down_current = electro;
    } else {
      go_down_current = 0;
    };
    if (go_down_current == 1 && go_down_last == 0){
      to_switch = true;
    };
    go_down_last = go_down_current;
    return to_switch;
  };
  

};



Game game;

  
#include <FastLED.h>

// uno
//#define rgb_pin 6

// nano
#define rgb_pin 12


class RGB_matrix{
  public:
  
  CRGB leds[256];

  void init(){
    FastLED.addLeds<WS2812, rgb_pin, GRB>(leds, 256); // rgb_pin объявлен в начале кода 
    FastLED.setBrightness(11);
    FastLED.clear(true);
    FastLED.show();
  };
  
  
  int XY(int x, int y) {
    int index = 0;
    if (y % 2 == 0) {
      index = 16 * (y - 1) + x - 1;
    } else if (y % 2 > 0) {
      index = 16 * y - x;
    };
    return index;
  };  
  
  
  void border(){
    for (int i = 0; i < 12; i++){
      leds[XY(3 + i, 1)] = CRGB::White;
      FastLED.show();
      delay(210);
    };
    for (int i = 0; i < 16; i++){
      leds[XY(14, 2 + i)] = CRGB::White;
      FastLED.show();
      delay(210);
    };
    for (int i = 0; i < 12; i++){
      leds[XY(14 - i, 16)] = CRGB::White;
      FastLED.show();
      delay(210);
    };
    for (int i = 0; i < 16; i++){
      leds[XY(3, 16 - i)] = CRGB::White;
      FastLED.show();
      delay(210);
    };
  };
  
  
  void show_virtual_matrix(){
    int start_show_x = 4;
    int start_show_y = 2;
    for (int i = 4; i < 18; i++){
      for (int o = 0; o < 10; o++){
        if (game.big_game_field[i][o] == 'v'){
          leds[XY(start_show_x + o, start_show_y + (i - 4))] = CRGB::Black;
        } else if (game.big_game_field[i][o] == 's'){
          leds[XY(start_show_x + o, start_show_y + (i - 4))] = CRGB::Yellow;
        } else if (game.big_game_field[i][o] == 't'){
          leds[XY(start_show_x + o, start_show_y + (i - 4))] = CRGB::Purple;
        } else if (game.big_game_field[i][o] == 'g'){
          leds[XY(start_show_x + o, start_show_y + (i - 4))] = CRGB::Blue;
        } else if (game.big_game_field[i][o] == 'l'){
          leds[XY(start_show_x + o, start_show_y + (i - 4))] = CRGB::Orange;
        } else if (game.big_game_field[i][o] == 'z'){
          leds[XY(start_show_x + o, start_show_y + (i - 4))] = CRGB::Red;
        } else if (game.big_game_field[i][o] == 'w'){
          leds[XY(start_show_x + o, start_show_y + (i - 4))] = CRGB::Green;
        } else if (game.big_game_field[i][o] == 'i'){
          leds[XY(start_show_x + o, start_show_y + (i - 4))] = CRGB::Aqua;
        };
      };
    };
    for (int u = 0; u < 4; u++){
      char symbol = game.figure_simbol[game.current_figure_index];
      if (game.falling_figure[u][1] < 4){
          continue;
      };
      int leds_position = XY(4 + game.falling_figure[u][0], game.falling_figure[u][1] - 2);
      if (symbol == 's'){
        leds[leds_position] = CRGB::Yellow;
      } else if (symbol == 't'){
          leds[leds_position] = CRGB::Purple;
      } else if (symbol == 'g'){
          leds[leds_position] = CRGB::Blue;
      } else if (symbol == 'l'){
          leds[leds_position] = CRGB::Orange;
      } else if (symbol == 'z'){
          leds[leds_position] = CRGB::Red;
      } else if (symbol == 'w'){
          leds[leds_position] = CRGB::Green;
      } else if (symbol == 'i'){
          leds[leds_position] = CRGB::Aqua;
      };
      
    };

    char symbol_next_figure = game.figure_simbol[game.random_next_figure_num];
    int leds_position = XY(15, 2);
    if (symbol_next_figure == 's'){
      leds[leds_position] = CRGB::Yellow;
    } else if (symbol_next_figure == 't'){
        leds[leds_position] = CRGB::Purple;
    } else if (symbol_next_figure == 'g'){
        leds[leds_position] = CRGB::Blue;
    } else if (symbol_next_figure == 'l'){
        leds[leds_position] = CRGB::Orange;
    } else if (symbol_next_figure == 'z'){
        leds[leds_position] = CRGB::Red;
    } else if (symbol_next_figure == 'w'){
        leds[leds_position] = CRGB::Green;
    } else if (symbol_next_figure == 'i'){
        leds[leds_position] = CRGB::Aqua;
    };

    FastLED.show();
  };
  
  // запускает финальную анимацию
  void end_animation(){
    int one_led_position = XY(15, 2);
    leds[one_led_position] = CRGB::Black;

    // mega
    //CRGB blinks[256] = {};
    //for (int i = 0; i < 256; i++){
    //    blinks[i] = leds[i];
    //};
    
    auto make_field_black = [&](){
      for (int o = 0; o < 14; o++){
        for (int z = 0; z < 10; z++){
          leds[XY(4 + z, 2 + o)] = CRGB::Black;
        };
      };
    };

    // mega
    //auto make_field_color = [&](){
    //  for (int q = 0; q < 256; q++){
    //    leds[q] = blinks[q];
    //  };
    //};
    
    auto chess_animation = [&](){

      for (int i = 0; i < 10; i++){
        if (i % 2 == 0){
          for (int o = 0; o < 14; o += 2){
            leds[XY(4 + i, 2 + o)] = CRGB::White;
              
          };
        } else {
          for (int o = 1; o < 14; o += 2){
            leds[XY(4 + i, 2 + o)] = CRGB::White;
          };
        };
      };

      FastLED.show();
      delay(1500);
    
      for (int i = 0; i < 10; i++){
        if (i % 2 != 0){
          for (int o = 0; o < 14; o += 2){
            leds[XY(4 + i, 2 + o)] = CRGB::White;
              
          };
        } else {
          for (int o = 1; o < 14; o += 2){
            leds[XY(4 + i, 2 + o)] = CRGB::White;
          };
        };
      };
      FastLED.show();
    
    };
    
    for (int l = 0; l < 3; l++){
      // mega
      //make_field_black();
      //FastLED.show();
      //delay(250);
      //make_field_color();
      //FastLED.show();
      //delay(250);
      //make_field_black();
      //FastLED.show();
      //delay(250);
      //make_field_color();
      //FastLED.show();
      //delay(250);
      //make_field_black();
      //FastLED.show();
      //delay(250);
      chess_animation();
      FastLED.show();
      delay(800);
      make_field_black();
      FastLED.show();
      delay(300);
    };
  };
    
};

// uno
//#define Left 8
//#define Right 9
//#define Spin 10
//#define Go_down 11

// nano
#define Left 10
#define Right 4
#define Spin 8
#define Go_down 6


RGB_matrix matrix;
Buttons button;

unsigned long timer;

void setup(){
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Spin, INPUT);
  pinMode(Go_down, INPUT);
  matrix.init();
  matrix.border();
  game.void_big_game_field();
  randomSeed(analogRead(A1));
  timer = millis();
};

int start_interval = 800;

void loop(){
  if (game.have_active_figure == false){
    game.start_figure();
    if (game.figure_round == 0){
      game.random_current_figure_num = random(0, 7);
      game.current_figure_index = game.random_current_figure_num;
      game.init_figure_into_falling_figure(game.random_current_figure_num);
      game.random_next_figure_num = random(0, 7);
    } else if (game.figure_round != 0){
      game.random_current_figure_num = game.random_next_figure_num;
      game.random_next_figure_num = random(0, 7);
      game.current_figure_index = game.random_current_figure_num;
      game.init_figure_into_falling_figure(game.random_current_figure_num);
    };
    matrix.show_virtual_matrix();
    game.have_active_figure = true;
  };
  

  int pin_left = digitalRead(Left);
  int pin_right = digitalRead(Right);
  int pin_spin = digitalRead(Spin);
  int pin_go_down = digitalRead(Go_down);

  if (button.left_button(pin_left) == true){
    game.figure_one_step_left();
    matrix.show_virtual_matrix();
  };

  if (button.right_button(pin_right) == true){
    game.figure_one_step_right();
    matrix.show_virtual_matrix();
  };

  if (button.spin_button(pin_spin) == true){
    game.change_figure_angle();
    matrix.show_virtual_matrix();
  };

  auto using_go_down_func = [&](){
    bool fixed = game.figure_one_step_down();
    matrix.show_virtual_matrix();
    if (fixed){
      bool end_or_not = game.end_or_not();
      if (end_or_not == false){
        game.combination_collapse();
        matrix.show_virtual_matrix();
        game.have_active_figure = false;
      } else if (end_or_not == true){
        matrix.end_animation();
        game.start_round();
        game.have_active_figure = false;
      };
    };
  };


  if (millis() - timer > start_interval - game.speed_interval){
    timer = millis();
    using_go_down_func();
  };

  if (button.go_down_button(pin_go_down) == true){
    using_go_down_func();
  };

}