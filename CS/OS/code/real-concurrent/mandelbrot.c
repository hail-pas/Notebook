#include "../thread/thread.h"
#include <math.h>


/**
 * @brief Mandelbrot set 是一个非常经典的分型图形，描绘了函数 f(z) = z^2 + c 的轨迹是否有界。
 * 对于复平面上每一个点，我们的计算都是并行的——因此我们的并行化也是十分简单：
 * 只需使用 OpenMP 对计算图作出静态划分即可。我们混用了 OpenMP 和我们的线程库。
 * 我们的线程库仅限于隔一段时间将当前渲染的结果显示在屏幕上，并在所有线程结束后输出渲染图。
 */


/**
 * @brief 依賴安裝
    curl https://sh.rustup.rs -sSf | sh
    cargo install viu
    source "$HOME/.cargo/env"
    
 *
 */

int NT;
#define W 6400
#define H 6400
#define IMG_FILE "mandelbrot.ppm"

static inline int belongs(int x, int y, int t) {
  return x / (W / NT) == t;
}

int x[W][H];
_Atomic int done = 0;

void dump(FILE *fp, int step) {
  int w = W / step, h = H / step;
  // STFW: Portable Pixel Map
  fprintf(fp, "P6\n%d %d 255\n", w, h);
  for (int j = 0; j < H; j += step) {
    for (int i = 0; i < W; i += step) {
      int n = x[i][j];
      int r = 255 * pow((n - 80) / 800.0, 3);
      int g = 255 * pow((n - 80) / 800.0, 0.7);
      int b = 255 * pow((n - 80) / 800.0, 0.5);
      fputc(r, fp); fputc(g, fp); fputc(b, fp);
    }
  }
}

void Tworker(int tid) {
  for (int i = 0; i < W; i++)
    for (int j = 0; j < H; j++)
      if (belongs(i, j, tid - 1)) {
        double a = 0, b = 0, c, d;
        while ((c = a * a) + (d = b * b) < 4 && x[i][j]++ < 880) {
          b = 2 * a * b + j * 1024.0 / H * 8e-9 - 0.645411;
          a = c - d + i * 1024.0 / W * 8e-9 + 0.356888;
        }
      }
  atomic_fetch_add(&done, 1);
}

void Tdump() {
  float ms = 0;
  while (1) {
    FILE *fp = popen("viu -", "w"); assert(fp);
    dump(fp, W / 256);
    pclose(fp);
    if (atomic_load(&done) == NT) break;
    usleep(1000000 / 2);
    ms += 1000.0 / 2;
  }
  printf("Approximate render time: %.1lfs\n", ms / 1000);

  FILE *fp = fopen(IMG_FILE, "w"); assert(fp);
  dump(fp, 2);
  fclose(fp);
}

int main(int argc, char *argv[]) {
  assert(argc == 2);
  NT = atoi(argv[1]);

  create(Tdump);

  #pragma omp parallel num_threads(NT)
  #pragma omp for schedule(static)
  for (int i = 0; i < NT; i++) {
    Tworker(i + 1);  // Sequential code
  }
  // Equivalent to:

  for (int i = 0; i < NT; i++) {
    create(Tworker);
  }

  join();
  return 0;
}
