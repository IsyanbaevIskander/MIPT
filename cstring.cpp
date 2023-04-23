#include <iostream>
#include "cstring.h"
#include <cstring>

size_t Strlen(const char* str) {
  size_t len = 0;

  while (*str) {
    ++len;
    ++str;
  }

  return len;
}

int Strcmp(const char* first, const char* second) {
  while (*first && *second) {

    if (*first > *(second)) {
      break;
    }

    if (*first < *second) {
      break;
    }
    ++first;
    ++second;
  }

  return *first - *second;
}

int Strncmp(const char* first, const char* second, size_t count) {
  size_t size = 0;

  while (size < count && *first && *second) {
    if (*first > *second) {
      break;
    }

    if (*first < *second) {
      break;
    }

    ++first;
    ++second;
    ++size;
  }

  return *first - *second;
}

char* Strcpy(char* dest, const char* src) {
  int count = 0;

  while (*src != '\0') {
    *dest = *src;
    ++dest;
    ++src;
    ++count;
  }

  *dest = '\0';

  return dest - count;
}

char* Strncpy(char* dest, const char* src, size_t count) {
  int index;
  size_t size = 0;

  while (*src && size < count) {
    *dest = *src;
    ++dest;
    ++index;
    ++src;
    ++size;
  }

  if (size < count) {

    while (size < count) {
      *dest = '\0';
      ++dest;
      ++index;
      ++size;
    }
  }

  return dest - index;
}

char* Strcat(char* dest, const char* src) {
  size_t len_dest = Strlen(dest);
  size_t len_src = Strlen(src);

  for (size_t i = 0; i < len_src; ++i) {
    *(dest + (i + len_dest)) = *(src + i);
  }

  return dest;
}

char* Strncat(char* dest, const char* src, size_t count) {
  size_t size = 0;
  size_t len_dest = Strlen(dest);
  size_t len_src = Strlen(src);

  for (size_t i = 0; i < len_src && size < count; ++i, ++size) {
    *(dest + (i + len_dest)) = *(src + i);
  }

  return dest;
}

const char* Strchr(const char* str, char symbol) {
  int count = 0;

  while (str[count] != '\0' && str[count] != symbol) {
    ++count;
  }

  return str[count] == symbol ? str + count : nullptr;
}

const char* Strrchr(const char* str, char symbol) {
  int count = 0;
  int answer = -1;

  while (str[count] != '\0') {

    if (*(str + count) == symbol) {
      answer = count;
    }

    ++count;
  }

  if (str[count] == symbol) {
    answer = count;
  }

  return (answer == -1 ? nullptr : str + answer);
}

size_t Strspn(const char* dest, const char* src) {
  size_t answer = 0;

  while (*dest) {
    if (Strchr(src, *dest) != nullptr) {
      ++answer;
    } else {
      break;
    }
    ++dest;
  }

  return answer;
}

size_t Strcspn(const char* dest, const char* src) {
  size_t answer = 0;

  while (*dest) {
    if (Strchr(src, *dest) == nullptr) {
      ++answer;
    } else {
      break;
    }
    ++dest;
  }

  return answer;
}

const char* Strpbrk(const char* dest, const char* breakset) {
  bool flag = false;

  while (*dest) {
    if (Strchr(breakset, *dest) != nullptr) {
      flag = true;
      break;
    }
    ++dest;
  }

  return (flag ? dest :nullptr);
}

const char* Strstr(const char* str, const char* pattern) {
  if (*pattern == '\0') {
    return str;
  }

  bool flag = false;

  while (*str != '\0') {
    const char* pattern_helper = pattern;
    const char* str_helper = str;

    while (*pattern_helper != '\0' && *str_helper == *pattern_helper) {
      ++pattern_helper;
      ++str_helper;
    }

    if (*pattern_helper == '\0') {
      flag= true;
      break;
    }

    ++str;
  }

  return flag ? str : nullptr;
}
