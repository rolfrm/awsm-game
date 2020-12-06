//compile with clang: clang-9 --target=wasm32 -nostdlib -Wl,--export-all -Wl,--no-entry -O3 -Wl,-no-gc-sections game1.c -Wl,--allow-undefined  -o game1.wasm 
typedef unsigned long long u64;
enum{
  KEY_UP = 265,
  KEY_DOWN = 264,
  KEY_LEFT = 263,
  KEY_RIGHT = 262,
  KEY_ESC =  256,
  KEY_ENTER = 257,
  KEY_BACKSPACE = 259,
  KEY_CTRL = 341,
  KEY_SHIFT = 340,
  KEY_F1 = 290,
  KEY_F2 = 291,
  KEY_F3 = 292,
  KEY_F4 = 293,
  KEY_F5 = 294,
  KEY_F6 = 295,
  KEY_F7 = 296,
  KEY_F8 = 297,
  KEY_F9 = 298,
  KEY_F10 = 299,
  KEY_F11 = 300,
  KEY_F12 = 301,
  KEY_A = 65,
  KEY_B = 66,
  KEY_C = 67,
  KEY_D = 68,
  KEY_E = 69,
  KEY_F = 70,
  KEY_G = 71,
  KEY_H = 72,
  KEY_I = 73,
  KEY_J = 74,
  KEY_K = 75,
  KEY_L = 76,
  KEY_M = 77,
  KEY_N = 78,
  KEY_O = 79,
  KEY_P = 80,
  KEY_Q = 81,
  KEY_R = 82,
  KEY_S = 83,
  KEY_T = 84,
  KEY_U = 85,
  KEY_V = 86,
  KEY_W = 87,
  KEY_X = 88,
  KEY_Y = 89,
  KEY_Z = 90
};


// functionality defined by libawsm
int print_str(const char * x);

// functionality defined by the 'engine'
float sinf(float x);
void swap_buffer();
void blit_init();
void blit(float x, float y, float w, float h, float r, float g, float b, float a);
u64 load_texture(const char * path);
void blit_texture(float x, float y, u64 img);
void scale(float x, float y);
void translate(float x, float y);
int key_down(int key);
void go(){
  print_str("starting 'game'\n");
  float x = 200.5;
  u64 tex = load_texture("../iron/duck.png");
  while(1){
    blit_init();
    blit(-1,-0.9,2,1.8,0.2,0.2,0.2,1);
    blit(sinf(x * 0.01) * 0.5, sinf(x * 0.01 + 3.14 * 0.5) * 0.5, 0.1, 0.1, 1.0, 0.0, 0.0, 0.5);
    blit(sinf(-x * 0.01) * 0.5, sinf(x * 0.01 + 3.14 * 0.5) * 0.5, 0.1, 0.1, 0.0, 1.0, 0.0, 0.5);
    translate(0.0,sinf(x * 0.1) * 0.25);
    scale(1 + sinf(x * 0.1) * 0.2,1 + sinf(x * 0.1) * 0.2);
    
    scale(0.25, 0.25);
    blit_texture(sinf(-x * 0.01) * 0.5, 0, tex);

    swap_buffer();
    if(key_down(KEY_A)){
      
      print_str("111\n");
      x += 1.0;
    }
    if(key_down(KEY_D))
      x -= 1.0;
    //x += 1;

  }

}
