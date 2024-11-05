#include <math.h>
#include <stdio.h>

int is_prime(int n) {
  int ret = 1;
  if (n == 1 || (n % 2 == 0 && n != 2)) {
    ret = 0;
  }
  for (int i = 3; i < sqrt(n); i += 2) {
    if (n % i == 0) {
      ret = 0;
      break;
    }
  }
  return ret;
}

int is_prime_by_exist(int x, int known_primes[], int len_known) {
  int ret = 1;
  for (int i = 0; i < len_known; i++) {
    if (x % known_primes[i] == 0) {
      ret = 0;
      break;
    }
  }
  return ret;
}

int get_prime(void) {
  int x;
  int cnt = 0;
  x = 2;
  // for (x = 2; x < 100; x++)
  while (cnt < 50) {
    if (is_prime(x)) {
      printf("%d ", x);
      cnt++;
    }
    x++;
  }
  printf("\n");
  return 0;
}

int get_prime2(int n, int m) {
  int x;
  int cnt = 0;
  x = n;
  // for (x = 2; x < 100; x++)
  while (cnt < m) {
    if (is_prime(x)) {
      printf("%d ", x);
      cnt++;
    }
    x++;
  }
  printf("\n");
  return 0;
}

int get_prime3(int n, int m) {
  int x = 2;
  int cnt = 0;
  int sum = 0;
  while (cnt < m) {
    if (is_prime(x)) {
      // printf("%d ", x);
      cnt++;
      if (cnt >= n && cnt <= m) {
        sum += x;
      }
      printf("x=%d,cnt=%d,sum=%d\n", x, cnt, sum);
    }
    x++;
  }
  printf("%d\n", sum);
  return 0;
}

int make_prime(void) {
  const int number = 10;
  // int prime[number] = {2}; // cannot compile
  int prime[number];
  prime[0] = 2;
  int count = 1;
  int i = 3;
  while (count < number) {
    if (is_prime_by_exist(i, prime, count)) {
      prime[count++] = i;
    }
    // {
    //   printf("i=%d \tcnt=%d\t", i, count);
    //   int i;
    //   for (i = 0; i < number; i++) {
    //     printf("%d\t", prime[i]);
    //   }
    //   printf("\n");
    // }
    i++;
  }
  for (i = 0; i < number; i++) {
    printf("%d", prime[i]);
    if ((i + 1) % 5)
      printf("\t");
    else
      printf("\n");
  }
  return 0;
}

// 构造素数表
// 欲构造n以内的素数表
// 1.令x为2
// 2.将2x、3x、4x直至ax<n的数标记为非素数
// 3.令x为下一个没有被标记为非素数的数，重复2;直到所有的数都已经尝试完毕
int make_prime2(void) {
  const int max_number = 25;
  int is_prime[max_number];
  int i;
  int x;
  for (i = 0; i < max_number; i++) {
    is_prime[i] = 1;
  }
  for (x = 2; x < max_number; x++) {
    if (is_prime[x]) {
      // 倍数全部标记为0
      for (i = 2; i * x < max_number; i++) {
        is_prime[i * x] = 0;
      }
    }
  }
  for (i = 2; i < max_number; i++) {
    if (is_prime[i]) {
      printf("%d\t", i);
    }
  }
  printf("\n");
  return 0;
}

int main() {
  make_prime();
  make_prime2();

  get_prime();
  get_prime2(2, 4);
  get_prime3(4, 8);

  int n;
  scanf("%d", &n);
  if (is_prime(n)) {
    printf("是素数");
  } else {
    printf("不是素数");
  }

  return 0;
}