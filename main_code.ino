class Game{
  public:
  
  int figures[19][4][2] = {
    // квадрат 
    {{1, 2}, {2, 2}, {1, 3}, {2, 3}},
    // т вниз       
    {{0, 2}, {1, 2}, {2, 2}, {1, 3}},
    // т влево
    {{2, 1}, {1, 2}, {2, 2}, {2, 3}},
    // т вправо
    {{1, 1}, {1, 2}, {2, 2}, {1, 3}},
    // т вверх
    {{1, 2}, {0, 3}, {1, 3}, {2, 3}},
    // г вниз
    {{0, 2}, {1, 2}, {2, 2}, {2, 3}},
    // г влево
    {{1, 1}, {2, 1}, {1, 2}, {1, 3}},
    // г вправо
    {{2, 1}, {2, 2}, {1, 3}, {2, 3}},
    // г вверх
    {{0, 2}, {0, 3}, {1, 3}, {2, 3}},
    // L вниз
    {{0, 2}, {0, 3}, {1, 3}, {2, 3}},
    // L влево
    {{1, 1}, {2, 1}, {2, 2}, {2, 3}},
    // L вправо
    {{1, 1}, {1, 2}, {1, 3}, {2, 3}},
    // L вверх
    {{2, 2}, {0, 3}, {1, 3}, {2, 3}},
    // зигзаг горизонтально
    {{0, 2}, {1, 2}, {1, 3}, {2, 3}},
    // зигзаг вертикально
    {{2, 1}, {1, 2}, {2, 2}, {1, 3}},
    // зиг ререрс горизонтально
    {{1, 2}, {2, 2}, {0, 3}, {1, 3}},
    // зиг реверс вертикально
    {{1, 1}, {1, 2}, {2, 2}, {2, 3}},
    // I вертикально
    {{1, 0}, {1, 1}, {1, 2}, {1, 3}},
    // I горизонтально
    {{0, 3}, {1, 3}, {2, 3}, {3, 3}},
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
  
  char figure_simbol[19] = {
      's', // квадрат
      't', 't', 't', 't', // т фигура
      'g', 'g', 'g', 'g', // г фигура
      'l', 'l', 'l', 'l', // L фигура
      'z', 'z', // зигзаг
      'w', 'w', // зигзаг реверс
      'i', 'i' // палка
  };
  
  
  int start_figure_x = 3;
  int start_figure_y = 0;
  int current_figure_index = 0;
  
    // массив, в котором хранятся текущие индексы в игровом поле падающей фигуры
  int falling_figure[4][2] = {};    
  
  
  void figure_init_into_field(){
    for (int i = 0; i < 4; i++){
      falling_figure[i][0] = figures[current_figure_index][i][0] + start_figure_x;
      falling_figure[i][1] = figures[current_figure_index][i][1] + start_figure_y;
    };
    
  };
  
  
  // добавляет символы фигуры на поле. принимает индекс фигуры. берет символ по индексу из массива figure_simbol 
  void fix_figure_position(){
    for (int i = 0; i < 4; i++){
      big_game_field[falling_figure[i][1]][falling_figure[i][0]] =  figure_simbol[current_figure_index];
    };
  };
  
  
  void figure_one_step_down(){
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
    };
    if (can_go_down == false){
      fix_figure_position();
    };
  };
  
  
  enum End_State {END, NOT_END};
  
  End_State end_or_not(){
    for (int i = 0; i < 4; i++){
      if (falling_figure[i][1] < 4){
        return END;
      };
    };
    return NOT_END;
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
    };
  };
  
  void figure_one_step_right(){
    bool can_go_right = true;
    for (int i = 0; i < 4; i++){
      if (falling_figure[i][0] >= 10 || big_game_field[falling_figure[i][1]][falling_figure[i][0] + 1] != 'v'){
          can_go_right = false;
      };
    };
    if (can_go_right == true){
      for (int i = 0; i < 4; i++){
        falling_figure[i][0] += 1;
      };
    };
  };
  
  
};