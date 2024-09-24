static inline unsigned int CC () __attribute__ ((always_inline));
static inline unsigned long long rdtsc () __attribute__ ((always_inline));

static inline unsigned int CC ()
  {
  int a;
  asm volatile ("rdtsc" : "=a" (a) : : "rdx");
  return a;
  }

static inline unsigned long long rdtsc ()
  {
  unsigned int tickl, tickh;
  asm volatile ("rdtsc" : "=a" (tickl), "=d" (tickh));
  return ((unsigned long long)tickh << 32) | tickl;
  }  
