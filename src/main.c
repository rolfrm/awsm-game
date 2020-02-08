#include <iron/full.h>
#include <iron/gl.h>
#include <awsm.h>

static void * mem_clone(void * ptr, size_t s){
  void * new = alloc(s);
  memcpy(new, ptr, s);
  return new;
}

gl_window * win;
typedef wasm_execution_stack stack;

static void _swap_buffer(stack * _){
  UNUSED(_);
  gl_window_swap(win);
  gl_window_poll_events();
  blit_begin(BLIT_MODE_UNIT);
}

static void _blit(stack * stk){
  f32 x, y, w, h, r, g, b, a;
  a = awsm_pop_f32(stk);
  b = awsm_pop_f32(stk);
  g = awsm_pop_f32(stk);
  r = awsm_pop_f32(stk);
  h = awsm_pop_f32(stk);
  w = awsm_pop_f32(stk);
  y = awsm_pop_f32(stk);
  x = awsm_pop_f32(stk);
  blit_rectangle(x,y,w,h,r,g,b,a);
}

static void _sinf(stack * stk){
  awsm_push_f32(stk, sin(awsm_pop_f32(stk)));
}

static void _load_texture(stack * stk){
  const char * path = awsm_pop_ptr(stk);
  image img = image_from_file(path);
  texture tex = texture_from_image(&img);
  texture * t = mem_clone(&tex, sizeof(tex));
  awsm_push_u64(stk, (u64) t);
}

static void _blit_texture(stack * stk){
  f32 x, y;
  u64 tex;
  tex = awsm_pop_u64(stk);
  y = awsm_pop_f32(stk);
  x = awsm_pop_f32(stk);
  blit(x, y, (void *) tex);
}

static void _blit_scale(stack * stk){
  f32 y = awsm_pop_f32(stk);
  f32 x = awsm_pop_f32(stk);
  blit_scale(x, y);
}

static void _blit_translate(stack * stk){
 f32 y = awsm_pop_f32(stk);
 f32 x = awsm_pop_f32(stk);
 blit_translate(x, y);
}

int main(int argc,const char * argv[]){
  UNUSED(argc);
  UNUSED(argv);
  if(argc == 1){
    printf("provide an executable...\n");
    return 1;
  }
  wasm_module * mod = awsm_load_module_from_file(argv[1]);
  awsm_register_function(mod, _swap_buffer, "swap_buffer");
  awsm_register_function(mod, _blit, "blit");
  awsm_register_function(mod, _sinf, "sinf");
  awsm_register_function(mod, _load_texture, "load_texture");
  awsm_register_function(mod, _blit_texture, "blit_texture");
  awsm_register_function(mod, _blit_scale, "scale");
  awsm_register_function(mod, _blit_translate, "translate");
  if(mod == NULL){
    printf("provide an executable...\n");
    return 1;
  }
  awsm_load_thread(mod, "go");
  
  win = gl_window_open(512, 512);
  gl_window_make_current(win);
  blit_begin(BLIT_MODE_UNIT);
  while(awsm_process(mod, 1024)){
    
  }
	      
  
  return 0;
}
