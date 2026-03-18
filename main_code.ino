
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
    {{4, 1}, {5, 2}, {3, 3}, {4, 3}},
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
    {{3, 2}, {4, 2}, {5, 2}, {5, 3}},
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
  
  
  // функция обновления фигуры(сброс переменных, инициализация новой, вызов рандома)
  void start_figure(){};
  
  
  // сброс поля, отрисовка нового поля
  void start_round(){};
  
  
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
        current_figure_y += 1;
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