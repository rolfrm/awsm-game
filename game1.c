//compile with clang: clang-9 --target=wasm32 -nostdlib -Wl,--export-all -Wl,--no-entry -O3 -Wl,-no-gc-sections game1.c -Wl,--allow-undefined  -o game1.wasm 
typedef unsigned long long u64;


// functionality defined by libawsm
int print_str(const char * x);

// functionality defined by the 'engine'
float sinf(float x);
void swap_buffer();
void blit(float x, float y, float w, float h, float r, float g, float b, float a);
u64 load_texture(const char * path);
void blit_texture(float x, float y, u64 img);
void scale(float x, float y);
void translate(float x, float y);

void go(){
  print_str("starting 'game'\n");
  float x = 200.5;
  u64 tex = load_texture("../iron/duck.png");
  while(1){

    blit(-1,-0.9,2,1.8,0.2,0.2,0.2,1);


    blit(sinf(x * 0.01) * 0.5, sinf(x * 0.01 + 3.14 * 0.5) * 0.5, 0.1, 0.1, 1.0, 0.0, 0.0, 0.5);
    blit(sinf(-x * 0.01) * 0.5, sinf(x * 0.01 + 3.14 * 0.5) * 0.5, 0.1, 0.1, 0.0, 1.0, 0.0, 0.5);
    translate(0.0,sinf(x * 0.1) * 0.25);
    scale(1 + sinf(x * 0.1) * 0.2,1 + sinf(x * 0.1) * 0.2);
    
    scale(0.25, 0.25);
    blit_texture(sinf(-x * 0.01) * 0.5, 0, tex);

    swap_buffer();
    //x += 1;

  }

}
