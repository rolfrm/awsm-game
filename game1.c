//compile with clang: clang-9 --target=wasm32 -nostdlib -Wl,--export-all -Wl,--no-entry -O3 -Wl,-no-gc-sections game1.c -Wl,--allow-undefined  -o game1.wasm 

void * get_symbol(const char * module, const char * symbol, unsigned int argcount, unsigned int retcount);
float sinf(float x);
int print_str(const char * x);
void print_i32(int x);
void print_f32(float x);
//void print_f64(double x);
void require_i32(int x, int y);
int awsm_fork();

void swap_buffer();
void blit(float x, float y, float w, float h, float r, float g, float b, float a);

typedef unsigned long long u64;

u64 load_texture(const char * path);
void blit_texture(float x, float y, u64 img);
void scale(float x, float y);

void go(){
  float x = 0.0;
  u64 tex = load_texture("../iron/duck.png");
  while(1){
    blit(-0.9,-0.9,1.8,1.8,0.2,0.2,0.2,0.05);
    

    blit(sinf(x * 0.01) * 0.5, sinf(x * 0.01 + 3.14 * 0.5) * 0.5, 0.1, 0.1, 1.0, 0.0, 0.0, 0.5);
    blit(sinf(-x * 0.01) * 0.5, sinf(x * 0.01 + 3.14 * 0.5) * 0.5, 0.1, 0.1, 0.0, 1.0, 0.0, 0.5);
    scale(0.25, 0.25);
    blit_texture(0, 0, tex);

    swap_buffer();
    x += 1;

  }

}