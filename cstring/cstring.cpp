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
      return 1;
    }

    if (*first < *second) {
      return -1;
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
      return 1;
    }

    if (*first < *second) {
      return -1;
    }

    ++first;
    ++second;
    ++size;
  }

  if (size == count) {
    return 0;
  }
  if (*first && !*second) {
    return 1;
  }
  if (!*first && *second) {
    return -1;
  }

  return 0;
}

char* Strcpy(char* dest, const char* src) {
  char* helper = dest;

  while (*src != '\0') {
    *dest = *src;
    ++dest;
    ++src;
  }

  *dest = '\0';

  return helper;
}

char* Strncpy(char* dest, const char* src, size_t count) {
  char* helper = dest;
  size_t size = 0;

  while (*src && size < count) {
    *dest = *src;
    ++dest;
    ++src;
    ++size;
  }

  if (size < count) {

    while (size < count) {
      *dest = '\0';
      ++dest;
      ++size;
    }
  }

  return helper;
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
    return str + count;
  }

  if (answer != -1) {
    return str + answer;
  }

  return nullptr;
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
  while (*dest) {
    if (Strchr(breakset, *dest) != nullptr) {
      return dest;
    }
    ++dest;
  }

  return nullptr;
}

const char* Strstr(const char* str, const char* pattern) {
  if (*pattern == '\0') {
    return str;
  }

  while (*str != '\0') {
    const char* pattern_helper = pattern;
    const char* str_helper = str;

    while (*pattern_helper != '\0' && *str_helper == *pattern_helper) {
      ++pattern_helper;
      ++str_helper;
    }

    if (*pattern_helper == '\0') {
      return str;
    }

    ++str;
  }

  return nullptr;
}
